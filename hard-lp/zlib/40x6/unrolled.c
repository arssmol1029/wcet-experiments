
typedef unsigned char Byte, Bytef;
Byte input[256];
Byte output[4096];
unsigned result, bound_failure;

static const Byte candidate[40][10] = {
    {120, 121, 122, 65, 65, 65, 66, 65, 66, 68},
    {120, 121, 122, 65, 66, 65, 66, 65, 65, 68},
    {120, 121, 122, 66, 65, 65, 66, 66, 66, 68},
    {120, 121, 122, 65, 66, 65, 65, 65, 66, 68},
    {120, 121, 122, 66, 65, 66, 66, 66, 66, 68},
    {120, 121, 122, 65, 66, 66, 66, 66, 65, 68},
    {120, 121, 122, 65, 66, 66, 66, 65, 65, 68},
    {120, 121, 122, 66, 66, 65, 66, 65, 65, 68},
    {120, 121, 122, 66, 66, 66, 65, 65, 66, 68},
    {120, 121, 122, 66, 66, 65, 66, 65, 66, 68},
    {120, 121, 122, 66, 66, 65, 65, 65, 66, 68},
    {120, 121, 122, 65, 65, 65, 66, 65, 65, 68},
    {120, 121, 122, 65, 65, 66, 66, 65, 65, 68},
    {120, 121, 122, 65, 65, 66, 65, 66, 65, 68},
    {120, 121, 122, 65, 66, 66, 66, 66, 66, 68},
    {120, 121, 122, 66, 65, 66, 65, 65, 66, 68},
    {120, 121, 122, 65, 65, 65, 65, 66, 66, 68},
    {120, 121, 122, 65, 66, 65, 65, 65, 65, 68},
    {120, 121, 122, 65, 66, 65, 65, 66, 66, 68},
    {120, 121, 122, 66, 65, 65, 66, 65, 66, 68},
    {120, 121, 122, 66, 65, 66, 66, 65, 65, 68},
    {120, 121, 122, 66, 66, 65, 65, 65, 65, 68},
    {120, 121, 122, 65, 66, 66, 65, 65, 65, 68},
    {120, 121, 122, 66, 66, 66, 66, 66, 65, 68},
    {120, 121, 122, 66, 65, 65, 66, 65, 65, 68},
    {120, 121, 122, 66, 65, 65, 65, 66, 66, 68},
    {120, 121, 122, 66, 66, 66, 66, 65, 66, 68},
    {120, 121, 122, 65, 65, 66, 66, 66, 66, 68},
    {120, 121, 122, 65, 66, 66, 65, 66, 66, 68},
    {120, 121, 122, 65, 65, 65, 65, 66, 65, 68},
    {120, 121, 122, 66, 66, 66, 65, 66, 66, 68},
    {120, 121, 122, 66, 65, 66, 66, 65, 66, 68},
    {120, 121, 122, 66, 65, 65, 66, 66, 65, 68},
    {120, 121, 122, 65, 66, 66, 65, 65, 66, 68},
    {120, 121, 122, 65, 66, 66, 66, 65, 66, 68},
    {120, 121, 122, 65, 66, 65, 66, 66, 66, 68},
    {120, 121, 122, 66, 66, 65, 65, 66, 66, 68},
    {120, 121, 122, 66, 65, 66, 65, 66, 65, 68},
    {120, 121, 122, 65, 66, 65, 66, 66, 65, 68},
    {120, 121, 122, 66, 66, 66, 65, 65, 65, 68},
};

