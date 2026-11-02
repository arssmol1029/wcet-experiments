#!/usr/bin/env python3
"""Apply an explicitly reviewed machine-header map; reject all new headers."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import subprocess

p=argparse.ArgumentParser()
p.add_argument('--raw',type=Path,required=True)
p.add_argument('--elf',type=Path,required=True)
p.add_argument('--blocks',type=int,choices=(32,128,512),required=True)
p.add_argument('--out',type=Path,required=True)
a=p.parse_args()
a.out.mkdir(parents=True,exist_ok=False)
b=a.blocks
nw,ew=b//32+1,2*b//32+1
entries={}
def add(fn,offsets,bound,proof):
    for offset in offsets: entries[(fn,offset)]=(bound,proof)
add('memset',[0x18],max(852,96*b,4*b*nw,8*b*ew),'Counted byte clear: max of hashtbl852, vmap12B*8 and graph bit-vector capacities; n decreases by one.')
add('memcpy',[0x18],72,'Only retained copy is block.val[N_ATOMS=18] of 4-byte values; all 72 bytes are counted.')
for fn in ['__aeabi_uidivmod','__aeabi_uidiv']:
    add(fn,[0x20],32,'Portable restoring division processes bits31 down to0 exactly; divisor nonzero on valid opcode domain.')
add('find_dom',[0x18],b*nw,'Initialize B*nodewords dominator words.')
add('find_dom',[0x3c,0xa8,0xcc],nw,'Each bitset traversal consumes nodewords words.')
add('find_dom',[0x68,0x74],b,'At most B levels and B blocks in each finite level list.')
add('find_closure',[0x44,0x50],b,'At most B levels/blocks; acyclic compiler graph, unchanged level links.')
add('find_closure',[0x84,0xa8],nw,'SET_UNION loops over nodewords words.')
add('find_ud.isra.0',[0x38,0x4c,0x18c,0x198],b,'Finite levels and block lists each bounded by B.')
add('find_ud.isra.0',[0x98],3,'Exactly three original statements per nonterminal block; analysis never adds statements.')
add('find_edom',[0x28],2*b*ew,'Initialize n_edges=2B, not live-edge count, times edgewords.')
add('find_edom',[0x74,0x80],b,'At most B levels and B blocks per level list.')
add('propedom',[0x3c,0x5c],ew,'SET_INTERSECT consumes edgewords words.')
add('find_inedges',[0x24,0x50,0x5c],b,'Reset B blocks; visit at most B levels and B blocks per level.')
add('F',[0x50],12*b,'Hash chain is bounded by allocated values; upstream proves <=3*(S+B), S=3(B-2), and 12B capacity is larger.')
add('opt_blks',[0x7c,0x98],b,'Single pass: at most B levels and B blocks per level.')
add('opt_blks',[0xd8],2*(b-2),'Predecessor chains consist of the 2(B-2) live edges, built once by find_inedges.')
add('opt_blks',[0xe4,0x6b0],18,'Fixed N_ATOMS=18 register/scratch entities.')
add('opt_blks',[0x670,0x270,0x284,0x2ac,0x8e4,0x914,0xc84,0x170],3,'Statement and skip-NOP traversals advance along one of three original nodes; optimization deletes/rewrites but adds none.')

dis=subprocess.check_output(['arm-linux-gnueabi-objdump','-d','--disassemble=opt_blks',str(a.elf)],text=True)
(a.out/'opt_blks.disasm.txt').write_text(dis)
start=re.search(r'^([0-9a-f]+) <opt_blks>:',dis,re.M)
if not start: raise RuntimeError('Missing reviewed opt_blks symbol')
branch=int(start[1],16)+0x728
if not re.search(r'^\s*'+format(branch,'x')+r':\s+[0-9a-f]+\s+bne\s+',dis,re.M):
    raise RuntimeError('Reviewed do_stmts early-return branch moved; manual audit required')
raw=a.raw.read_text()
seen=set()
proofs=[]
def loop(m):
    key=(m[2],int(m[3],16))
    if key not in entries: raise RuntimeError('Unreviewed loop '+str(key))
    seen.add(key)
    bound,proof=entries[key]
    proofs.append({'function':key[0],'offset':hex(key[1]),'max':bound,'proof':proof,
                   'raw_directive':m[0]})
    # Source iteration count is a conservative backedge bound, not an asserted exact count.
    return m[1]+str(bound)+m[4]
pattern=r'(loop\s+"([^"]+)"\s*\+\s*(0x[0-9a-fA-F]+)\s+)\?(\s*;)'
ff=re.sub(pattern,loop,raw)
if seen!=set(entries): raise RuntimeError('Header set changed: '+repr(set(entries)-seen))
ff=ff.replace('recurse "find_levels_r" ? ;',f'recurse "find_levels_r" {2*b} ;')
if '?' in ff: raise RuntimeError('Unresolved flow fact remains')
ff+='\n// Proven invariant: every task call passes do_stmts=1 unchanged.\n'
ff+='ignoreseq "opt_blks" + 0x728;\nnoreturn "abort";\nnoreturn "opt_error";\n'
(a.out/'kernel.ff').write_text(ff)
(a.out/'proof.json').write_text(json.dumps({'blocks':b,'source_statements':3*(b-2),
 'live_edges':2*(b-2),'allocated_edges':2*b,'loop_bounds':'conservative local backedge maxima; source N used safely, not assumed N-1',
 'elf_sha256':hashlib.sha256(a.elf.read_bytes()).hexdigest(),
 'raw_ff_sha256':hashlib.sha256(a.raw.read_bytes()).hexdigest(),
 'recursion':{'function':'find_levels_r','max_recursive_calls_per_root':2*b,
 'proof':'Each unmarked nonterminal expands once and calls two successors. Total invocations <=1+2(B-2); repeated marked leaves immediately return.'},
 'noreturn_proof':'abort is nonreturning; opt_error longjmps, and valid LD/ADD/AND/JEQ filter domain excludes all error conditions.',
 'branch_fact':{'function':'opt_blks','offset':'0x728','fact':'ignoreseq','proof':'bench_kernel passes1; parameter preserved until this BNE; fall-through is branch movement and not part of the task.'},
 'loop_headers':proofs},indent=2)+'\n')
with (a.out/'proof.tsv').open('w') as f:
    w=csv.DictWriter(f,fieldnames=['function','offset','max','proof','raw_directive'],delimiter='\t')
    w.writeheader();w.writerows(proofs)
print(json.dumps({'elf':str(a.elf),'loops':len(proofs),'recursion_max':2*b,'ff':str(a.out/'kernel.ff')}))
