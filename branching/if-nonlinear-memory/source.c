extern void hit(unsigned);
unsigned input_value;
void benchmark_entry(void){unsigned x=input_value; if(x*x+3u*x+7u<100u) hit(1); else hit(2); if(x*x+3u*x+7u>=100u) hit(3); else hit(4);}
