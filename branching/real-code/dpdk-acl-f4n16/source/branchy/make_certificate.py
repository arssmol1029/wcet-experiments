#!/usr/bin/env python3
"""Bind finite domain, conservative source bounds, and immutable local evidence.

No model, flow facts, remote command, or solver is run by this script.
"""
import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path

p=argparse.ArgumentParser()
p.add_argument('--out',type=Path,required=True)
a=p.parse_args()
here=Path(__file__).resolve().parent
common=here.parent/'dpdk-acl-port'
families=[
    {'name':'F0','protocol_value':0,'protocol_mask':240,'source_ipv4':0x0a000000,'source_prefix_bits':8},
    {'name':'F1','protocol_value':1,'protocol_mask':15,'source_ipv4':0x08000000,'source_prefix_bits':6},
    {'name':'F2','protocol_value':1,'protocol_mask':3,'source_ipv4':0x0c000000,'source_prefix_bits':6},
    {'name':'F3','protocol_value':0,'protocol_mask':12,'source_ipv4':0,'source_prefix_bits':4}]

def part(fs,source):
    cells=defaultdict(list)
    for byte in range(256):
        sig=0
        for i,f in enumerate(fs):
            mask=((255<<(8-f['source_prefix_bits']))&255) if source else f['protocol_mask']
            val=((f['source_ipv4']>>24)&mask) if source else f['protocol_value']
            sig|=int((byte&mask)==val)<<i
        cells[sig].append(byte)
    assert sorted(b for bs in cells.values() for b in bs)==list(range(256))
    return [{'signature':s,'values':bs} for s,bs in sorted(cells.items())]

def artifact(path):
    path=path.resolve()
    return {'path':str(path),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()}

def evidence(kind,f,n,attempt):
    d=here/f'{kind}-F{f}-N{n}-command-attempt{attempt:02d}'
    result=json.loads((d/'result.json').read_text())
    assert result['returncode']==0 and not result['timed_out']
    assert result['wall_seconds']<30
    assert result['peak_rss_platform_units']<512*1024*1024 # local macOS units
    observation=json.loads((d/'stdout.log').read_text())
    assert observation['status']=='PASS' and observation['F']==f and observation['N']==n
    return {'command':artifact(d/'command.json'),'result':artifact(d/'result.json'),
        'stdout':artifact(d/'stdout.log'),'stderr':artifact(d/'stderr.log'),
        'observation_not_a_source_bound':observation}

