#include "repeat.h"
unsigned input_value; unsigned requests[64]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned state=input_value; if(state>1u) return;
#define STEP(I) { unsigned i=(I); if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
REPEAT_64(STEP)
#undef STEP
final_state=state; }
