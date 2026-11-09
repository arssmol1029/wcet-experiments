# getopt-alias-96

Адаптация [`process_long_option` из glibc 2.40](https://github.com/bminor/glibc/blob/glibc-2.40/posix/getopt.c). Проверки 96 имён развёрнуты для фиксированного односимвольного сокращения, при этом сохранены выбор первого совпадения и проверка неоднозначности.
