/* Unchanged logging environment from the first probe. Valid field types and
 * the proved preallocated-pool contract make both logging sites unreachable. */
#ifndef BENCH_RTE_LOG_H
#define BENCH_RTE_LOG_H
#include <stdio.h>
#define RTE_LOG_LINE(level,type,...) do { fprintf(stderr, __VA_ARGS__); fputc('\n',stderr); } while (0)
#endif
