/* Bounded real-data/array environment for the unchanged Wireshark core.
 * License of core.inc remains GPL-2.0-or-later. No dynamic allocation. */
#ifndef LZ77_BOUNDED_ADAPTER_H
#define LZ77_BOUNDED_ADAPTER_H
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#define INPUT_CAP 4096u
#define OUTPUT_CAP 65536u
typedef struct { const uint8_t *data; unsigned length; } tvbuff_t;
typedef struct { uint8_t data[OUTPUT_CAP]; unsigned count; } wmem_array_t;

/* These checked violations are OUTSIDE the admitted corpus domain. Unlike
 * Wireshark this adapter traps rather than entering the exception runtime.
 * Valid real-data accesses and arrays with proven spare capacity are exact. */
static void adapter_violation(void) { __builtin_trap(); }
static uint8_t tvb_get_uint8(tvbuff_t *tvb, int offset)
{
    if (offset < 0 || (unsigned)offset >= tvb->length)
        adapter_violation();
    return tvb->data[(unsigned)offset];
}
static uint16_t tvb_get_letohs(tvbuff_t *tvb, int offset)
{
    return (uint16_t)(tvb_get_uint8(tvb, offset) |
                      ((uint16_t)tvb_get_uint8(tvb, offset + 1) << 8));
}
static uint32_t tvb_get_letohl(tvbuff_t *tvb, int offset)
{
    return (uint32_t)tvb_get_uint8(tvb, offset) |
           ((uint32_t)tvb_get_uint8(tvb, offset + 1) << 8) |
           ((uint32_t)tvb_get_uint8(tvb, offset + 2) << 16) |
           ((uint32_t)tvb_get_uint8(tvb, offset + 3) << 24);
}
static unsigned wmem_array_get_count(const wmem_array_t *array)
{
    return array->count;
}
static bool wmem_array_try_index(const wmem_array_t *array, unsigned index,
                                 uint8_t *value)
{
    if (index >= array->count)
        return true;
    *value = array->data[index];
    return false;
}
static void wmem_array_append_one(wmem_array_t *array, uint8_t value)
{
    if (array->count >= OUTPUT_CAP)
        adapter_violation();
    array->data[array->count++] = value;
}
#endif
