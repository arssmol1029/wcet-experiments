#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "harness.c"
static unsigned scenarios;
static void verify(void)
{
    benchmark_output.count = 0;
    benchmark_entry();
    assert(benchmark_ok);
    assert(benchmark_output.count == benchmark_expected_size);
    assert(memcmp(benchmark_output.data, benchmark_expected, benchmark_expected_size) == 0);
    ++scenarios;
}
int main(void)
{
    /* Check the ELF .data/BSS state before calling any initializer. */
    assert(benchmark_input_size == PRESET_INPUT_SIZE);
    assert(benchmark_output.count == 0);
    benchmark_entry();
    assert(benchmark_ok && benchmark_output.count == PRESET_OUTPUT_SIZE);
    for (unsigned i = 0; i < benchmark_output.count; ++i)
        assert(benchmark_output.data[i] == 'A');
    ++scenarios;
    for (unsigned n = 1; n <= 65; ++n) {
        fixture_begin();
        for (unsigned i = 0; i < n; ++i) fixture_literal((uint8_t)(i * 37));
        fixture_end(); verify();
    }
    fixture_begin(); fixture_literal('A'); fixture_match(1, 6, false); fixture_end(); verify();
    fixture_begin(); fixture_literal('A'); fixture_literal('B'); fixture_literal('C');
    fixture_match(3, 9, false); fixture_end(); verify();
    fixture_begin(); fixture_literal('x'); fixture_literal('y');
    fixture_match(2, 10, false); fixture_match(2, 24, false); fixture_end(); verify();
    const unsigned lengths[] = {25, 26, 279, 280, 4096};
    for (unsigned i = 0; i < sizeof(lengths) / sizeof(*lengths); ++i) {
        fixture_begin(); fixture_literal('K'); fixture_match(1, lengths[i], i == 4);
        fixture_end(); verify();
    }
    for (unsigned scale = 0; scale < 4; ++scale) {
        benchmark_init(scale); verify();
    }
    fixture_begin(); fixture_literal('A'); fixture_match(2, 3, false); fixture_end();
    benchmark_output.count = 0; benchmark_entry(); assert(!benchmark_ok); ++scenarios;
    fixture_begin(); fixture_literal('A'); fixture_match(1, MAX_INPUT_SIZE + 4u, true); fixture_end();
    benchmark_output.count = 0; benchmark_entry(); assert(!benchmark_ok); ++scenarios;
    tvbuff_t empty = {benchmark_input, 0};
    benchmark_output.count = 0;
    assert(!do_uncompress(NULL, 0, 1, &benchmark_output));
    assert(!do_uncompress(&empty, 0, 0, &benchmark_output));
    scenarios += 2;
    printf("PASS: %u scenarios; exact bytes; overlap; flag boundaries; shared nibble; 8/16/32-bit lengths; invalid offset; max-length reject\n", scenarios);
    return 0;
}
