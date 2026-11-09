# of-match-64-direct

Адаптация [`__of_match_node` из Linux Device Tree](https://github.com/torvalds/linux/blob/v6.12/drivers/of/base.c). Обход 64 записей развёрнут, а проверка лучшего балла перенесена внутрь ветвей трёх фиксированных рангов с сохранением первого совпадения при равенстве.

## Замеры

- OTAWA — 38,59 с
- Pathfinder — 556,76 с
- Ограничения — 1163 → 9113
- WCET — 6875 → 5995

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | 205,6 с | TL |
| SCIP | 183,14 с | 755,87 с |
| FSCIP | 113,18 с | TL |
