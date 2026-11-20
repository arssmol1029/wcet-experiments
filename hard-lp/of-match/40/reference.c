#include <stddef.h>
#include <stdint.h>
#define INT_MAX_VALUE 2147483647
unsigned char input[384], output[4096];
unsigned result, bound_failure;
struct of_device_id { const char *name, *type, *compatible; };
struct device_node { const char *compatible[3]; };
static const struct of_device_id table[]={
 {"","",(const char*)input+0},
 {"","",(const char*)input+8},
 {"","",(const char*)input+16},
 {"","",(const char*)input+24},
 {"","",(const char*)input+32},
 {"","",(const char*)input+40},
 {"","",(const char*)input+48},
 {"","",(const char*)input+56},
 {"","",(const char*)input+64},
 {"","",(const char*)input+72},
 {"","",(const char*)input+80},
 {"","",(const char*)input+88},
 {"","",(const char*)input+96},
 {"","",(const char*)input+104},
 {"","",(const char*)input+112},
 {"","",(const char*)input+120},
 {"","",(const char*)input+128},
 {"","",(const char*)input+136},
 {"","",(const char*)input+144},
 {"","",(const char*)input+152},
 {"","",(const char*)input+160},
 {"","",(const char*)input+168},
 {"","",(const char*)input+176},
 {"","",(const char*)input+184},
 {"","",(const char*)input+192},
 {"","",(const char*)input+200},
 {"","",(const char*)input+208},
 {"","",(const char*)input+216},
 {"","",(const char*)input+224},
 {"","",(const char*)input+232},
 {"","",(const char*)input+240},
 {"","",(const char*)input+248},
 {"","",(const char*)input+256},
 {"","",(const char*)input+264},
 {"","",(const char*)input+272},
 {"","",(const char*)input+280},
 {"","",(const char*)input+288},
 {"","",(const char*)input+296},
 {"","",(const char*)input+304},
 {"","",(const char*)input+312},
 {"","",(const char*)input+320},
 {"","",(const char*)input+328},
 {"","",(const char*)input+336},
 {"","",(const char*)input+344},
 {"","",(const char*)input+352},
 {"","",(const char*)input+360},
 {"","",(const char*)input+368},
 {"","",(const char*)input+376},
 {"","",""}
};

static __attribute__((always_inline)) inline int compatible_score(unsigned char key) {
    if (key=='a') return INT_MAX_VALUE/2;
    if (key=='b') return INT_MAX_VALUE/2 - 4;
    if (key=='c') return INT_MAX_VALUE/2 - 8;
    return 0;
}
int benchmark_entry(void) {
    const struct of_device_id *best_match = NULL;
    const struct of_device_id *matches;
    int score, best_score=0;

    for (int i = 0; i < 40; ++i) {
        matches = &table[i];
        score = compatible_score(input[8*i+5]);
        if (score > best_score) { best_match = matches; best_score = score; }
    }
    return best_match ? (int)(best_match-table)+1 : 0;
}
