#include "repeat.h"
unsigned input_value; unsigned requests[64]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u;
#define STEP(I) { unsigned i=(I); if(requests[i] != 0u) heavy(); else light(); }
REPEAT_64(STEP)
#undef STEP
final_state=0u; }
