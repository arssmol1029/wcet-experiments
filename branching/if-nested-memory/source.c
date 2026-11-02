extern void hit(unsigned);
unsigned input_value;
void benchmark_entry(void){unsigned x=input_value; if(x<128u){if(x<64u){if(x<32u) hit(1); else hit(2);}else{if(x>96u) hit(3);else hit(4);}}else hit(5); if(x<32u) hit(6); else hit(7);}
