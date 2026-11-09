# pg-acl-96x12

Адаптация [`aclmask` из PostgreSQL 17.0](https://github.com/postgres/postgres/blob/REL_17_0/src/backend/utils/adt/acl.c). Оба прохода по 96 записям развёрнуты для фиксированной маски, а проверки членства читают 12 входных флагов из готового кэша.
