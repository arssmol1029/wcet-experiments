#!/usr/bin/env python3
"""Root-coordinated bounded ARM build, all upstream library sources unchanged."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import time


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--source',type=Path,required=True)
    ap.add_argument('--out',type=Path,required=True)
    ap.add_argument('--tool-prefix',default='arm-linux-gnueabi-')
    ap.add_argument('--remote-status',action='store_true')
    a=ap.parse_args();here=Path(__file__).resolve().parent;src=a.source.resolve()
    inventory=json.loads((here/'SOURCE-INVENTORY.json').read_text())
    expected={f['relative_path']:f['sha256']for f in inventory['lib_files']}
    actual={str(f.relative_to(src)):sha(f)for f in (src/'lib').rglob('*')if f.is_file()}
    assert actual==expected,'Source differs from pinned archive'
    before=None
    if a.remote_status:
        before=subprocess.run(['git','-C','/home/ahunuin/lp_benchmark','status','--short','--branch'],
            check=True,capture_output=True,text=True).stdout
    out=a.out.resolve();out.mkdir(parents=True,exist_ok=False)
    if before is not None:(out/'git-status-before.txt').write_text(before)
    snap=out/'recipe-source';snap.mkdir()
    for name in ['build_arm.py','bridge.c','arm_main.c','memory_runtime.c','abi_probe.c',
                 'source-contract.md','entropy-source-analysis.md','SOURCE-INVENTORY.json']:
        shutil.copy2(here/name,snap/name)
    manifest={'status':'BUILDING_NOT_ADMITTED','entry':'task_zstd_block','N':4096,
        'commit':inventory['commit'],'source_root':str(src),'commands':[],
        'upstream_algorithm_changes':0,'caller_renames':0,
        'source_files':[{'path':str(f),'sha256':sha(f)}for f in sorted((src/'lib').rglob('*'))if f.is_file()],
        'recipe_files':[{'path':str(f),'sha256':sha(f)}for f in sorted(snap.iterdir())]}
    def save():(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    def run(label,argv):
        start=time.monotonic()
        with(out/(label+'.stdout')).open('wb')as so,(out/(label+'.stderr')).open('wb')as se:
            r=subprocess.run([str(x)for x in argv],stdout=so,stderr=se,cwd=out,timeout=60)
        manifest['commands'].append({'label':label,'argv':[str(x)for x in argv],
            'returncode':r.returncode,'wall_seconds':time.monotonic()-start,'timeout_seconds':60});save()
        assert r.returncode==0,label
    p=a.tool_prefix
    run('gcc-version',[p+'gcc','--version'])
    flags=['-std=c99','-O2','-g','-march=armv5te','-marm','-mfloat-abi=soft','-fno-pie',
        '-ffunction-sections','-fdata-sections','-fstack-usage','-fno-tree-vectorize',
        '-fno-tree-slp-vectorize','-DZSTD_DISABLE_ASM','-DZSTD_LEGACY_SUPPORT=0',
        '-DDEBUGLEVEL=0','-Wno-deprecated-declarations','-I'+str(src/'lib')]
    manifest['compiler_flags']=flags;objects=[]
    cfiles=sorted(f for d in ['common','compress']for f in(src/'lib'/d).glob('*.c'))
    for i,f in enumerate(cfiles):
        obj=out/(f.parent.name+'-'+f.stem+'.o')
        run('compile-%02d'%i,[p+'gcc',*flags,'-c',f,'-o',obj]);objects.append(obj)
    for name in ['bridge','memory_runtime']:
        obj=out/(name+'.o')
        extra=['-fno-builtin','-fno-tree-loop-distribute-patterns']if name=='memory_runtime'else[]
        run('compile-'+name,[p+'gcc',*flags,*extra,'-c',here/(name+'.c'),'-o',obj]);objects.append(obj)
    dest=out/'n4096';dest.mkdir();elf=dest/'kernel.elf';mo=dest/'main.o'
    run('compile-main-4096',[p+'gcc',*flags,'-c',here/'arm_main.c','-o',mo])
    run('link-4096',[p+'gcc','-static','-no-pie','-march=armv5te','-marm','-mfloat-abi=soft',
        '-Wl,--gc-sections','-Wl,-Map='+str(dest/'link.map'),mo,*objects,'-o',elf])
    run('disassembly-4096',[p+'objdump','-d','-w',elf])
    run('symbols-4096',[p+'nm','-S','-n',elf])
    run('elf-metadata-4096',[p+'readelf','-h','-A','-r','-l',elf])
    run('abi-probe-compile',[p+'gcc',*flags,'-c',here/'abi_probe.c','-o',out/'abi-probe.o'])
    run('abi-probe-data',[p+'objdump','-s','-j','.rodata.zstd_block_arm_abi_values',out/'abi-probe.o'])
    manifest['profiles']=[{'N':4096,'entry':'task_zstd_block','elf':str(elf),'sha256':sha(elf)}]
    manifest['status']='BUILT_ARM_ELF_NOT_ADMITTED';save()
    print(json.dumps({'status':manifest['status'],'profiles':manifest['profiles']},indent=2))


if __name__=='__main__':main()
