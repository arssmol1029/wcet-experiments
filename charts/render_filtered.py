"""Render comparable unrolled Pathfinder measurements without changing README."""
from pathlib import Path
import json
from html import escape
root=Path(__file__).resolve().parent.parent
sections={
 'alternating':'branching-loops/sintetic-code/alternating-unrolled-*',
 'budget':'branching-loops/sintetic-code/budget-unrolled-*',
 'independent':'branching-loops/sintetic-code/independent-unrolled-*',
 'threshold':'branching-loops/sintetic-code/threshold-unrolled-*',
 'frr':'loop-unrolling/real-code/frr/frr-*-*',
 'pipeline':'loop-unrolling/real-code/pipeline/pipeline-*-*',
}
for family,pattern in sections.items():
 rows=[]
 for path in sorted(root.glob(pattern)):
  f=path/'results.json'; readme=path/'README.md'
  if not f.is_file() or not readme.is_file():continue
  d=json.loads(f.read_text()); v=d.get('with_pathfinder') or {}; times=v.get('solver_seconds') or {}; audit=d.get('ffx_validation') or {}
  if d.get('pathfinder_status') not in (None,'COMPLETE') or audit.get('violated_constraints',0) or not v.get('wcet'):continue
  if any(times.get(s) is None for s in ('highs','scip','fscip')):continue
  if family in ('frr','pipeline'):
   table=readme.read_text().split('| После развёртывания |')[-1].splitlines()[0]
   if 'Некорректное ограничение' in table:continue
  rows.append((path.name,[times[s] for s in ('highs','scip','fscip')]))
 if not rows:continue
 maxv=max(max(a) for _,a in rows)*1.1 or 1; width=1000; left=65; right=970; bottom=345; top=56; slot=(right-left)/len(rows)
 parts=['<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1000 510" role="img">','<rect width="100%" height="100%" fill="white"/>','<g font-family="Arial, sans-serif" font-size="14" fill="#182337">','<text x="65" y="31">Время решения, с</text>']
 colors=['#235a9e','#147353','#7750a1']
 for i in range(6):
  y=bottom-(bottom-top)*i/5; parts.append(f'<path d="M{left} {y:.2f}H{right}" stroke="#dce2eb"/><text x="55" y="{y+5:.2f}" text-anchor="end">{maxv*i/5:.3g}</text>')
 for i,(name,vals) in enumerate(rows):
  center=left+(i+.5)*slot; bar=min(32,slot/5)
  for j,v in enumerate(vals):
   h=(bottom-top)*v/maxv;x=center+(j-1.5)*bar;parts.append(f'<rect x="{x:.2f}" y="{bottom-h:.2f}" width="{bar-2:.2f}" height="{h:.2f}" fill="{colors[j]}"><title>{escape(name)}: {v} с</title></rect>')
  parts.append(f'<text x="{center:.2f}" y="{bottom+15}" text-anchor="end" font-size="11" transform="rotate(-32 {center:.2f} {bottom+15})">{escape(name)}</text>')
 for j,name in enumerate(('HiGHS','SCIP','FSCIP')): parts.append(f'<rect x="{75+j*200}" y="455" width="13" height="13" fill="{colors[j]}"/><text x="{94+j*200}" y="466">{name}</text>')
 prefix='loop-unrolling' if family in ('frr','pipeline') else 'branching-loops'; (root/'charts'/f'{prefix}-{family}.svg').write_text('\n'.join(parts+['</g></svg>']))
 print(family,len(rows))
