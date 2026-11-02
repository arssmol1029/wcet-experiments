/* Ordinary monitoring API. Both bodies remain in the measured call graph. */
extern volatile unsigned cascade_accepted;
extern volatile unsigned cascade_anchor_positive[];

__attribute__((noinline)) void record_accepted(void)
{
    ++cascade_accepted;
}

__attribute__((noinline)) void record_anchor(unsigned bit)
{
    ++cascade_anchor_positive[bit];
}
