# of-match-32-direct

Адаптация [`__of_match_node` из Linux Device Tree](https://github.com/torvalds/linux/blob/v6.12/drivers/of/base.c). Обход 32 записей развёрнут, а проверка лучшего балла перенесена внутрь ветвей трёх фиксированных рангов с сохранением первого совпадения при равенстве.
