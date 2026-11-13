import json
import math
from collections import defaultdict
import re
from html import escape
from pathlib import Path

out = Path(__file__).resolve().parent
repo = out.parent
solvers = ('HiGHS', 'SCIP', 'FSCIP')
colors = ('#235a9e', '#5488c0', '#147353', '#4a9c7d', '#7750a1', '#a17dc1')

def number(value):
    return format(value, '.15g').replace('.', ',')

def chart(file, title, modes, tasks):
    width, height, left, right, top, bottom = 1000, 510, 65, 970, 56, 344
    maximum = 1.1 * max(value for _, _, runs in tasks for value, _ in runs if value is not None)
    def y(value):
        return bottom - value / maximum * (bottom - top)
    parts = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="{width}" height="{height}" role="img"><title>{escape(title)}</title>', '<rect width="100%" height="100%" fill="white"/>', '<g font-family="Arial, sans-serif" font-size="14" fill="#182337">']
    def label(x, y, value, attrs=''):
        parts.append(f'<text x="{x}" y="{y}" {attrs}>{escape(value)}</text>')
    label(left, 31, 'Время решения, с', 'font-weight="bold"')
    unit = 10 ** math.floor(math.log10(maximum / 5))
    step = next(unit * multiplier for multiplier in (1, 2, 2.5, 5, 10) if unit * multiplier >= maximum / 5)
    for i in range(int(maximum / step) + 1):
        tick = float(f'{i * step:.8g}')
        parts.append(f'<path d="M{left} {y(tick):.2f}H{right}" stroke="#dce2eb"/>')
        label(left - 10, y(tick) + 5, number(tick), 'text-anchor="end"')
    parts.append(f'<path d="M{left} {top}V{bottom}H{right}" fill="none" stroke="#64748b"/>')
    slot = (right - left) / len(tasks)
    rotate_labels = any(len(name) * 8 > slot - 10 for name, _, _ in tasks)
    for index, (name, _, runs) in enumerate(tasks):
        center = left + (index + .5) * slot
        present = [(i, v, status) for i, (v, status) in enumerate(runs) if v is not None]
        bar = min(32, slot / 9)
        gaps = [bar / 8 if a[0]//2 == b[0]//2 else bar * .44 for a, b in zip(present, present[1:])]
        x = center - (len(present) * bar + sum(gaps)) / 2
        for j, (i, value, status) in enumerate(present):
            h = bottom - y(value)
            key = f'{name}, {solvers[i//2]}, {modes[i%2]}'
            parts.append(f'<rect x="{x}" y="{y(value):.4f}" width="{bar}" height="{h:.4f}" fill="{colors[i]}"><title>{escape(key)}, {number(value)} с ({status})</title></rect>')
            if status == 'TL':
                label(x+bar/2, y(value)-8, 'TL', 'text-anchor="middle" fill="#be142b" font-weight="bold"')
            x += bar + (gaps[j] if j < len(gaps) else 0)
        if rotate_labels:
            label(center, bottom+15, name, f'text-anchor="end" font-size="12" transform="rotate(-32 {center} {bottom+15})"')
        else:
            label(center, bottom+25, name, 'text-anchor="middle" font-weight="bold"')
    for i, color in enumerate(colors):
        x = 75 + (i//2)*304
        y_legend = 452 + (i % 2) * 23
        parts.append(f'<rect x="{x}" y="{y_legend}" width="13" height="13" rx="2" fill="{color}"/>')
        label(x+19, y_legend + 11, f'{solvers[i//2]} {modes[i%2]}', 'font-size="13"')
    (out / file).write_text('\n'.join(parts + ['</g></svg>']))

def section(title, file, modes, tasks):
    headers = [f'{solver} {mode}' for solver in solvers for mode in modes]
    lines = [f'### {title}', '', f'![Время решения по задачам — {title}](charts/{file})', '', '<details>', '<summary>Время решения и статусы</summary>', '', '| Задача | ' + ' | '.join(headers) + ' |', '|---|' + '---:|' * 6]
    for name, path, runs in tasks:
        cells = []
        for value, status in runs:
            if value is None:
                cells.append(status or '—')
            elif status == 'TL':
                cells.append(f'TL ({value} с)')
            else:
                cells.append(f'{number(value)} с · {status}')
        lines.append(f'| [{name}]({path}) | ' + ' | '.join(cells) + ' |')
    return '\n'.join(lines + ['', '</details>', ''])

SECTIONS = ('hard-lp', 'branching', 'branching-loops', 'loop-unrolling')


def natural(text):
    return tuple((1, int(chunk)) if chunk.isdigit() else (0, chunk)
                 for chunk in re.split(r'(\d+)', text))


def hard_runs(source):
    limit = int(re.search(r'^### .*TL (\d+) с', source, re.M).group(1))
    rows = {solver: (a.strip(), b.strip()) for solver, a, b in re.findall(
        r'^\| (HiGHS|SCIP|FSCIP) \| ([^|]+) \| ([^|]+) \|$', source, re.M)}
    runs = []
    for solver in solvers:
        for item in rows[solver]:
            if item == 'TL':
                runs.append((limit, 'TL'))
            elif item == '—':
                runs.append((None, None))
            else:
                runs.append((float(item.removesuffix(' с').replace(',', '.')), 'решено'))
    return runs


def json_runs(source):
    runs = []
    for solver in solvers:
        for variant in ('without_pathfinder', 'with_pathfinder'):
            data = source.get(variant) or {}
            value = (data.get('solver_seconds') or {}).get(solver.lower())
            status = (data.get('solver_status') or {}).get(solver.lower())
            runs.append((value, status or ('статус не записан' if value is not None else None)))
    return runs


def group_tasks(directory):
    groups = defaultdict(list)
    pattern = '*/*/README.md' if directory == 'hard-lp' else '**/results.json'
    for file in sorted((repo / directory).glob(pattern), key=lambda p: natural(str(p.relative_to(repo)))):
        path = file.relative_to(repo)
        name = path.parent.name
        if directory == 'hard-lp':
            family = path.parts[1]
            runs = hard_runs(file.read_text())
        else:
            if len(path.parts) == 5:
                family = path.parts[2]
                name = name.removeprefix('dml32_').removeprefix(family + '-')
            elif path.parts[1] == 'sintetic-code':
                family, name = name.split('-', 1)
            else:
                family = 'libpcap' if name.startswith('libpcap-') else name
                if family == 'libpcap':
                    name = name.removeprefix('libpcap-')
            runs = json_runs(json.loads(file.read_text()))
        groups[family].append((name, path.as_posix(), runs))
    return groups


def main():
    readme = ['# Сравнение решателей WCET', '']
    for directory in SECTIONS:
        modes = ('on', 'off') if directory == 'hard-lp' else ('без Pathfinder', 'с Pathfinder')
        readme.extend([f'## [`{directory}`]({directory}/)', ''])
        for family, tasks in sorted(group_tasks(directory).items()):
            filename = f'{directory}-{family}.svg'
            chart(filename, family, modes, tasks)
            readme.append(section(family, filename, modes, tasks))
    (repo / 'README.md').write_text('\n'.join(readme).rstrip() + '\n')


if __name__ == '__main__':
    main()
