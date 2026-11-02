extern void hit(unsigned);
unsigned input_value;
void benchmark_entry(void){unsigned x=input_value; switch(x){case 1: hit(1); break;case 8: hit(2); break;case 29: hit(3); break;case 64: hit(4); break;case 113: hit(5); break;case 176: hit(6); break;case 253: hit(7); break;case 344: hit(8); break;case 449: hit(9); break;case 568: hit(10); break;case 701: hit(11); break;case 848: hit(12); break;default:hit(13);} if(x<128u)hit(14);else hit(15);}
