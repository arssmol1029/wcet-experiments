#ifndef DML32_STUDY_ENVIRONMENT_H
#define DML32_STUDY_ENVIRONMENT_H
extern volatile unsigned int study_assert_events, study_integer_div0_events;
extern volatile unsigned int study_fp_div0_events, study_fp_nonfinite_events;
extern volatile unsigned int study_log_events, study_invalid_input_events;
extern volatile unsigned int study_last_assert_line, study_main_return_code;
extern const char *volatile study_last_assert_file;
void study_reset_diagnostics(void);
int study_diagnostics_invalid(void);
#endif
