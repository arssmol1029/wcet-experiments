# numeric8

Синтетическая BPF-политика, скомпилированная [ARM JIT Linux 6.6](https://github.com/torvalds/linux/blob/v6.6/arch/arm/net/bpf_jit_32.c). Политика проверяет 8 входных слов, а ассемблерная обвязка подключает сохранённый JIT-образ с ациклическим графом.
