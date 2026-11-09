# of-match-64-direct

Адаптация [`__of_match_node` из Linux Device Tree](https://github.com/torvalds/linux/blob/v6.12/drivers/of/base.c). Обход 64 записей развёрнут, а проверка лучшего балла перенесена внутрь ветвей трёх фиксированных рангов с сохранением первого совпадения при равенстве.
