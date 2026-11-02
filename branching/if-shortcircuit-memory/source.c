extern void hit(unsigned);
unsigned input_value;
void benchmark_entry(void){unsigned x=input_value; if(x<128u && x>32u && (x<64u || x>96u)) hit(1); else hit(2); if(x<=32u) hit(3); else hit(4);}
