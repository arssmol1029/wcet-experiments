# of-match-32-direct

Адаптация [`__of_match_node` из Linux Device Tree](https://github.com/torvalds/linux/blob/v6.12/drivers/of/base.c). Обход 32 записей развёрнут, а проверка лучшего балла перенесена внутрь ветвей трёх фиксированных рангов с сохранением первого совпадения при равенстве.

## Замеры

- OTAWA — 10,6 с
- Pathfinder — 256,71 с
- Ограничения — 587 → 4433
- WCET — 3515 → 3075

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | 11,24 с | 32,5 с |
| SCIP | 13,84 с | 69,59 с |
| FSCIP | 4,17 с | 68,38 с |
