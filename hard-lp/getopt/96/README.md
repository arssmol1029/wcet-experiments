# getopt-alias-96

Адаптация [`process_long_option` из glibc 2.40](https://github.com/bminor/glibc/blob/glibc-2.40/posix/getopt.c). Проверки 96 имён развёрнуты для фиксированного односимвольного сокращения, при этом сохранены выбор первого совпадения и проверка неоднозначности.

## Замеры

- OTAWA — 3,47 с
- Pathfinder — 143,08 с
- Ограничения — 589 → 2715
- WCET — 7295 → 5695

### Решение ЛП модели, TL 1800 с

| Решатель | Presolve on | Presolve off |
|---|---|---|
| HiGHS | 138,09 с | 998,16 с |
| SCIP | TL | TL |
| FSCIP | TL | TL |
