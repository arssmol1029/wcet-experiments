unsigned input_value; unsigned requests[8]; volatile unsigned sink; unsigned final_state;
void light(void); void medium(void); void heavy(void);
void benchmark_entry(void) { sink=0u; final_state=0u; unsigned x=input_value; if(x>7u) return; x=x+4u;
{ unsigned i=0u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=1u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=2u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=3u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=4u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=5u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=6u; if(x<8u) heavy(); else light(); x=x+1u; }
{ unsigned i=7u; if(x<8u) heavy(); else light(); x=x+1u; }
final_state=x; }
