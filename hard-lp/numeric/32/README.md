# numeric32

Синтетическая BPF-политика, скомпилированная [ARM JIT Linux 6.6](https://github.com/torvalds/linux/blob/v6.6/arch/arm/net/bpf_jit_32.c). Политика проверяет 32 входных слов, а ассемблерная обвязка подключает сохранённый JIT-образ с ациклическим графом.

## Замеры

- OTAWA — 2685,36 с
- Pathfinder — 449,48 с
- Ограничения — 2439 → 30575
- WCET — 32405 → [22945–29445]

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | TL | TL |
| SCIP | TL | TL |
| FSCIP | TL | TL |
