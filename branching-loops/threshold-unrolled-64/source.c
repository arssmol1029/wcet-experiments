#include "repeat.h"
unsigned input_value; unsigned requests[64]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned x=input_value; if(x>7u) return; x=x+4u;
#define STEP(I) { unsigned i=(I); if(x<8u) heavy(); else light(); x=x+1u; }
REPEAT_64(STEP)
#undef STEP
final_state=x; }
