# numeric12

Синтетическая BPF-политика, скомпилированная [ARM JIT Linux 6.6](https://github.com/torvalds/linux/blob/v6.6/arch/arm/net/bpf_jit_32.c). Политика проверяет 12 входных слов, а ассемблерная обвязка подключает сохранённый JIT-образ с ациклическим графом.

## Замеры

- OTAWA — ≈ 774 с
- Pathfinder — ≈ 1173,52 с
- Ограничения — 775 → 12731
- WCET — 10285 → [7085–9097,86]

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | TL | TL |
| SCIP | TL | TL |
| FSCIP | TL | TL |
