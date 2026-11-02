#ifndef STUDY_DML_SERVICES_H
#define STUDY_DML_SERVICES_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
typedef unsigned int uint;
struct dal_logger;
void dml_environment_assert_fail(const char *, unsigned int);
void dml_environment_log(const char *, ...);
#define ASSERT(condition) do { if (!(condition)) dml_environment_assert_fail(__FILE__, __LINE__); } while (0)
#define DC_LOG_DML(...) dml_environment_log(__VA_ARGS__)
#endif
