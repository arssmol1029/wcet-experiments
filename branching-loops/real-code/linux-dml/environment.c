/* Explicit finite environment. No allocation, libc, traps or hidden calls. */
#include "environment.h"
volatile unsigned int study_assert_events, study_integer_div0_events;
volatile unsigned int study_fp_div0_events, study_fp_nonfinite_events;
volatile unsigned int study_log_events, study_invalid_input_events;
volatile unsigned int study_last_assert_line, study_main_return_code;
const char *volatile study_last_assert_file;
void study_reset_diagnostics(void)
{
    study_assert_events=study_integer_div0_events=0;
    study_fp_div0_events=study_fp_nonfinite_events=0;
    study_log_events=study_invalid_input_events=0;
    study_last_assert_line=study_main_return_code=0;
    study_last_assert_file=0;
}
int study_diagnostics_invalid(void)
{
    return study_assert_events || study_integer_div0_events || study_fp_div0_events ||
           study_fp_nonfinite_events || study_invalid_input_events;
}
void dml_environment_assert_fail(const char *file, unsigned int line)
{
    study_assert_events++;
    study_last_assert_file=file;
    study_last_assert_line=line;
}
void dml_environment_log(const char *format, ...)
{
    (void)format;
    study_log_events++;
}
int __aeabi_idiv0(int value)
{
    study_integer_div0_events++;
    return value;
}
long long __aeabi_ldiv0(long long value)
{
    study_integer_div0_events++;
    return value;
}
