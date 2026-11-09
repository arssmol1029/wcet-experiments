
unsigned input[64];
unsigned char output[4096];
unsigned result, bound_failure;

unsigned benchmark_entry(void) {
    unsigned held = 0, remaining;
    held |= 1U;
    if (held == 63U) return held;
    held |= 1U;
    if (held == 63U) return held;
    remaining = 63U & ~held;
    if ((16U & remaining) && input[11]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((36U & remaining) && input[9]) {
        held |= 36U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[3]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[2]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[11]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[1]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[7]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[5]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[5]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[8]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((36U & remaining) && input[7]) {
        held |= 36U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[9]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[1]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[6]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[5]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((12U & remaining) && input[9]) {
        held |= 12U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[3]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[0]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[9]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[1]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((10U & remaining) && input[9]) {
        held |= 10U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[11]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[5]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[9]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[9]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[4]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[4]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((34U & remaining) && input[9]) {
        held |= 34U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((12U & remaining) && input[4]) {
        held |= 12U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((18U & remaining) && input[10]) {
        held |= 18U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((10U & remaining) && input[3]) {
        held |= 10U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[8]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[11]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[6]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[3]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[10]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((10U & remaining) && input[0]) {
        held |= 10U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[11]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[0]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((18U & remaining) && input[4]) {
        held |= 18U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((36U & remaining) && input[10]) {
        held |= 36U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[9]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((10U & remaining) && input[3]) {
        held |= 10U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[10]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[5]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[1]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[6]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((34U & remaining) && input[6]) {
        held |= 34U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((34U & remaining) && input[1]) {
        held |= 34U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[10]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[0]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[3]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((18U & remaining) && input[2]) {
        held |= 18U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[9]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[1]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[3]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[10]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[8]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[10]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[5]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((6U & remaining) && input[1]) {
        held |= 6U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[5]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[5]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[7]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[4]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[0]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[8]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[7]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[2]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((36U & remaining) && input[10]) {
        held |= 36U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[0]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[1]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[2]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[2]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[0]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[9]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[1]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((2U & remaining) && input[9]) {
        held |= 2U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[5]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[5]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((8U & remaining) && input[0]) {
        held |= 8U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[11]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((18U & remaining) && input[9]) {
        held |= 18U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((32U & remaining) && input[4]) {
        held |= 32U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((24U & remaining) && input[0]) {
        held |= 24U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((16U & remaining) && input[9]) {
        held |= 16U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((12U & remaining) && input[5]) {
        held |= 12U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((18U & remaining) && input[11]) {
        held |= 18U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((20U & remaining) && input[5]) {
        held |= 20U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((20U & remaining) && input[10]) {
        held |= 20U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((40U & remaining) && input[7]) {
        held |= 40U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((4U & remaining) && input[8]) {
        held |= 4U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((48U & remaining) && input[8]) {
        held |= 48U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    if ((48U & remaining) && input[8]) {
        held |= 48U;
        if (held == 63U) return held;
        remaining = 63U & ~held;
    }
    return held;
}
