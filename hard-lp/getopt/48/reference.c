#include <stddef.h>
#include <stdint.h>
unsigned char input[256], output[4096];
unsigned result, bound_failure;
struct option { const char *name; int has_arg; int *flag; int val; };
static const struct option longopts[] = {
  {(const char *)(input + 0),0,NULL,118},
  {(const char *)(input + 4),0,NULL,118},
  {(const char *)(input + 8),0,NULL,118},
  {(const char *)(input + 12),0,NULL,118},
  {(const char *)(input + 16),0,NULL,118},
  {(const char *)(input + 20),0,NULL,118},
  {(const char *)(input + 24),0,NULL,118},
  {(const char *)(input + 28),0,NULL,118},
  {(const char *)(input + 32),0,NULL,118},
  {(const char *)(input + 36),0,NULL,118},
  {(const char *)(input + 40),0,NULL,118},
  {(const char *)(input + 44),0,NULL,118},
  {(const char *)(input + 48),0,NULL,118},
  {(const char *)(input + 52),0,NULL,118},
  {(const char *)(input + 56),0,NULL,118},
  {(const char *)(input + 60),0,NULL,118},
  {(const char *)(input + 64),0,NULL,118},
  {(const char *)(input + 68),0,NULL,118},
  {(const char *)(input + 72),0,NULL,118},
  {(const char *)(input + 76),0,NULL,118},
  {(const char *)(input + 80),0,NULL,118},
  {(const char *)(input + 84),0,NULL,118},
  {(const char *)(input + 88),0,NULL,118},
  {(const char *)(input + 92),0,NULL,118},
  {(const char *)(input + 96),0,NULL,118},
  {(const char *)(input + 100),0,NULL,118},
  {(const char *)(input + 104),0,NULL,118},
  {(const char *)(input + 108),0,NULL,118},
  {(const char *)(input + 112),0,NULL,118},
  {(const char *)(input + 116),0,NULL,118},
  {(const char *)(input + 120),0,NULL,118},
  {(const char *)(input + 124),0,NULL,118},
  {(const char *)(input + 128),0,NULL,118},
  {(const char *)(input + 132),0,NULL,118},
  {(const char *)(input + 136),0,NULL,118},
  {(const char *)(input + 140),0,NULL,118},
  {(const char *)(input + 144),0,NULL,118},
  {(const char *)(input + 148),0,NULL,118},
  {(const char *)(input + 152),0,NULL,118},
  {(const char *)(input + 156),0,NULL,118},
  {(const char *)(input + 160),0,NULL,118},
  {(const char *)(input + 164),0,NULL,118},
  {(const char *)(input + 168),0,NULL,118},
  {(const char *)(input + 172),0,NULL,118},
  {(const char *)(input + 176),0,NULL,118},
  {(const char *)(input + 180),0,NULL,118},
  {(const char *)(input + 184),0,NULL,118},
  {(const char *)(input + 188),0,NULL,118},
  {(const char *)(input + 192),0,NULL,118},
  {(const char *)(input + 196),0,NULL,118},
  {(const char *)(input + 200),0,NULL,118},
  {(const char *)(input + 204),0,NULL,118},
  {(const char *)(input + 208),0,NULL,118},
  {(const char *)(input + 212),0,NULL,118},
  {(const char *)(input + 216),0,NULL,118},
  {(const char *)(input + 220),0,NULL,118},
  {(const char *)(input + 224),0,NULL,118},
  {(const char *)(input + 228),0,NULL,118},
  {(const char *)(input + 232),0,NULL,118},
  {(const char *)(input + 236),0,NULL,118},
  {(const char *)(input + 240),0,NULL,118},
  {(const char *)(input + 244),0,NULL,118},
  {(const char *)(input + 248),0,NULL,118},
  {(const char *)(input + 252),0,NULL,118},
  {NULL,0,NULL,0}
};
int benchmark_entry(void) {
    const struct option *p, *pfound = NULL;
    int indfound = -1, option_index, ambig_fallback = 0;
    for (option_index = 0; option_index < 48; ++option_index) {
        p = &longopts[option_index];
        if (input[4 * option_index] == 'a' && pfound == NULL) {
            pfound = p;
            indfound = option_index;
        }
    }
    if (ambig_fallback) return 255;
    return indfound + 1;
}
