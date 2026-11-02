#include "adapter.h"
#include "core.inc"

#ifndef BENCHMARK_PRESET_HEADER
#define BENCHMARK_PRESET_HEADER "preset3.h"
#endif
#include BENCHMARK_PRESET_HEADER

uint8_t benchmark_input[INPUT_CAP] = PRESET_INPUT_BYTES;
unsigned benchmark_input_size = PRESET_INPUT_SIZE;
wmem_array_t benchmark_output;
bool benchmark_ok;

/* Fixture generation is outside benchmark_entry and retains the reference
 * expanded bytes as an independent, simple per-byte oracle. */
uint8_t benchmark_expected[OUTPUT_CAP];
unsigned benchmark_expected_size;
static unsigned flag_offset, flag_used, half_offset;
static uint32_t flag_value;

static void put8(unsigned value)
{
    if (benchmark_input_size >= INPUT_CAP) adapter_violation();
    benchmark_input[benchmark_input_size++] = (uint8_t)value;
}
static void put16(unsigned value) { put8(value); put8(value >> 8); }
static void put32(uint32_t value) { put16(value); put16(value >> 16); }
static void flush_flags(void)
{
    for (unsigned i = 0; i < 4; ++i)
        benchmark_input[flag_offset + i] = (uint8_t)(flag_value >> (8 * i));
}
static void token_flag(bool match)
{
    if (flag_used == 32) {
        flag_offset = benchmark_input_size;
        flag_value = 0;
        flag_used = 0;
        put32(0);
    }
    if (match) flag_value |= UINT32_C(1) << (31 - flag_used);
    ++flag_used;
    flush_flags();
}
void fixture_begin(void)
{
    benchmark_input_size = 0;
    benchmark_expected_size = 0;
    flag_used = 32;
    half_offset = 0;
}
void fixture_literal(uint8_t value)
{
    token_flag(false);
    put8(value);
    benchmark_expected[benchmark_expected_size++] = value;
}
void fixture_match(unsigned offset, unsigned length, bool force32)
{
    if (!offset || offset > 8192 || length < 3) adapter_violation();
    token_flag(true);
    put16(((offset - 1) << 3) | (length <= 9 ? length - 3 : 7));
    if (length >= 10) {
        unsigned half = length <= 24 ? length - 10 : 15;
        if (!half_offset) {
            half_offset = benchmark_input_size;
            put8(half);
        } else {
            benchmark_input[half_offset] |= (uint8_t)(half << 4);
            half_offset = 0;
        }
        if (length >= 25) {
            if (length < 280 && !force32) put8(length - 25);
            else {
                put8(255);
                put16(force32 ? 0 : length - 3);
                if (force32) put32(length - 3);
            }
        }
    }
    if (offset <= benchmark_expected_size && length <= OUTPUT_CAP - benchmark_expected_size)
        for (unsigned i = 0; i < length; ++i) {
            unsigned j = benchmark_expected_size;
            benchmark_expected[j] = benchmark_expected[j - offset];
            benchmark_expected_size = j + 1;
        }
}
void fixture_end(void) { token_flag(true); }

/* Four admitted sizes; max decoded size is 64 * (4096+280+279+25+24+10+9+3)/8+1
 * = 37809, strictly below OUTPUT_CAP. Each match <=4096. */
void benchmark_init(unsigned scale)
{
    static const unsigned lengths[] = {3, 9, 10, 24, 25, 279, 280, 4096};
    unsigned count = scale == 0 ? 8 : scale == 1 ? 16 : scale == 2 ? 32 : 64;
    fixture_begin();
    fixture_literal('A');
    for (unsigned i = 0; i < count; ++i)
        fixture_match(1, lengths[i % 8], i % 8 == 7);
    fixture_end();
    benchmark_output.count = 0;
}

void benchmark_entry(void)
{
    tvbuff_t input = {benchmark_input, benchmark_input_size};
    benchmark_ok = do_uncompress(&input, 0, (int)benchmark_input_size,
                                  &benchmark_output);
}

#ifdef BENCHMARK_STANDALONE
int main(void)
{
    benchmark_entry();
    return benchmark_ok && benchmark_output.count == PRESET_OUTPUT_SIZE ? 0 : 1;
}
#endif
