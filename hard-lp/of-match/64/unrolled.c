#include <stddef.h>
#include <stdint.h>
#define INT_MAX_VALUE 2147483647
unsigned char input[512], output[4096];
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
 {"","",(const char*)input+384},
 {"","",(const char*)input+392},
 {"","",(const char*)input+400},
 {"","",(const char*)input+408},
 {"","",(const char*)input+416},
 {"","",(const char*)input+424},
 {"","",(const char*)input+432},
 {"","",(const char*)input+440},
 {"","",(const char*)input+448},
 {"","",(const char*)input+456},
 {"","",(const char*)input+464},
 {"","",(const char*)input+472},
 {"","",(const char*)input+480},
 {"","",(const char*)input+488},
 {"","",(const char*)input+496},
 {"","",(const char*)input+504},
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

    if (input[5] == 'a') {
        matches=&table[0];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[5] == 'b') {
        matches=&table[0];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[5] == 'c') {
        matches=&table[0];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[13] == 'a') {
        matches=&table[1];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[13] == 'b') {
        matches=&table[1];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[13] == 'c') {
        matches=&table[1];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[21] == 'a') {
        matches=&table[2];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[21] == 'b') {
        matches=&table[2];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[21] == 'c') {
        matches=&table[2];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[29] == 'a') {
        matches=&table[3];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[29] == 'b') {
        matches=&table[3];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[29] == 'c') {
        matches=&table[3];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[37] == 'a') {
        matches=&table[4];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[37] == 'b') {
        matches=&table[4];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[37] == 'c') {
        matches=&table[4];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[45] == 'a') {
        matches=&table[5];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[45] == 'b') {
        matches=&table[5];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[45] == 'c') {
        matches=&table[5];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[53] == 'a') {
        matches=&table[6];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[53] == 'b') {
        matches=&table[6];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[53] == 'c') {
        matches=&table[6];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[61] == 'a') {
        matches=&table[7];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[61] == 'b') {
        matches=&table[7];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[61] == 'c') {
        matches=&table[7];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[69] == 'a') {
        matches=&table[8];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[69] == 'b') {
        matches=&table[8];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[69] == 'c') {
        matches=&table[8];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[77] == 'a') {
        matches=&table[9];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[77] == 'b') {
        matches=&table[9];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[77] == 'c') {
        matches=&table[9];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[85] == 'a') {
        matches=&table[10];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[85] == 'b') {
        matches=&table[10];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[85] == 'c') {
        matches=&table[10];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[93] == 'a') {
        matches=&table[11];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[93] == 'b') {
        matches=&table[11];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[93] == 'c') {
        matches=&table[11];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[101] == 'a') {
        matches=&table[12];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[101] == 'b') {
        matches=&table[12];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[101] == 'c') {
        matches=&table[12];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[109] == 'a') {
        matches=&table[13];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[109] == 'b') {
        matches=&table[13];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[109] == 'c') {
        matches=&table[13];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[117] == 'a') {
        matches=&table[14];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[117] == 'b') {
        matches=&table[14];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[117] == 'c') {
        matches=&table[14];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[125] == 'a') {
        matches=&table[15];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[125] == 'b') {
        matches=&table[15];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[125] == 'c') {
        matches=&table[15];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[133] == 'a') {
        matches=&table[16];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[133] == 'b') {
        matches=&table[16];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[133] == 'c') {
        matches=&table[16];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[141] == 'a') {
        matches=&table[17];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[141] == 'b') {
        matches=&table[17];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[141] == 'c') {
        matches=&table[17];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[149] == 'a') {
        matches=&table[18];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[149] == 'b') {
        matches=&table[18];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[149] == 'c') {
        matches=&table[18];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[157] == 'a') {
        matches=&table[19];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[157] == 'b') {
        matches=&table[19];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[157] == 'c') {
        matches=&table[19];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[165] == 'a') {
        matches=&table[20];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[165] == 'b') {
        matches=&table[20];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[165] == 'c') {
        matches=&table[20];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[173] == 'a') {
        matches=&table[21];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[173] == 'b') {
        matches=&table[21];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[173] == 'c') {
        matches=&table[21];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[181] == 'a') {
        matches=&table[22];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[181] == 'b') {
        matches=&table[22];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[181] == 'c') {
        matches=&table[22];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[189] == 'a') {
        matches=&table[23];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[189] == 'b') {
        matches=&table[23];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[189] == 'c') {
        matches=&table[23];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[197] == 'a') {
        matches=&table[24];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[197] == 'b') {
        matches=&table[24];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[197] == 'c') {
        matches=&table[24];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[205] == 'a') {
        matches=&table[25];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[205] == 'b') {
        matches=&table[25];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[205] == 'c') {
        matches=&table[25];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[213] == 'a') {
        matches=&table[26];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[213] == 'b') {
        matches=&table[26];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[213] == 'c') {
        matches=&table[26];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[221] == 'a') {
        matches=&table[27];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[221] == 'b') {
        matches=&table[27];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[221] == 'c') {
        matches=&table[27];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[229] == 'a') {
        matches=&table[28];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[229] == 'b') {
        matches=&table[28];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[229] == 'c') {
        matches=&table[28];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[237] == 'a') {
        matches=&table[29];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[237] == 'b') {
        matches=&table[29];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[237] == 'c') {
        matches=&table[29];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[245] == 'a') {
        matches=&table[30];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[245] == 'b') {
        matches=&table[30];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[245] == 'c') {
        matches=&table[30];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[253] == 'a') {
        matches=&table[31];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[253] == 'b') {
        matches=&table[31];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[253] == 'c') {
        matches=&table[31];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[261] == 'a') {
        matches=&table[32];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[261] == 'b') {
        matches=&table[32];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[261] == 'c') {
        matches=&table[32];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[269] == 'a') {
        matches=&table[33];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[269] == 'b') {
        matches=&table[33];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[269] == 'c') {
        matches=&table[33];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[277] == 'a') {
        matches=&table[34];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[277] == 'b') {
        matches=&table[34];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[277] == 'c') {
        matches=&table[34];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[285] == 'a') {
        matches=&table[35];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[285] == 'b') {
        matches=&table[35];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[285] == 'c') {
        matches=&table[35];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[293] == 'a') {
        matches=&table[36];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[293] == 'b') {
        matches=&table[36];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[293] == 'c') {
        matches=&table[36];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[301] == 'a') {
        matches=&table[37];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[301] == 'b') {
        matches=&table[37];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[301] == 'c') {
        matches=&table[37];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[309] == 'a') {
        matches=&table[38];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[309] == 'b') {
        matches=&table[38];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[309] == 'c') {
        matches=&table[38];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[317] == 'a') {
        matches=&table[39];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[317] == 'b') {
        matches=&table[39];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[317] == 'c') {
        matches=&table[39];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[325] == 'a') {
        matches=&table[40];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[325] == 'b') {
        matches=&table[40];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[325] == 'c') {
        matches=&table[40];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[333] == 'a') {
        matches=&table[41];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[333] == 'b') {
        matches=&table[41];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[333] == 'c') {
        matches=&table[41];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[341] == 'a') {
        matches=&table[42];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[341] == 'b') {
        matches=&table[42];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[341] == 'c') {
        matches=&table[42];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[349] == 'a') {
        matches=&table[43];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[349] == 'b') {
        matches=&table[43];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[349] == 'c') {
        matches=&table[43];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[357] == 'a') {
        matches=&table[44];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[357] == 'b') {
        matches=&table[44];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[357] == 'c') {
        matches=&table[44];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[365] == 'a') {
        matches=&table[45];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[365] == 'b') {
        matches=&table[45];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[365] == 'c') {
        matches=&table[45];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[373] == 'a') {
        matches=&table[46];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[373] == 'b') {
        matches=&table[46];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[373] == 'c') {
        matches=&table[46];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[381] == 'a') {
        matches=&table[47];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[381] == 'b') {
        matches=&table[47];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[381] == 'c') {
        matches=&table[47];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[389] == 'a') {
        matches=&table[48];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[389] == 'b') {
        matches=&table[48];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[389] == 'c') {
        matches=&table[48];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[397] == 'a') {
        matches=&table[49];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[397] == 'b') {
        matches=&table[49];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[397] == 'c') {
        matches=&table[49];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[405] == 'a') {
        matches=&table[50];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[405] == 'b') {
        matches=&table[50];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[405] == 'c') {
        matches=&table[50];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[413] == 'a') {
        matches=&table[51];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[413] == 'b') {
        matches=&table[51];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[413] == 'c') {
        matches=&table[51];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[421] == 'a') {
        matches=&table[52];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[421] == 'b') {
        matches=&table[52];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[421] == 'c') {
        matches=&table[52];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[429] == 'a') {
        matches=&table[53];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[429] == 'b') {
        matches=&table[53];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[429] == 'c') {
        matches=&table[53];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[437] == 'a') {
        matches=&table[54];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[437] == 'b') {
        matches=&table[54];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[437] == 'c') {
        matches=&table[54];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[445] == 'a') {
        matches=&table[55];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[445] == 'b') {
        matches=&table[55];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[445] == 'c') {
        matches=&table[55];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[453] == 'a') {
        matches=&table[56];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[453] == 'b') {
        matches=&table[56];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[453] == 'c') {
        matches=&table[56];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[461] == 'a') {
        matches=&table[57];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[461] == 'b') {
        matches=&table[57];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[461] == 'c') {
        matches=&table[57];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[469] == 'a') {
        matches=&table[58];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[469] == 'b') {
        matches=&table[58];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[469] == 'c') {
        matches=&table[58];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[477] == 'a') {
        matches=&table[59];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[477] == 'b') {
        matches=&table[59];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[477] == 'c') {
        matches=&table[59];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[485] == 'a') {
        matches=&table[60];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[485] == 'b') {
        matches=&table[60];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[485] == 'c') {
        matches=&table[60];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[493] == 'a') {
        matches=&table[61];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[493] == 'b') {
        matches=&table[61];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[493] == 'c') {
        matches=&table[61];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[501] == 'a') {
        matches=&table[62];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[501] == 'b') {
        matches=&table[62];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[501] == 'c') {
        matches=&table[62];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }

    if (input[509] == 'a') {
        matches=&table[63];
        if (INT_MAX_VALUE/2 - 0 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 0;
        }
    }

    else if (input[509] == 'b') {
        matches=&table[63];
        if (INT_MAX_VALUE/2 - 4 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 4;
        }
    }

    else if (input[509] == 'c') {
        matches=&table[63];
        if (INT_MAX_VALUE/2 - 8 > best_score) {
            best_match = matches;
            best_score = INT_MAX_VALUE/2 - 8;
        }
    }
    return best_match ? (int)(best_match-table)+1 : 0;
}
