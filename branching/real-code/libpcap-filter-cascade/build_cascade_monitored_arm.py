#!/usr/bin/env python3
"""Exact ARM compile recipe; scheduling belongs to the parent agent."""
from pathlib import Path
import argparse, hashlib, json, os, shutil, signal, subprocess, time

p=argparse.ArgumentParser()
p.add_argument('--out',type=Path,required=True)
p.add_argument('--compiler',default='arm-linux-gnueabi-gcc')
p.add_argument('--seconds',type=int,default=60)
p.add_argument('--profile',default='triangle')
a=p.parse_args()
root=Path(__file__).resolve().parent
src=root/'source/libpcap-libpcap-1.10.5'
out=a.out.resolve(); out.mkdir(parents=True,exist_ok=False)
cc=shutil.which(a.compiler); assert cc,a.compiler
prefix=cc[:-3]; started=time.monotonic();commands=[]
def run(label,argv):
    remaining=a.seconds-(time.monotonic()-started); assert remaining>0
    t=time.monotonic(); timed=False
    with (out/(label+'.stdout')).open('wb') as so,(out/(label+'.stderr')).open('wb') as se:
        proc=subprocess.Popen(argv,cwd=root,stdout=so,stderr=se,start_new_session=True)
        try: rc=proc.wait(timeout=remaining)
        except subprocess.TimeoutExpired:
            timed=True;os.killpg(proc.pid,signal.SIGTERM)
            try:rc=proc.wait(timeout=2)
            except subprocess.TimeoutExpired:os.killpg(proc.pid,signal.SIGKILL);rc=proc.wait()
    commands.append({'label':label,'argv':argv,'cwd':str(root),'returncode':rc,
        'timed_out':timed,'wall_seconds':time.monotonic()-t})
    (out/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
    assert rc==0 and not timed,(label,rc,timed)
    return (out/(label+'.stdout')).read_text(errors='replace')
try:
    version=run('compiler-version',[cc,'--version'])
    flags=['-O2','-g','-gdwarf-4','-std=gnu11','-march=armv5te','-marm','-mfloat-abi=soft',
        '-fno-pie','-fno-builtin','-fno-lto','-fno-optimize-sibling-calls',
        '-ffunction-sections','-fdata-sections','-fstack-usage',
        '-I'+str(root),'-I'+str(src)]
    filter_obj=out/'bpf_filter.o'; harness_obj=out/'harness.o'
    run('compile-upstream',[cc,*flags,'-c',str(src/'bpf_filter.c'),'-o',str(filter_obj)])
    run('compile-harness',[cc,*flags,'-fno-if-conversion','-fno-if-conversion2','-DSTANDALONE',
        '-DCASCADE_POLICY_INCLUDE="cascade-monitored-profiles/'+a.profile+'/policies.inc"',
        '-DCASCADE_CALLS_INCLUDE="cascade-monitored-profiles/'+a.profile+'/calls.inc"',
        '-c',str(root/'cascade_monitored_harness.c'),'-o',str(harness_obj)])
    runtime_obj=out/'counter_runtime.o'
    run('compile-counter-runtime',[cc,*flags,'-c',str(root/'counter_runtime.c'),'-o',str(runtime_obj)])
    elf=out/'kernel.elf'
    run('link',[cc,'-static','-no-pie','-march=armv5te','-marm','-mfloat-abi=soft',
        str(filter_obj),str(harness_obj),str(runtime_obj),'-Wl,--gc-sections','-Wl,-Map='+str(out/'kernel.map'),'-o',str(elf)])
    run('symbols',[prefix+'nm','-n','-S',str(elf)])
    run('disassembly',[prefix+'objdump','-d','-l',str(elf)])
    run('elf-attributes',[prefix+'readelf','-h','-A',str(elf)])
    run('sections',[prefix+'readelf','-S','-l',str(elf)])
    run('object-disassembly',[prefix+'objdump','-dr','-l',str(filter_obj)])
    result={'status':'BUILT_NOT_ADMITTED','profile':a.profile,'entry':'task_libpcap_cascade',
        'compiler':version,'elf_sha256':hashlib.sha256(elf.read_bytes()).hexdigest(),
        'upstream_commit':'bbcbc9174df3298a854daee2b3e666a4b6e5383a',
        'source_sha256':hashlib.sha256((src/'bpf_filter.c').read_bytes()).hexdigest(),
        'upstream_source_changes':0,'ARM_execution':False,'synthetic_policy':True,
        'nocall_directives':0,'FF_and_whole_machine_closure_admitted':False,
        'wall_seconds':time.monotonic()-started}
except Exception as e:
    result={'status':'FAILED','error':repr(e),'wall_seconds':time.monotonic()-started}
    (out/'result.json').write_text(json.dumps(result,indent=2)+'\n');raise
(out/'result.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result))