models=[]
for f,n in [(2,16),(4,16),(4,64),(4,256)]:
    protocol=part(families[:f],False);source=part(families[:f],True)
    k0,k1=len(protocol),len(source)
    u=1+k0+12*k0*k1;r=u-1;j=k0+11*k0*k1
    nodes=1+19*n+j*(n-1);arrays=1+18*n+j*(n-1)
    def memory(snode,sset,smrt,sblock):
        align=lambda s:(s+7)&~7
        q=align(snode)*nodes+align(32*sset)*arrays+align(smrt)*n
        reserve=max(8388608,1<<(q-1).bit_length())
        return {'sizeof_node':snode,'sizeof_ptrset':sset,'sizeof_mrt':smrt,'sizeof_block':sblock,
            'aligned_payload_upper_all_allocations_without_reuse':q,
            'prepared_stock_min_alloc':reserve,'setup_calloc_request':reserve+7+sblock}
    arm=memory(104,36,128,16);native=memory(128,40,128,32)
    row={'name':f'acl-branchy-F{f}-N{n}','entry':'task_dpdk_acl','F':f,'N':n,
        'partitions':{'protocol':protocol,'source_first_byte':source},'K0':k0,'K1':k1,
        'source_bounds':{'tree_unfolded_nodes':u,'merge_backcalls_per_external_root':r,
            'merge_invocations_per_external_root_including_root':r+1,
            'merge_backcalls_entire_task':r*(n-1),
            'merge_invocations_entire_task_including_6N_roots':6*n+r*(n-1),
            'nonleaf_duplicate_events_per_external_root':j,
            'nonleaf_duplicate_events_entire_task':j*(n-1),
            'node_allocation_lifetime_events':nodes,'pointer_array_allocation_events':arrays,
            'MRT_allocation_events':n,'free_invocations_entire_task':nodes,
            'free_invocations_per_recursion_nest':nodes,
            'max_live_nodes_upper_without_reuse_assumptions':nodes,
            'max_live_arrays_upper_without_reuse_assumptions':arrays,
            'max_live_MRT_upper_without_reuse_assumptions':n,
            'suggested_conservative_recurse_merge':r+1,'suggested_conservative_recurse_free':nodes,
            'active_merge_frames':14,'active_free_frames':13,
            'out_of_line_deref_active_frames_upper':13,
            'ARM_memcpy_bytes_local_upper':1152,'ARM_memset_bytes_local_upper':1152,
            'stable_num_ptrs_max':max(k0,k1),'transient_num_ptrs_upper':2*max(k0,k1)+1,
            'max_ptrs_capacity':32,'ARM_memory':arm,'native64_memory':native},
        'native':evidence('native',f,n,1),'instrumented_proof_probe':evidence('probe',f,n,1)}
    ob=row['instrumented_proof_probe']['observation_not_a_source_bound']
    assert ob['node_events']<=nodes and ob['free_events']<=nodes
    assert ob['merge_total_per_nest_max']<=r+1 and ob['free_total_per_nest_max']<=nodes
    assert ob['fresh_payload']<=native['aligned_payload_upper_all_allocations_without_reuse']
    assert row['native']['observation_not_a_source_bound']['min_alloc']==arm['prepared_stock_min_alloc']==native['prepared_stock_min_alloc']
    if n<=64:row['ASan_UBSan']=evidence('sanitize',f,n,2)
    else:row['ASan_UBSan']={'status':'NOT_RUN','reason':'Smaller profiles only, as requested.'}
    models.append(row)

bound_files=['harness.c','build.sh','proof_probe.c','build_probe.sh','make_certificate.py','README.md','BRANCHY-PROOF.md','STACK-LIVENESS.md']
shared=['compat.h','rte_log.h','portable_runtime.c','generated/acl-build-slice.inc','upstream/tb_mem.c',
    'upstream/tb_mem.h','upstream/acl.h','upstream/rte_acl.h','source-manifest.json']
data={'status':'NATIVE_DOMAIN_AND_SOURCE_BOUNDS_READY_ARM_CFG_FF_IPET_PENDING',
    'upstream':json.loads((common/'source-manifest.json').read_text()),
    'source':{'local':[artifact(here/x) for x in bound_files],'shared_unchanged':[artifact(common/x) for x in shared]},
    'domain':{'families':families,'profiles':[[2,16],[4,16],[4,64],[4,256]],
        'rule_i':{'family':'i modulo F','priority':'i+1','userdata':'i+1','category_mask':1},
        'common':{'source_remaining_24_bits':'wildcard','destination_ipv4':'192.0.2.0/24',
            'source_port':[4608,4735],'destination_port':[13312,13567]},
        'fields':5,'categories':1,'logical_byte_depth':13,
        'entry_state':'Fresh zeroed context and acyclic prepared list; stock tb_alloc(pool,0) completed before entry; single task invocation.',
        'excluded':'Earlier arbitrary broad five-tuple inputs and unary nested profile; their facts do not transfer.'},
    'interpretation':{'bounds':'Source-derived conservative upper bounds with exact integer arithmetic; not bounds fitted to observed maxima.',
        'native_probe':'Separate compiler-instrumented proof experiment, never a performance kernel.',
        'sanitizer':'ASan+UBSan PASS on F2N16/F4N16/F4N64. LeakSanitizer unavailable on local macOS. Failed detect_leaks=1 attempt01 preserved.',
        'memory':'Charge all logical allocation events including allocations serviced by caches. Ignoring reuse overestimates fresh pool payload.',
        'zero_nocall':'No nocall or FF added here; ARM binary closure and actual OTAWA constraints remain root-owned gates.'},
    'models':models}
a.out.mkdir(parents=True,exist_ok=False)
(a.out/'domain-and-proof-manifest.json').write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n')
print(json.dumps([{'profile':m['name'],'source_bounds':m['source_bounds']} for m in models]))
