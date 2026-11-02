#include "repeat.h"
unsigned input_value; unsigned requests[64]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u;
for(unsigned i=0u;i<64u;i=i+1u) { if(requests[i] != 0u) heavy(); else light(); }
final_state=0u; }
