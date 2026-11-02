#include "repeat.h"
unsigned input_value; unsigned requests[32]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned x=input_value; if(x>7u) return; x=x+4u;
for(unsigned i=0u;i<32u;i=i+1u) { if(x<8u) heavy(); else light(); x=x+1u; }
final_state=x; }
