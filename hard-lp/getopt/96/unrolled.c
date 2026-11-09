#include <stddef.h>
#include <stdint.h>
unsigned char input[384], output[4096];
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
  {(const char *)(input + 256),0,NULL,118},
  {(const char *)(input + 260),0,NULL,118},
  {(const char *)(input + 264),0,NULL,118},
  {(const char *)(input + 268),0,NULL,118},
  {(const char *)(input + 272),0,NULL,118},
  {(const char *)(input + 276),0,NULL,118},
  {(const char *)(input + 280),0,NULL,118},
  {(const char *)(input + 284),0,NULL,118},
  {(const char *)(input + 288),0,NULL,118},
  {(const char *)(input + 292),0,NULL,118},
  {(const char *)(input + 296),0,NULL,118},
  {(const char *)(input + 300),0,NULL,118},
  {(const char *)(input + 304),0,NULL,118},
  {(const char *)(input + 308),0,NULL,118},
  {(const char *)(input + 312),0,NULL,118},
  {(const char *)(input + 316),0,NULL,118},
  {(const char *)(input + 320),0,NULL,118},
  {(const char *)(input + 324),0,NULL,118},
  {(const char *)(input + 328),0,NULL,118},
  {(const char *)(input + 332),0,NULL,118},
  {(const char *)(input + 336),0,NULL,118},
  {(const char *)(input + 340),0,NULL,118},
  {(const char *)(input + 344),0,NULL,118},
  {(const char *)(input + 348),0,NULL,118},
  {(const char *)(input + 352),0,NULL,118},
  {(const char *)(input + 356),0,NULL,118},
  {(const char *)(input + 360),0,NULL,118},
  {(const char *)(input + 364),0,NULL,118},
  {(const char *)(input + 368),0,NULL,118},
  {(const char *)(input + 372),0,NULL,118},
  {(const char *)(input + 376),0,NULL,118},
  {(const char *)(input + 380),0,NULL,118},
  {NULL,0,NULL,0}
};
int benchmark_entry(void) {
    const struct option *p, *pfound = NULL;
    int indfound = -1, option_index, ambig_fallback = 0;
    p = &longopts[0];
    option_index = 0;
    if (input[0] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[1];
    option_index = 1;
    if (input[4] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[2];
    option_index = 2;
    if (input[8] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[3];
    option_index = 3;
    if (input[12] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[4];
    option_index = 4;
    if (input[16] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[5];
    option_index = 5;
    if (input[20] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[6];
    option_index = 6;
    if (input[24] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[7];
    option_index = 7;
    if (input[28] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[8];
    option_index = 8;
    if (input[32] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[9];
    option_index = 9;
    if (input[36] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[10];
    option_index = 10;
    if (input[40] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[11];
    option_index = 11;
    if (input[44] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[12];
    option_index = 12;
    if (input[48] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[13];
    option_index = 13;
    if (input[52] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[14];
    option_index = 14;
    if (input[56] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[15];
    option_index = 15;
    if (input[60] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[16];
    option_index = 16;
    if (input[64] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[17];
    option_index = 17;
    if (input[68] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[18];
    option_index = 18;
    if (input[72] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[19];
    option_index = 19;
    if (input[76] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[20];
    option_index = 20;
    if (input[80] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[21];
    option_index = 21;
    if (input[84] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[22];
    option_index = 22;
    if (input[88] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[23];
    option_index = 23;
    if (input[92] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[24];
    option_index = 24;
    if (input[96] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[25];
    option_index = 25;
    if (input[100] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[26];
    option_index = 26;
    if (input[104] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[27];
    option_index = 27;
    if (input[108] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[28];
    option_index = 28;
    if (input[112] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[29];
    option_index = 29;
    if (input[116] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[30];
    option_index = 30;
    if (input[120] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[31];
    option_index = 31;
    if (input[124] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[32];
    option_index = 32;
    if (input[128] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[33];
    option_index = 33;
    if (input[132] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[34];
    option_index = 34;
    if (input[136] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[35];
    option_index = 35;
    if (input[140] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[36];
    option_index = 36;
    if (input[144] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[37];
    option_index = 37;
    if (input[148] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[38];
    option_index = 38;
    if (input[152] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[39];
    option_index = 39;
    if (input[156] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[40];
    option_index = 40;
    if (input[160] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[41];
    option_index = 41;
    if (input[164] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[42];
    option_index = 42;
    if (input[168] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[43];
    option_index = 43;
    if (input[172] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[44];
    option_index = 44;
    if (input[176] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[45];
    option_index = 45;
    if (input[180] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[46];
    option_index = 46;
    if (input[184] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[47];
    option_index = 47;
    if (input[188] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[48];
    option_index = 48;
    if (input[192] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[49];
    option_index = 49;
    if (input[196] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[50];
    option_index = 50;
    if (input[200] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[51];
    option_index = 51;
    if (input[204] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[52];
    option_index = 52;
    if (input[208] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[53];
    option_index = 53;
    if (input[212] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[54];
    option_index = 54;
    if (input[216] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[55];
    option_index = 55;
    if (input[220] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[56];
    option_index = 56;
    if (input[224] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[57];
    option_index = 57;
    if (input[228] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[58];
    option_index = 58;
    if (input[232] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[59];
    option_index = 59;
    if (input[236] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[60];
    option_index = 60;
    if (input[240] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[61];
    option_index = 61;
    if (input[244] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[62];
    option_index = 62;
    if (input[248] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[63];
    option_index = 63;
    if (input[252] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[64];
    option_index = 64;
    if (input[256] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[65];
    option_index = 65;
    if (input[260] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[66];
    option_index = 66;
    if (input[264] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[67];
    option_index = 67;
    if (input[268] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[68];
    option_index = 68;
    if (input[272] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[69];
    option_index = 69;
    if (input[276] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[70];
    option_index = 70;
    if (input[280] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[71];
    option_index = 71;
    if (input[284] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[72];
    option_index = 72;
    if (input[288] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[73];
    option_index = 73;
    if (input[292] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[74];
    option_index = 74;
    if (input[296] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[75];
    option_index = 75;
    if (input[300] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[76];
    option_index = 76;
    if (input[304] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[77];
    option_index = 77;
    if (input[308] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[78];
    option_index = 78;
    if (input[312] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[79];
    option_index = 79;
    if (input[316] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[80];
    option_index = 80;
    if (input[320] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[81];
    option_index = 81;
    if (input[324] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[82];
    option_index = 82;
    if (input[328] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[83];
    option_index = 83;
    if (input[332] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[84];
    option_index = 84;
    if (input[336] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[85];
    option_index = 85;
    if (input[340] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[86];
    option_index = 86;
    if (input[344] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[87];
    option_index = 87;
    if (input[348] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[88];
    option_index = 88;
    if (input[352] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[89];
    option_index = 89;
    if (input[356] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[90];
    option_index = 90;
    if (input[360] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[91];
    option_index = 91;
    if (input[364] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[92];
    option_index = 92;
    if (input[368] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[93];
    option_index = 93;
    if (input[372] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[94];
    option_index = 94;
    if (input[376] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}
    p = &longopts[95];
    option_index = 95;
    if (input[380] == 'a') {
if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }}

    if (ambig_fallback) return 255;
    return indfound + 1;
}
