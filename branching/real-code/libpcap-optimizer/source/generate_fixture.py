#!/usr/bin/env python3
"""Emit a real classic-BPF OR filter DAG, with static ARM-safe pointers."""
import argparse
import hashlib
import json
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--blocks', type=int, choices=(32, 128, 512), required=True)
p.add_argument('--out', type=Path, required=True)
a = p.parse_args()
n = a.blocks
tests = n - 2
nw, ew = n // 32 + 1, 2 * n // 32 + 1
rows = ['/* Generated harness input; upstream optimizer remains unchanged. */',
        f'#define CASE_BLOCKS {n}', f'#define CASE_TESTS {tests}',
        f'#define CASE_NODEWORDS {nw}', f'#define CASE_EDGEWORDS {ew}',
        f'#define CASE_MAXVAL {12*n}',
        'static struct block fixture_blocks[CASE_BLOCKS];',
        'static struct slist fixture_stmts[CASE_TESTS][3] = {']
for i in range(tests):
    rows.append(f'[{i}] = {{{{.s={{.code=BPF_LD|BPF_H|BPF_ABS,.k=0}},.next=&fixture_stmts[{i}][1]}},'
                f'{{.s={{.code=BPF_ALU|BPF_ADD|BPF_K,.k={i%16}}},.next=&fixture_stmts[{i}][2]}},'
                f'{{.s={{.code=BPF_ALU|BPF_AND|BPF_K,.k=65535}}}}}},')
rows += ['};', 'static bpf_u_int32 fixture_dom[CASE_BLOCKS][CASE_NODEWORDS];',
         'static bpf_u_int32 fixture_closure[CASE_BLOCKS][CASE_NODEWORDS];',
         'static bpf_u_int32 fixture_edom[2*CASE_BLOCKS][CASE_EDGEWORDS];',
         'static struct block fixture_blocks[CASE_BLOCKS] = {']
for i in range(n):
    common = (f'.id={i},.dom=fixture_dom[{i}],.closure=fixture_closure[{i}],'
              f'.et={{.id={i},.pred=&fixture_blocks[{i}],.edom=fixture_edom[{i}]')
    if i < tests:
        rows.append(f'[{i}]={{{common},.succ=&fixture_blocks[{tests}]}},'
                    f'.ef={{.id={n+i},.pred=&fixture_blocks[{i}],.edom=fixture_edom[{n+i}],'
                    f'.succ=&fixture_blocks[{i+1 if i+1<tests else n-1}]}},.stmts=fixture_stmts[{i}],'
                    f'.s={{.code=BPF_JMP|BPF_JEQ|BPF_K,.k={257*i+7}}}}},')
    else:
        rows.append(f'[{i}]={{{common}}},.ef={{.id={n+i},.pred=&fixture_blocks[{i}],'
                    f'.edom=fixture_edom[{n+i}]}},.s={{.code=BPF_RET|BPF_K,.k={65535 if i==tests else 0}}}}},')
rows += ['};', 'static struct block *fixture_block_ptrs[CASE_BLOCKS] = {']
rows += [f'&fixture_blocks[{i}],' for i in range(n)]
rows += ['};', 'static struct edge *fixture_edge_ptrs[2*CASE_BLOCKS] = {']
rows += [f'&fixture_blocks[{i}].et,' for i in range(n)]
rows += [f'&fixture_blocks[{i}].ef,' for i in range(n)]
rows += ['};', 'static struct block *fixture_levels[CASE_BLOCKS];',
         'static struct vmapinfo fixture_vmap[CASE_MAXVAL];',
         'static struct valnode fixture_vnodes[CASE_MAXVAL];',
         'static struct icode fixture_ic = {.root=fixture_blocks,.cur_mark=0};',
         'static opt_state_t fixture_state = {',
         '.n_blocks=CASE_BLOCKS,.blocks=fixture_block_ptrs,.n_edges=2*CASE_BLOCKS,',
         '.edges=fixture_edge_ptrs,.nodewords=CASE_NODEWORDS,.edgewords=CASE_EDGEWORDS,',
         '.levels=fixture_levels,.all_dom_sets=&fixture_dom[0][0],',
         '.all_closure_sets=&fixture_closure[0][0],.all_edge_sets=&fixture_edom[0][0],',
         '.maxval=CASE_MAXVAL,.vmap=fixture_vmap,.vnode_base=fixture_vnodes',
         '};']
a.out.mkdir(parents=True, exist_ok=True)
text='\n'.join(rows)+'\n'
(a.out/'fixture.h').write_text(text)
filters=' or '.join(f'((ether[0:2] + {i%16}) & 65535) = {257*i+7}' for i in range(tests))
(a.out/'filter.txt').write_text(filters+'\n')
(a.out/'fixture.json').write_text(json.dumps({'blocks':n,'tests':tests,'statements':3*tests,
 'edges':2*tests,'max_value_nodes':12*n,'fixture_sha256':hashlib.sha256(text.encode()).hexdigest(),
 'domain':'classic BPF acyclic OR DAG; packet >=2 bytes; scratch memory unused',
 'origin':'harness IR for the recorded valid libpcap filter expression'},indent=2)+'\n')
print(a.out)
