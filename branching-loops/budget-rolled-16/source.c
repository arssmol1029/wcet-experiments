#include "repeat.h"
unsigned input_value; unsigned requests[16]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned budget=5u;
for(unsigned i=0u;i<16u;i=i+1u) { switch(requests[i]) { case 2u: if(budget>=2u) { budget=budget-2u; heavy(); } /* fall through */ case 1u: if(budget>=1u) { budget=budget-1u; medium(); } break; default: light(); break; } }
final_state=budget; }