unsigned benchmark_entry(void) {
    int len, best_len = 2;
    unsigned match_start = 0;
    Byte scan_end1 = input[best_len - 1];
    Byte scan_end = input[best_len];

    if (candidate[0][best_len] != scan_end ||
        candidate[0][best_len - 1] != scan_end1 ||
        candidate[0][0] != input[0] ||
        candidate[0][1] != input[1])
        goto next_0;
    if (candidate[0][3] != input[3]) {
        len = 3;
        goto checked_0;
    }
    if (candidate[0][4] != input[4]) {
        len = 4;
        goto checked_0;
    }
    if (candidate[0][5] != input[5]) {
        len = 5;
        goto checked_0;
    }
    if (candidate[0][6] != input[6]) {
        len = 6;
        goto checked_0;
    }
    if (candidate[0][7] != input[7]) {
        len = 7;
        goto checked_0;
    }
    if (candidate[0][8] != input[8]) {
        len = 8;
        goto checked_0;
    }
    len = 9;
checked_0:
    if (len > best_len) {
        match_start = 1280;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_0: ;

    if (candidate[1][best_len] != scan_end ||
        candidate[1][best_len - 1] != scan_end1 ||
        candidate[1][0] != input[0] ||
        candidate[1][1] != input[1])
        goto next_1;
    if (candidate[1][3] != input[3]) {
        len = 3;
        goto checked_1;
    }
    if (candidate[1][4] != input[4]) {
        len = 4;
        goto checked_1;
    }
    if (candidate[1][5] != input[5]) {
        len = 5;
        goto checked_1;
    }
    if (candidate[1][6] != input[6]) {
        len = 6;
        goto checked_1;
    }
    if (candidate[1][7] != input[7]) {
        len = 7;
        goto checked_1;
    }
    if (candidate[1][8] != input[8]) {
        len = 8;
        goto checked_1;
    }
    len = 9;
checked_1:
    if (len > best_len) {
        match_start = 1248;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_1: ;

    if (candidate[2][best_len] != scan_end ||
        candidate[2][best_len - 1] != scan_end1 ||
        candidate[2][0] != input[0] ||
        candidate[2][1] != input[1])
        goto next_2;
    if (candidate[2][3] != input[3]) {
        len = 3;
        goto checked_2;
    }
    if (candidate[2][4] != input[4]) {
        len = 4;
        goto checked_2;
    }
    if (candidate[2][5] != input[5]) {
        len = 5;
        goto checked_2;
    }
    if (candidate[2][6] != input[6]) {
        len = 6;
        goto checked_2;
    }
    if (candidate[2][7] != input[7]) {
        len = 7;
        goto checked_2;
    }
    if (candidate[2][8] != input[8]) {
        len = 8;
        goto checked_2;
    }
    len = 9;
checked_2:
    if (len > best_len) {
        match_start = 1216;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_2: ;

    if (candidate[3][best_len] != scan_end ||
        candidate[3][best_len - 1] != scan_end1 ||
        candidate[3][0] != input[0] ||
        candidate[3][1] != input[1])
        goto next_3;
    if (candidate[3][3] != input[3]) {
        len = 3;
        goto checked_3;
    }
    if (candidate[3][4] != input[4]) {
        len = 4;
        goto checked_3;
    }
    if (candidate[3][5] != input[5]) {
        len = 5;
        goto checked_3;
    }
    if (candidate[3][6] != input[6]) {
        len = 6;
        goto checked_3;
    }
    if (candidate[3][7] != input[7]) {
        len = 7;
        goto checked_3;
    }
    if (candidate[3][8] != input[8]) {
        len = 8;
        goto checked_3;
    }
    len = 9;
checked_3:
    if (len > best_len) {
        match_start = 1184;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_3: ;

    if (candidate[4][best_len] != scan_end ||
        candidate[4][best_len - 1] != scan_end1 ||
        candidate[4][0] != input[0] ||
        candidate[4][1] != input[1])
        goto next_4;
    if (candidate[4][3] != input[3]) {
        len = 3;
        goto checked_4;
    }
    if (candidate[4][4] != input[4]) {
        len = 4;
        goto checked_4;
    }
    if (candidate[4][5] != input[5]) {
        len = 5;
        goto checked_4;
    }
    if (candidate[4][6] != input[6]) {
        len = 6;
        goto checked_4;
    }
    if (candidate[4][7] != input[7]) {
        len = 7;
        goto checked_4;
    }
    if (candidate[4][8] != input[8]) {
        len = 8;
        goto checked_4;
    }
    len = 9;
checked_4:
    if (len > best_len) {
        match_start = 1152;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_4: ;

    if (candidate[5][best_len] != scan_end ||
        candidate[5][best_len - 1] != scan_end1 ||
        candidate[5][0] != input[0] ||
        candidate[5][1] != input[1])
        goto next_5;
    if (candidate[5][3] != input[3]) {
        len = 3;
        goto checked_5;
    }
    if (candidate[5][4] != input[4]) {
        len = 4;
        goto checked_5;
    }
    if (candidate[5][5] != input[5]) {
        len = 5;
        goto checked_5;
    }
    if (candidate[5][6] != input[6]) {
        len = 6;
        goto checked_5;
    }
    if (candidate[5][7] != input[7]) {
        len = 7;
        goto checked_5;
    }
    if (candidate[5][8] != input[8]) {
        len = 8;
        goto checked_5;
    }
    len = 9;
checked_5:
    if (len > best_len) {
        match_start = 1120;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_5: ;

    if (candidate[6][best_len] != scan_end ||
        candidate[6][best_len - 1] != scan_end1 ||
        candidate[6][0] != input[0] ||
        candidate[6][1] != input[1])
        goto next_6;
    if (candidate[6][3] != input[3]) {
        len = 3;
        goto checked_6;
    }
    if (candidate[6][4] != input[4]) {
        len = 4;
        goto checked_6;
    }
    if (candidate[6][5] != input[5]) {
        len = 5;
        goto checked_6;
    }
    if (candidate[6][6] != input[6]) {
        len = 6;
        goto checked_6;
    }
    if (candidate[6][7] != input[7]) {
        len = 7;
        goto checked_6;
    }
    if (candidate[6][8] != input[8]) {
        len = 8;
        goto checked_6;
    }
    len = 9;
checked_6:
    if (len > best_len) {
        match_start = 1088;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_6: ;

    if (candidate[7][best_len] != scan_end ||
        candidate[7][best_len - 1] != scan_end1 ||
        candidate[7][0] != input[0] ||
        candidate[7][1] != input[1])
        goto next_7;
    if (candidate[7][3] != input[3]) {
        len = 3;
        goto checked_7;
    }
    if (candidate[7][4] != input[4]) {
        len = 4;
        goto checked_7;
    }
    if (candidate[7][5] != input[5]) {
        len = 5;
        goto checked_7;
    }
    if (candidate[7][6] != input[6]) {
        len = 6;
        goto checked_7;
    }
    if (candidate[7][7] != input[7]) {
        len = 7;
        goto checked_7;
    }
    if (candidate[7][8] != input[8]) {
        len = 8;
        goto checked_7;
    }
    len = 9;
checked_7:
    if (len > best_len) {
        match_start = 1056;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_7: ;

    if (candidate[8][best_len] != scan_end ||
        candidate[8][best_len - 1] != scan_end1 ||
        candidate[8][0] != input[0] ||
        candidate[8][1] != input[1])
        goto next_8;
    if (candidate[8][3] != input[3]) {
        len = 3;
        goto checked_8;
    }
    if (candidate[8][4] != input[4]) {
        len = 4;
        goto checked_8;
    }
    if (candidate[8][5] != input[5]) {
        len = 5;
        goto checked_8;
    }
    if (candidate[8][6] != input[6]) {
        len = 6;
        goto checked_8;
    }
    if (candidate[8][7] != input[7]) {
        len = 7;
        goto checked_8;
    }
    if (candidate[8][8] != input[8]) {
        len = 8;
        goto checked_8;
    }
    len = 9;
checked_8:
    if (len > best_len) {
        match_start = 1024;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_8: ;

    if (candidate[9][best_len] != scan_end ||
        candidate[9][best_len - 1] != scan_end1 ||
        candidate[9][0] != input[0] ||
        candidate[9][1] != input[1])
        goto next_9;
    if (candidate[9][3] != input[3]) {
        len = 3;
        goto checked_9;
    }
    if (candidate[9][4] != input[4]) {
        len = 4;
        goto checked_9;
    }
    if (candidate[9][5] != input[5]) {
        len = 5;
        goto checked_9;
    }
    if (candidate[9][6] != input[6]) {
        len = 6;
        goto checked_9;
    }
    if (candidate[9][7] != input[7]) {
        len = 7;
        goto checked_9;
    }
    if (candidate[9][8] != input[8]) {
        len = 8;
        goto checked_9;
    }
    len = 9;
checked_9:
    if (len > best_len) {
        match_start = 992;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_9: ;

    if (candidate[10][best_len] != scan_end ||
        candidate[10][best_len - 1] != scan_end1 ||
        candidate[10][0] != input[0] ||
        candidate[10][1] != input[1])
        goto next_10;
    if (candidate[10][3] != input[3]) {
        len = 3;
        goto checked_10;
    }
    if (candidate[10][4] != input[4]) {
        len = 4;
        goto checked_10;
    }
    if (candidate[10][5] != input[5]) {
        len = 5;
        goto checked_10;
    }
    if (candidate[10][6] != input[6]) {
        len = 6;
        goto checked_10;
    }
    if (candidate[10][7] != input[7]) {
        len = 7;
        goto checked_10;
    }
    if (candidate[10][8] != input[8]) {
        len = 8;
        goto checked_10;
    }
    len = 9;
checked_10:
    if (len > best_len) {
        match_start = 960;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_10: ;

    if (candidate[11][best_len] != scan_end ||
        candidate[11][best_len - 1] != scan_end1 ||
        candidate[11][0] != input[0] ||
        candidate[11][1] != input[1])
        goto next_11;
    if (candidate[11][3] != input[3]) {
        len = 3;
        goto checked_11;
    }
    if (candidate[11][4] != input[4]) {
        len = 4;
        goto checked_11;
    }
    if (candidate[11][5] != input[5]) {
        len = 5;
        goto checked_11;
    }
    if (candidate[11][6] != input[6]) {
        len = 6;
        goto checked_11;
    }
    if (candidate[11][7] != input[7]) {
        len = 7;
        goto checked_11;
    }
    if (candidate[11][8] != input[8]) {
        len = 8;
        goto checked_11;
    }
    len = 9;
checked_11:
    if (len > best_len) {
        match_start = 928;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_11: ;

    if (candidate[12][best_len] != scan_end ||
        candidate[12][best_len - 1] != scan_end1 ||
        candidate[12][0] != input[0] ||
        candidate[12][1] != input[1])
        goto next_12;
    if (candidate[12][3] != input[3]) {
        len = 3;
        goto checked_12;
    }
    if (candidate[12][4] != input[4]) {
        len = 4;
        goto checked_12;
    }
    if (candidate[12][5] != input[5]) {
        len = 5;
        goto checked_12;
    }
    if (candidate[12][6] != input[6]) {
        len = 6;
        goto checked_12;
    }
    if (candidate[12][7] != input[7]) {
        len = 7;
        goto checked_12;
    }
    if (candidate[12][8] != input[8]) {
        len = 8;
        goto checked_12;
    }
    len = 9;
checked_12:
    if (len > best_len) {
        match_start = 896;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_12: ;

    if (candidate[13][best_len] != scan_end ||
        candidate[13][best_len - 1] != scan_end1 ||
        candidate[13][0] != input[0] ||
        candidate[13][1] != input[1])
        goto next_13;
    if (candidate[13][3] != input[3]) {
        len = 3;
        goto checked_13;
    }
    if (candidate[13][4] != input[4]) {
        len = 4;
        goto checked_13;
    }
    if (candidate[13][5] != input[5]) {
        len = 5;
        goto checked_13;
    }
    if (candidate[13][6] != input[6]) {
        len = 6;
        goto checked_13;
    }
    if (candidate[13][7] != input[7]) {
        len = 7;
        goto checked_13;
    }
    if (candidate[13][8] != input[8]) {
        len = 8;
        goto checked_13;
    }
    len = 9;
checked_13:
    if (len > best_len) {
        match_start = 864;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_13: ;

    if (candidate[14][best_len] != scan_end ||
        candidate[14][best_len - 1] != scan_end1 ||
        candidate[14][0] != input[0] ||
        candidate[14][1] != input[1])
        goto next_14;
    if (candidate[14][3] != input[3]) {
        len = 3;
        goto checked_14;
    }
    if (candidate[14][4] != input[4]) {
        len = 4;
        goto checked_14;
    }
    if (candidate[14][5] != input[5]) {
        len = 5;
        goto checked_14;
    }
    if (candidate[14][6] != input[6]) {
        len = 6;
        goto checked_14;
    }
    if (candidate[14][7] != input[7]) {
        len = 7;
        goto checked_14;
    }
    if (candidate[14][8] != input[8]) {
        len = 8;
        goto checked_14;
    }
    len = 9;
checked_14:
    if (len > best_len) {
        match_start = 832;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_14: ;

    if (candidate[15][best_len] != scan_end ||
        candidate[15][best_len - 1] != scan_end1 ||
        candidate[15][0] != input[0] ||
        candidate[15][1] != input[1])
        goto next_15;
    if (candidate[15][3] != input[3]) {
        len = 3;
        goto checked_15;
    }
    if (candidate[15][4] != input[4]) {
        len = 4;
        goto checked_15;
    }
    if (candidate[15][5] != input[5]) {
        len = 5;
        goto checked_15;
    }
    if (candidate[15][6] != input[6]) {
        len = 6;
        goto checked_15;
    }
    if (candidate[15][7] != input[7]) {
        len = 7;
        goto checked_15;
    }
    if (candidate[15][8] != input[8]) {
        len = 8;
        goto checked_15;
    }
    len = 9;
checked_15:
    if (len > best_len) {
        match_start = 800;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_15: ;

    if (candidate[16][best_len] != scan_end ||
        candidate[16][best_len - 1] != scan_end1 ||
        candidate[16][0] != input[0] ||
        candidate[16][1] != input[1])
        goto next_16;
    if (candidate[16][3] != input[3]) {
        len = 3;
        goto checked_16;
    }
    if (candidate[16][4] != input[4]) {
        len = 4;
        goto checked_16;
    }
    if (candidate[16][5] != input[5]) {
        len = 5;
        goto checked_16;
    }
    if (candidate[16][6] != input[6]) {
        len = 6;
        goto checked_16;
    }
    if (candidate[16][7] != input[7]) {
        len = 7;
        goto checked_16;
    }
    if (candidate[16][8] != input[8]) {
        len = 8;
        goto checked_16;
    }
    len = 9;
checked_16:
    if (len > best_len) {
        match_start = 768;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_16: ;

    if (candidate[17][best_len] != scan_end ||
        candidate[17][best_len - 1] != scan_end1 ||
        candidate[17][0] != input[0] ||
        candidate[17][1] != input[1])
        goto next_17;
    if (candidate[17][3] != input[3]) {
        len = 3;
        goto checked_17;
    }
    if (candidate[17][4] != input[4]) {
        len = 4;
        goto checked_17;
    }
    if (candidate[17][5] != input[5]) {
        len = 5;
        goto checked_17;
    }
    if (candidate[17][6] != input[6]) {
        len = 6;
        goto checked_17;
    }
    if (candidate[17][7] != input[7]) {
        len = 7;
        goto checked_17;
    }
    if (candidate[17][8] != input[8]) {
        len = 8;
        goto checked_17;
    }
    len = 9;
checked_17:
    if (len > best_len) {
        match_start = 736;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_17: ;

    if (candidate[18][best_len] != scan_end ||
        candidate[18][best_len - 1] != scan_end1 ||
        candidate[18][0] != input[0] ||
        candidate[18][1] != input[1])
        goto next_18;
    if (candidate[18][3] != input[3]) {
        len = 3;
        goto checked_18;
    }
    if (candidate[18][4] != input[4]) {
        len = 4;
        goto checked_18;
    }
    if (candidate[18][5] != input[5]) {
        len = 5;
        goto checked_18;
    }
    if (candidate[18][6] != input[6]) {
        len = 6;
        goto checked_18;
    }
    if (candidate[18][7] != input[7]) {
        len = 7;
        goto checked_18;
    }
    if (candidate[18][8] != input[8]) {
        len = 8;
        goto checked_18;
    }
    len = 9;
checked_18:
    if (len > best_len) {
        match_start = 704;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_18: ;

    if (candidate[19][best_len] != scan_end ||
        candidate[19][best_len - 1] != scan_end1 ||
        candidate[19][0] != input[0] ||
        candidate[19][1] != input[1])
        goto next_19;
    if (candidate[19][3] != input[3]) {
        len = 3;
        goto checked_19;
    }
    if (candidate[19][4] != input[4]) {
        len = 4;
        goto checked_19;
    }
    if (candidate[19][5] != input[5]) {
        len = 5;
        goto checked_19;
    }
    if (candidate[19][6] != input[6]) {
        len = 6;
        goto checked_19;
    }
    if (candidate[19][7] != input[7]) {
        len = 7;
        goto checked_19;
    }
    if (candidate[19][8] != input[8]) {
        len = 8;
        goto checked_19;
    }
    len = 9;
checked_19:
    if (len > best_len) {
        match_start = 672;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_19: ;

    if (candidate[20][best_len] != scan_end ||
        candidate[20][best_len - 1] != scan_end1 ||
        candidate[20][0] != input[0] ||
        candidate[20][1] != input[1])
        goto next_20;
    if (candidate[20][3] != input[3]) {
        len = 3;
        goto checked_20;
    }
    if (candidate[20][4] != input[4]) {
        len = 4;
        goto checked_20;
    }
    if (candidate[20][5] != input[5]) {
        len = 5;
        goto checked_20;
    }
    if (candidate[20][6] != input[6]) {
        len = 6;
        goto checked_20;
    }
    if (candidate[20][7] != input[7]) {
        len = 7;
        goto checked_20;
    }
    if (candidate[20][8] != input[8]) {
        len = 8;
        goto checked_20;
    }
    len = 9;
checked_20:
    if (len > best_len) {
        match_start = 640;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_20: ;

    if (candidate[21][best_len] != scan_end ||
        candidate[21][best_len - 1] != scan_end1 ||
        candidate[21][0] != input[0] ||
        candidate[21][1] != input[1])
        goto next_21;
    if (candidate[21][3] != input[3]) {
        len = 3;
        goto checked_21;
    }
    if (candidate[21][4] != input[4]) {
        len = 4;
        goto checked_21;
    }
    if (candidate[21][5] != input[5]) {
        len = 5;
        goto checked_21;
    }
    if (candidate[21][6] != input[6]) {
        len = 6;
        goto checked_21;
    }
    if (candidate[21][7] != input[7]) {
        len = 7;
        goto checked_21;
    }
    if (candidate[21][8] != input[8]) {
        len = 8;
        goto checked_21;
    }
    len = 9;
checked_21:
    if (len > best_len) {
        match_start = 608;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_21: ;

    if (candidate[22][best_len] != scan_end ||
        candidate[22][best_len - 1] != scan_end1 ||
        candidate[22][0] != input[0] ||
        candidate[22][1] != input[1])
        goto next_22;
    if (candidate[22][3] != input[3]) {
        len = 3;
        goto checked_22;
    }
    if (candidate[22][4] != input[4]) {
        len = 4;
        goto checked_22;
    }
    if (candidate[22][5] != input[5]) {
        len = 5;
        goto checked_22;
    }
    if (candidate[22][6] != input[6]) {
        len = 6;
        goto checked_22;
    }
    if (candidate[22][7] != input[7]) {
        len = 7;
        goto checked_22;
    }
    if (candidate[22][8] != input[8]) {
        len = 8;
        goto checked_22;
    }
    len = 9;
checked_22:
    if (len > best_len) {
        match_start = 576;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_22: ;

    if (candidate[23][best_len] != scan_end ||
        candidate[23][best_len - 1] != scan_end1 ||
        candidate[23][0] != input[0] ||
        candidate[23][1] != input[1])
        goto next_23;
    if (candidate[23][3] != input[3]) {
        len = 3;
        goto checked_23;
    }
    if (candidate[23][4] != input[4]) {
        len = 4;
        goto checked_23;
    }
    if (candidate[23][5] != input[5]) {
        len = 5;
        goto checked_23;
    }
    if (candidate[23][6] != input[6]) {
        len = 6;
        goto checked_23;
    }
    if (candidate[23][7] != input[7]) {
        len = 7;
        goto checked_23;
    }
    if (candidate[23][8] != input[8]) {
        len = 8;
        goto checked_23;
    }
    len = 9;
checked_23:
    if (len > best_len) {
        match_start = 544;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_23: ;

    if (candidate[24][best_len] != scan_end ||
        candidate[24][best_len - 1] != scan_end1 ||
        candidate[24][0] != input[0] ||
        candidate[24][1] != input[1])
        goto next_24;
    if (candidate[24][3] != input[3]) {
        len = 3;
        goto checked_24;
    }
    if (candidate[24][4] != input[4]) {
        len = 4;
        goto checked_24;
    }
    if (candidate[24][5] != input[5]) {
        len = 5;
        goto checked_24;
    }
    if (candidate[24][6] != input[6]) {
        len = 6;
        goto checked_24;
    }
    if (candidate[24][7] != input[7]) {
        len = 7;
        goto checked_24;
    }
    if (candidate[24][8] != input[8]) {
        len = 8;
        goto checked_24;
    }
    len = 9;
checked_24:
    if (len > best_len) {
        match_start = 512;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_24: ;

    if (candidate[25][best_len] != scan_end ||
        candidate[25][best_len - 1] != scan_end1 ||
        candidate[25][0] != input[0] ||
        candidate[25][1] != input[1])
        goto next_25;
    if (candidate[25][3] != input[3]) {
        len = 3;
        goto checked_25;
    }
    if (candidate[25][4] != input[4]) {
        len = 4;
        goto checked_25;
    }
    if (candidate[25][5] != input[5]) {
        len = 5;
        goto checked_25;
    }
    if (candidate[25][6] != input[6]) {
        len = 6;
        goto checked_25;
    }
    if (candidate[25][7] != input[7]) {
        len = 7;
        goto checked_25;
    }
    if (candidate[25][8] != input[8]) {
        len = 8;
        goto checked_25;
    }
    len = 9;
checked_25:
    if (len > best_len) {
        match_start = 480;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_25: ;

    if (candidate[26][best_len] != scan_end ||
        candidate[26][best_len - 1] != scan_end1 ||
        candidate[26][0] != input[0] ||
        candidate[26][1] != input[1])
        goto next_26;
    if (candidate[26][3] != input[3]) {
        len = 3;
        goto checked_26;
    }
    if (candidate[26][4] != input[4]) {
        len = 4;
        goto checked_26;
    }
    if (candidate[26][5] != input[5]) {
        len = 5;
        goto checked_26;
    }
    if (candidate[26][6] != input[6]) {
        len = 6;
        goto checked_26;
    }
    if (candidate[26][7] != input[7]) {
        len = 7;
        goto checked_26;
    }
    if (candidate[26][8] != input[8]) {
        len = 8;
        goto checked_26;
    }
    len = 9;
checked_26:
    if (len > best_len) {
        match_start = 448;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_26: ;

    if (candidate[27][best_len] != scan_end ||
        candidate[27][best_len - 1] != scan_end1 ||
        candidate[27][0] != input[0] ||
        candidate[27][1] != input[1])
        goto next_27;
    if (candidate[27][3] != input[3]) {
        len = 3;
        goto checked_27;
    }
    if (candidate[27][4] != input[4]) {
        len = 4;
        goto checked_27;
    }
    if (candidate[27][5] != input[5]) {
        len = 5;
        goto checked_27;
    }
    if (candidate[27][6] != input[6]) {
        len = 6;
        goto checked_27;
    }
    if (candidate[27][7] != input[7]) {
        len = 7;
        goto checked_27;
    }
    if (candidate[27][8] != input[8]) {
        len = 8;
        goto checked_27;
    }
    len = 9;
checked_27:
    if (len > best_len) {
        match_start = 416;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_27: ;

    if (candidate[28][best_len] != scan_end ||
        candidate[28][best_len - 1] != scan_end1 ||
        candidate[28][0] != input[0] ||
        candidate[28][1] != input[1])
        goto next_28;
    if (candidate[28][3] != input[3]) {
        len = 3;
        goto checked_28;
    }
    if (candidate[28][4] != input[4]) {
        len = 4;
        goto checked_28;
    }
    if (candidate[28][5] != input[5]) {
        len = 5;
        goto checked_28;
    }
    if (candidate[28][6] != input[6]) {
        len = 6;
        goto checked_28;
    }
    if (candidate[28][7] != input[7]) {
        len = 7;
        goto checked_28;
    }
    if (candidate[28][8] != input[8]) {
        len = 8;
        goto checked_28;
    }
    len = 9;
checked_28:
    if (len > best_len) {
        match_start = 384;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_28: ;

    if (candidate[29][best_len] != scan_end ||
        candidate[29][best_len - 1] != scan_end1 ||
        candidate[29][0] != input[0] ||
        candidate[29][1] != input[1])
        goto next_29;
    if (candidate[29][3] != input[3]) {
        len = 3;
        goto checked_29;
    }
    if (candidate[29][4] != input[4]) {
        len = 4;
        goto checked_29;
    }
    if (candidate[29][5] != input[5]) {
        len = 5;
        goto checked_29;
    }
    if (candidate[29][6] != input[6]) {
        len = 6;
        goto checked_29;
    }
    if (candidate[29][7] != input[7]) {
        len = 7;
        goto checked_29;
    }
    if (candidate[29][8] != input[8]) {
        len = 8;
        goto checked_29;
    }
    len = 9;
checked_29:
    if (len > best_len) {
        match_start = 352;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_29: ;

    if (candidate[30][best_len] != scan_end ||
        candidate[30][best_len - 1] != scan_end1 ||
        candidate[30][0] != input[0] ||
        candidate[30][1] != input[1])
        goto next_30;
    if (candidate[30][3] != input[3]) {
        len = 3;
        goto checked_30;
    }
    if (candidate[30][4] != input[4]) {
        len = 4;
        goto checked_30;
    }
    if (candidate[30][5] != input[5]) {
        len = 5;
        goto checked_30;
    }
    if (candidate[30][6] != input[6]) {
        len = 6;
        goto checked_30;
    }
    if (candidate[30][7] != input[7]) {
        len = 7;
        goto checked_30;
    }
    if (candidate[30][8] != input[8]) {
        len = 8;
        goto checked_30;
    }
    len = 9;
checked_30:
    if (len > best_len) {
        match_start = 320;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_30: ;

    if (candidate[31][best_len] != scan_end ||
        candidate[31][best_len - 1] != scan_end1 ||
        candidate[31][0] != input[0] ||
        candidate[31][1] != input[1])
        goto next_31;
    if (candidate[31][3] != input[3]) {
        len = 3;
        goto checked_31;
    }
    if (candidate[31][4] != input[4]) {
        len = 4;
        goto checked_31;
    }
    if (candidate[31][5] != input[5]) {
        len = 5;
        goto checked_31;
    }
    if (candidate[31][6] != input[6]) {
        len = 6;
        goto checked_31;
    }
    if (candidate[31][7] != input[7]) {
        len = 7;
        goto checked_31;
    }
    if (candidate[31][8] != input[8]) {
        len = 8;
        goto checked_31;
    }
    len = 9;
checked_31:
    if (len > best_len) {
        match_start = 288;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_31: ;

    if (candidate[32][best_len] != scan_end ||
        candidate[32][best_len - 1] != scan_end1 ||
        candidate[32][0] != input[0] ||
        candidate[32][1] != input[1])
        goto next_32;
    if (candidate[32][3] != input[3]) {
        len = 3;
        goto checked_32;
    }
    if (candidate[32][4] != input[4]) {
        len = 4;
        goto checked_32;
    }
    if (candidate[32][5] != input[5]) {
        len = 5;
        goto checked_32;
    }
    if (candidate[32][6] != input[6]) {
        len = 6;
        goto checked_32;
    }
    if (candidate[32][7] != input[7]) {
        len = 7;
        goto checked_32;
    }
    if (candidate[32][8] != input[8]) {
        len = 8;
        goto checked_32;
    }
    len = 9;
checked_32:
    if (len > best_len) {
        match_start = 256;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_32: ;

    if (candidate[33][best_len] != scan_end ||
        candidate[33][best_len - 1] != scan_end1 ||
        candidate[33][0] != input[0] ||
        candidate[33][1] != input[1])
        goto next_33;
    if (candidate[33][3] != input[3]) {
        len = 3;
        goto checked_33;
    }
    if (candidate[33][4] != input[4]) {
        len = 4;
        goto checked_33;
    }
    if (candidate[33][5] != input[5]) {
        len = 5;
        goto checked_33;
    }
    if (candidate[33][6] != input[6]) {
        len = 6;
        goto checked_33;
    }
    if (candidate[33][7] != input[7]) {
        len = 7;
        goto checked_33;
    }
    if (candidate[33][8] != input[8]) {
        len = 8;
        goto checked_33;
    }
    len = 9;
checked_33:
    if (len > best_len) {
        match_start = 224;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_33: ;

    if (candidate[34][best_len] != scan_end ||
        candidate[34][best_len - 1] != scan_end1 ||
        candidate[34][0] != input[0] ||
        candidate[34][1] != input[1])
        goto next_34;
    if (candidate[34][3] != input[3]) {
        len = 3;
        goto checked_34;
    }
    if (candidate[34][4] != input[4]) {
        len = 4;
        goto checked_34;
    }
    if (candidate[34][5] != input[5]) {
        len = 5;
        goto checked_34;
    }
    if (candidate[34][6] != input[6]) {
        len = 6;
        goto checked_34;
    }
    if (candidate[34][7] != input[7]) {
        len = 7;
        goto checked_34;
    }
    if (candidate[34][8] != input[8]) {
        len = 8;
        goto checked_34;
    }
    len = 9;
checked_34:
    if (len > best_len) {
        match_start = 192;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_34: ;

    if (candidate[35][best_len] != scan_end ||
        candidate[35][best_len - 1] != scan_end1 ||
        candidate[35][0] != input[0] ||
        candidate[35][1] != input[1])
        goto next_35;
    if (candidate[35][3] != input[3]) {
        len = 3;
        goto checked_35;
    }
    if (candidate[35][4] != input[4]) {
        len = 4;
        goto checked_35;
    }
    if (candidate[35][5] != input[5]) {
        len = 5;
        goto checked_35;
    }
    if (candidate[35][6] != input[6]) {
        len = 6;
        goto checked_35;
    }
    if (candidate[35][7] != input[7]) {
        len = 7;
        goto checked_35;
    }
    if (candidate[35][8] != input[8]) {
        len = 8;
        goto checked_35;
    }
    len = 9;
checked_35:
    if (len > best_len) {
        match_start = 160;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_35: ;

    if (candidate[36][best_len] != scan_end ||
        candidate[36][best_len - 1] != scan_end1 ||
        candidate[36][0] != input[0] ||
        candidate[36][1] != input[1])
        goto next_36;
    if (candidate[36][3] != input[3]) {
        len = 3;
        goto checked_36;
    }
    if (candidate[36][4] != input[4]) {
        len = 4;
        goto checked_36;
    }
    if (candidate[36][5] != input[5]) {
        len = 5;
        goto checked_36;
    }
    if (candidate[36][6] != input[6]) {
        len = 6;
        goto checked_36;
    }
    if (candidate[36][7] != input[7]) {
        len = 7;
        goto checked_36;
    }
    if (candidate[36][8] != input[8]) {
        len = 8;
        goto checked_36;
    }
    len = 9;
checked_36:
    if (len > best_len) {
        match_start = 128;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_36: ;

    if (candidate[37][best_len] != scan_end ||
        candidate[37][best_len - 1] != scan_end1 ||
        candidate[37][0] != input[0] ||
        candidate[37][1] != input[1])
        goto next_37;
    if (candidate[37][3] != input[3]) {
        len = 3;
        goto checked_37;
    }
    if (candidate[37][4] != input[4]) {
        len = 4;
        goto checked_37;
    }
    if (candidate[37][5] != input[5]) {
        len = 5;
        goto checked_37;
    }
    if (candidate[37][6] != input[6]) {
        len = 6;
        goto checked_37;
    }
    if (candidate[37][7] != input[7]) {
        len = 7;
        goto checked_37;
    }
    if (candidate[37][8] != input[8]) {
        len = 8;
        goto checked_37;
    }
    len = 9;
checked_37:
    if (len > best_len) {
        match_start = 96;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_37: ;

    if (candidate[38][best_len] != scan_end ||
        candidate[38][best_len - 1] != scan_end1 ||
        candidate[38][0] != input[0] ||
        candidate[38][1] != input[1])
        goto next_38;
    if (candidate[38][3] != input[3]) {
        len = 3;
        goto checked_38;
    }
    if (candidate[38][4] != input[4]) {
        len = 4;
        goto checked_38;
    }
    if (candidate[38][5] != input[5]) {
        len = 5;
        goto checked_38;
    }
    if (candidate[38][6] != input[6]) {
        len = 6;
        goto checked_38;
    }
    if (candidate[38][7] != input[7]) {
        len = 7;
        goto checked_38;
    }
    if (candidate[38][8] != input[8]) {
        len = 8;
        goto checked_38;
    }
    len = 9;
checked_38:
    if (len > best_len) {
        match_start = 64;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_38: ;

    if (candidate[39][best_len] != scan_end ||
        candidate[39][best_len - 1] != scan_end1 ||
        candidate[39][0] != input[0] ||
        candidate[39][1] != input[1])
        goto next_39;
    if (candidate[39][3] != input[3]) {
        len = 3;
        goto checked_39;
    }
    if (candidate[39][4] != input[4]) {
        len = 4;
        goto checked_39;
    }
    if (candidate[39][5] != input[5]) {
        len = 5;
        goto checked_39;
    }
    if (candidate[39][6] != input[6]) {
        len = 6;
        goto checked_39;
    }
    if (candidate[39][7] != input[7]) {
        len = 7;
        goto checked_39;
    }
    if (candidate[39][8] != input[8]) {
        len = 8;
        goto checked_39;
    }
    len = 9;
checked_39:
    if (len > best_len) {
        match_start = 32;
        best_len = len;
        if (len >= 9)
            goto finish;
        scan_end1 = input[best_len - 1];
        scan_end = input[best_len];
    }
next_39: ;
finish:
    return (match_start << 8) | (best_len <= 10 ? best_len : 10);
}
