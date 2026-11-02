unsigned input_value; unsigned requests[8]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned state=input_value; if(state>1u) return;
{ unsigned i=0u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=1u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=2u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=3u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=4u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=5u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=6u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
{ unsigned i=7u; if(state==0u) { heavy(); state=1u; } else { light(); state=0u; } }
final_state=state; }
