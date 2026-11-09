# Трудные LP-модели для IPET

В наборе 16 полных моделей с автоматическим FFX и 61 сохранённый прогон решателей.
[Сводка профилей](profiles.tsv) содержит происхождение, оптимумы или интервалы, SHA-256 и время Pathfinder и экспорта.
[Таблица прогонов](runs.tsv) содержит настройки presolve, время, число узлов, статусы и границы.

Целевые значения приведены в единицах модели стоимости OTAWA. Времена прогонов относятся к указанным этапам и получены в разных средах.
Критерий трудности учитывает либо не менее 60 секунд и 1000 узлов, либо достижение лимита после ветвления с проверенным решением и открытым разрывом.
Прочие варианты сохранены для изучения численной трудности и сравнения размеров.

| Семейство | Вариант | Полный LP | Группа |
|---|---|---|---|
| `frr` | [16](frr/16/README.md) | [model.lp](frr/16/model.lp) | Контрольный размер |
| `frr` | [64](frr/64/README.md) | [model.lp](frr/64/model.lp) | Прошёл порог трудности |
| `lookup` | [64](lookup/64/README.md) | [model.lp](lookup/64/model.lp) | Прошёл порог трудности |
| `lookup` | [128](lookup/128/README.md) | [model.lp](lookup/128/model.lp) | Прошёл порог трудности |
| `numeric` | [8](numeric/8/README.md) | [model.lp](numeric/8/model.lp) | Прошёл порог трудности |
| `numeric` | [12](numeric/12/README.md) | [model.lp](numeric/12/model.lp) | Прошёл порог трудности |
| `numeric` | [32](numeric/32/README.md) | [model.lp](numeric/32/model.lp) | Прошёл порог трудности |
| `getopt` | [32](getopt/32/README.md) | [model.lp](getopt/32/model.lp) | Контрольный размер |
| `getopt` | [64](getopt/64/README.md) | [model.lp](getopt/64/model.lp) | Контрольный размер |
| `getopt` | [96](getopt/96/README.md) | [model.lp](getopt/96/model.lp) | Прошёл порог трудности |
| `of-match` | [32](of-match/32/README.md) | [model.lp](of-match/32/model.lp) | Контрольный размер |
| `of-match` | [48](of-match/48/README.md) | [model.lp](of-match/48/model.lp) | Контрольный размер |
| `of-match` | [64](of-match/64/README.md) | [model.lp](of-match/64/model.lp) | Прошёл порог трудности |
| `zlib` | [40x6](zlib/40x6/README.md) | [model.lp](zlib/40x6/model.lp) | Численно трудный профиль |
| `zlib` | [56x6](zlib/56x6/README.md) | [model.lp](zlib/56x6/model.lp) | Численно трудный профиль |
| `pg-acl` | [96x12](pg-acl/96x12/README.md) | [model.lp](pg-acl/96x12/model.lp) | Численно трудный профиль |
