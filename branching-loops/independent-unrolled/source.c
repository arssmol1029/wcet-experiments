unsigned input_value; unsigned requests[8]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u;
{ unsigned i=0u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=1u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=2u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=3u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=4u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=5u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=6u; if(requests[i] != 0u) heavy(); else light(); }
{ unsigned i=7u; if(requests[i] != 0u) heavy(); else light(); }
final_state=0u; }
