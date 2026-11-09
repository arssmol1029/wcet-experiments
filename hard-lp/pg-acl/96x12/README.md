# pg-acl-96x12

Адаптация [`aclmask` из PostgreSQL 17.0](https://github.com/postgres/postgres/blob/REL_17_0/src/backend/utils/adt/acl.c). Оба прохода по 96 записям развёрнуты для фиксированной маски, а проверки членства читают 12 входных флагов из готового кэша.

## Замеры

- OTAWA — 2504,02 с
- Pathfinder — 257,16 с
- Ограничения — 955 → 7785
- WCET — 8590 → 3890

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | 18,68 с | 65,71 с |
| SCIP | 221,52 с | 106,45 с |
| FSCIP | 105,16 с | 25,83 с |
