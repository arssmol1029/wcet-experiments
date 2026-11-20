
unsigned input[64];
unsigned char output[4096];
unsigned result, bound_failure;

static const struct { unsigned mask; unsigned index; } rules[62] = {
    {16U, 11U},
    {36U, 9U},
    {16U, 3U},
    {16U, 2U},
    {8U, 11U},
    {32U, 1U},
    {32U, 7U},
    {2U, 5U},
    {8U, 5U},
    {2U, 8U},
    {36U, 7U},
    {16U, 9U},
    {8U, 1U},
    {8U, 6U},
    {24U, 5U},
    {12U, 9U},
    {16U, 3U},
    {8U, 0U},
    {8U, 9U},
    {8U, 1U},
    {10U, 9U},
    {8U, 11U},
    {2U, 5U},
    {2U, 9U},
    {16U, 9U},
    {8U, 4U},
    {8U, 4U},
    {34U, 9U},
    {12U, 4U},
    {18U, 10U},
    {10U, 3U},
    {32U, 8U},
    {8U, 11U},
    {4U, 6U},
    {4U, 3U},
    {16U, 10U},
    {10U, 0U},
    {2U, 11U},
    {32U, 0U},
    {18U, 4U},
    {36U, 10U},
    {2U, 9U},
    {10U, 3U},
    {16U, 10U},
    {2U, 5U},
    {24U, 1U},
    {32U, 6U},
    {34U, 6U},
    {34U, 1U},
    {32U, 10U},
    {4U, 0U},
    {4U, 3U},
    {18U, 2U},
    {32U, 9U},
    {4U, 1U},
    {8U, 3U},
    {16U, 10U},
    {16U, 8U},
    {4U, 10U},
    {16U, 5U},
    {6U, 1U},
    {32U, 5U},
};
unsigned benchmark_entry(void) {
    unsigned held = 0, remaining;
    held |= 1U;
    if (held == 63U) return held;
    held |= 1U;
    if (held == 63U) return held;
    remaining = 63U & ~held;
    for (unsigned i=0; i<62; ++i) {
        unsigned mask = rules[i].mask;
        if ((mask & remaining) && input[rules[i].index]) {
            held |= mask;
            if (held == 63U) return held;
            remaining = 63U & ~held;
        }
    }
    return held;
}
