unsigned input_value; unsigned requests[8]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned state=input_value; if(state>1u) return;
for(unsigned i=0u;i<8u;i=i+1u) { if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
final_state=state; }
