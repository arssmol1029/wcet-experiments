extern void hit(unsigned);
unsigned input_value;
void benchmark_entry(void){unsigned x=input_value; switch(x){case 0: hit(1); break;case 1: hit(2); break;case 2: hit(3); break;case 3: hit(4); break;case 4: hit(5); break;case 5: hit(6); break;case 6: hit(7); break;case 7: hit(8); break;case 8: hit(9); break;case 9: hit(10); break;case 10: hit(11); break;case 11: hit(12); break;default:hit(13);} if(x<6u)hit(14);else hit(15);}
