int lookup_128(int array[], int key)
{
    int found = 0, index = 0;
    for(int i = 0; i < 16; i++)
    {
	if(array[i] == key && found == 0)
	{
	    index = i;
	    found = 1;
	}
    }
    return index;
}


int lookup_128_unr_full(int array[], int key)
{
    int found = 0, index = 0, i = 0;
    // Slice 0
    i++;
    if(i < 128 && array[0] == key && found == 0)
    {
	index = 0;
	found = 1;
    }
// Slice 1
    i++;
    if(i < 128 && array[1] == key && found == 0)
    {
	index = 1;
	found = 1;
    }
// Slice 2
    i++;
    if(i < 128 && array[2] == key && found == 0)
    {
	index = 2;
	found = 1;
    }
// Slice 3
    i++;
    if(i < 128 && array[3] == key && found == 0)
    {
	index = 3;
	found = 1;
    }
// Slice 4
    i++;
    if(i < 128 && array[4] == key && found == 0)
    {
	index = 4;
	found = 1;
    }
// Slice 5
    i++;
    if(i < 128 && array[5] == key && found == 0)
    {
	index = 5;
	found = 1;
    }
// Slice 6
    i++;
    if(i < 128 && array[6] == key && found == 0)
    {
	index = 6;
	found = 1;
    }
// Slice 7
    i++;
    if(i < 128 && array[7] == key && found == 0)
    {
	index = 7;
	found = 1;
    }
// Slice 8
    i++;
    if(i < 128 && array[8] == key && found == 0)
    {
	index = 8;
	found = 1;
    }
// Slice 9
    i++;
    if(i < 128 && array[9] == key && found == 0)
    {
	index = 9;
	found = 1;
    }
// Slice 10
    i++;
    if(i < 128 && array[10] == key && found == 0)
    {
	index = 10;
	found = 1;
    }
// Slice 11
    i++;
    if(i < 128 && array[11] == key && found == 0)
    {
	index = 11;
	found = 1;
    }
// Slice 12
    i++;
    if(i < 128 && array[12] == key && found == 0)
    {
	index = 12;
	found = 1;
    }
// Slice 13
    i++;
    if(i < 128 && array[13] == key && found == 0)
    {
	index = 13;
	found = 1;
    }
// Slice 14
    i++;
    if(i < 128 && array[14] == key && found == 0)
    {
	index = 14;
	found = 1;
    }
// Slice 15
    i++;
    if(i < 128 && array[15] == key && found == 0)
    {
	index = 15;
	found = 1;
    }
// Slice 16
    i++;
    if(i < 128 && array[16] == key && found == 0)
    {
	index = 16;
	found = 1;
    }
// Slice 17
    i++;
    if(i < 128 && array[17] == key && found == 0)
    {
	index = 17;
	found = 1;
    }
// Slice 18
    i++;
    if(i < 128 && array[18] == key && found == 0)
    {
	index = 18;
	found = 1;
    }
// Slice 19
    i++;
    if(i < 128 && array[19] == key && found == 0)
    {
	index = 19;
	found = 1;
    }
// Slice 20
    i++;
    if(i < 128 && array[20] == key && found == 0)
    {
	index = 20;
	found = 1;
    }
// Slice 21
    i++;
    if(i < 128 && array[21] == key && found == 0)
    {
	index = 21;
	found = 1;
    }
// Slice 22
    i++;
    if(i < 128 && array[22] == key && found == 0)
    {
	index = 22;
	found = 1;
    }
// Slice 23
    i++;
    if(i < 128 && array[23] == key && found == 0)
    {
	index = 23;
	found = 1;
    }
// Slice 24
    i++;
    if(i < 128 && array[24] == key && found == 0)
    {
	index = 24;
	found = 1;
    }
// Slice 25
    i++;
    if(i < 128 && array[25] == key && found == 0)
    {
	index = 25;
	found = 1;
    }
// Slice 26
    i++;
    if(i < 128 && array[26] == key && found == 0)
    {
	index = 26;
	found = 1;
    }
// Slice 27
    i++;
    if(i < 128 && array[27] == key && found == 0)
    {
	index = 27;
	found = 1;
    }
// Slice 28
    i++;
    if(i < 128 && array[28] == key && found == 0)
    {
	index = 28;
	found = 1;
    }
// Slice 29
    i++;
    if(i < 128 && array[29] == key && found == 0)
    {
	index = 29;
	found = 1;
    }
// Slice 30
    i++;
    if(i < 128 && array[30] == key && found == 0)
    {
	index = 30;
	found = 1;
    }
// Slice 31
    i++;
    if(i < 128 && array[31] == key && found == 0)
    {
	index = 31;
	found = 1;
    }
// Slice 32
    i++;
    if(i < 128 && array[32] == key && found == 0)
    {
	index = 32;
	found = 1;
    }
// Slice 33
    i++;
    if(i < 128 && array[33] == key && found == 0)
    {
	index = 33;
	found = 1;
    }
// Slice 34
    i++;
    if(i < 128 && array[34] == key && found == 0)
    {
	index = 34;
	found = 1;
    }
// Slice 35
    i++;
    if(i < 128 && array[35] == key && found == 0)
    {
	index = 35;
	found = 1;
    }
// Slice 36
    i++;
    if(i < 128 && array[36] == key && found == 0)
    {
	index = 36;
	found = 1;
    }
// Slice 37
    i++;
    if(i < 128 && array[37] == key && found == 0)
    {
	index = 37;
	found = 1;
    }
// Slice 38
    i++;
    if(i < 128 && array[38] == key && found == 0)
    {
	index = 38;
	found = 1;
    }
// Slice 39
    i++;
    if(i < 128 && array[39] == key && found == 0)
    {
	index = 39;
	found = 1;
    }
// Slice 40
    i++;
    if(i < 128 && array[40] == key && found == 0)
    {
	index = 40;
	found = 1;
    }
// Slice 41
    i++;
    if(i < 128 && array[41] == key && found == 0)
    {
	index = 41;
	found = 1;
    }
// Slice 42
    i++;
    if(i < 128 && array[42] == key && found == 0)
    {
	index = 42;
	found = 1;
    }
// Slice 43
    i++;
    if(i < 128 && array[43] == key && found == 0)
    {
	index = 43;
	found = 1;
    }
// Slice 44
    i++;
    if(i < 128 && array[44] == key && found == 0)
    {
	index = 44;
	found = 1;
    }
// Slice 45
    i++;
    if(i < 128 && array[45] == key && found == 0)
    {
	index = 45;
	found = 1;
    }
// Slice 46
    i++;
    if(i < 128 && array[46] == key && found == 0)
    {
	index = 46;
	found = 1;
    }
// Slice 47
    i++;
    if(i < 128 && array[47] == key && found == 0)
    {
	index = 47;
	found = 1;
    }
// Slice 48
    i++;
    if(i < 128 && array[48] == key && found == 0)
    {
	index = 48;
	found = 1;
    }
// Slice 49
    i++;
    if(i < 128 && array[49] == key && found == 0)
    {
	index = 49;
	found = 1;
    }
// Slice 50
    i++;
    if(i < 128 && array[50] == key && found == 0)
    {
	index = 50;
	found = 1;
    }
// Slice 51
    i++;
    if(i < 128 && array[51] == key && found == 0)
    {
	index = 51;
	found = 1;
    }
// Slice 52
    i++;
    if(i < 128 && array[52] == key && found == 0)
    {
	index = 52;
	found = 1;
    }
// Slice 53
    i++;
    if(i < 128 && array[53] == key && found == 0)
    {
	index = 53;
	found = 1;
    }
// Slice 54
    i++;
    if(i < 128 && array[54] == key && found == 0)
    {
	index = 54;
	found = 1;
    }
// Slice 55
    i++;
    if(i < 128 && array[55] == key && found == 0)
    {
	index = 55;
	found = 1;
    }
// Slice 56
    i++;
    if(i < 128 && array[56] == key && found == 0)
    {
	index = 56;
	found = 1;
    }
// Slice 57
    i++;
    if(i < 128 && array[57] == key && found == 0)
    {
	index = 57;
	found = 1;
    }
// Slice 58
    i++;
    if(i < 128 && array[58] == key && found == 0)
    {
	index = 58;
	found = 1;
    }
// Slice 59
    i++;
    if(i < 128 && array[59] == key && found == 0)
    {
	index = 59;
	found = 1;
    }
// Slice 60
    i++;
    if(i < 128 && array[60] == key && found == 0)
    {
	index = 60;
	found = 1;
    }
// Slice 61
    i++;
    if(i < 128 && array[61] == key && found == 0)
    {
	index = 61;
	found = 1;
    }
// Slice 62
    i++;
    if(i < 128 && array[62] == key && found == 0)
    {
	index = 62;
	found = 1;
    }
// Slice 63
    i++;
    if(i < 128 && array[63] == key && found == 0)
    {
	index = 63;
	found = 1;
    }
// Slice 64
    i++;
    if(i < 128 && array[64] == key && found == 0)
    {
	index = 64;
	found = 1;
    }
// Slice 65
    i++;
    if(i < 128 && array[65] == key && found == 0)
    {
	index = 65;
	found = 1;
    }
// Slice 66
    i++;
    if(i < 128 && array[66] == key && found == 0)
    {
	index = 66;
	found = 1;
    }
// Slice 67
    i++;
    if(i < 128 && array[67] == key && found == 0)
    {
	index = 67;
	found = 1;
    }
// Slice 68
    i++;
    if(i < 128 && array[68] == key && found == 0)
    {
	index = 68;
	found = 1;
    }
// Slice 69
    i++;
    if(i < 128 && array[69] == key && found == 0)
    {
	index = 69;
	found = 1;
    }
// Slice 70
    i++;
    if(i < 128 && array[70] == key && found == 0)
    {
	index = 70;
	found = 1;
    }
// Slice 71
    i++;
    if(i < 128 && array[71] == key && found == 0)
    {
	index = 71;
	found = 1;
    }
// Slice 72
    i++;
    if(i < 128 && array[72] == key && found == 0)
    {
	index = 72;
	found = 1;
    }
// Slice 73
    i++;
    if(i < 128 && array[73] == key && found == 0)
    {
	index = 73;
	found = 1;
    }
// Slice 74
    i++;
    if(i < 128 && array[74] == key && found == 0)
    {
	index = 74;
	found = 1;
    }
// Slice 75
    i++;
    if(i < 128 && array[75] == key && found == 0)
    {
	index = 75;
	found = 1;
    }
// Slice 76
    i++;
    if(i < 128 && array[76] == key && found == 0)
    {
	index = 76;
	found = 1;
    }
// Slice 77
    i++;
    if(i < 128 && array[77] == key && found == 0)
    {
	index = 77;
	found = 1;
    }
// Slice 78
    i++;
    if(i < 128 && array[78] == key && found == 0)
    {
	index = 78;
	found = 1;
    }
// Slice 79
    i++;
    if(i < 128 && array[79] == key && found == 0)
    {
	index = 79;
	found = 1;
    }
// Slice 80
    i++;
    if(i < 128 && array[80] == key && found == 0)
    {
	index = 80;
	found = 1;
    }
// Slice 81
    i++;
    if(i < 128 && array[81] == key && found == 0)
    {
	index = 81;
	found = 1;
    }
// Slice 82
    i++;
    if(i < 128 && array[82] == key && found == 0)
    {
	index = 82;
	found = 1;
    }
// Slice 83
    i++;
    if(i < 128 && array[83] == key && found == 0)
    {
	index = 83;
	found = 1;
    }
// Slice 84
    i++;
    if(i < 128 && array[84] == key && found == 0)
    {
	index = 84;
	found = 1;
    }
// Slice 85
    i++;
    if(i < 128 && array[85] == key && found == 0)
    {
	index = 85;
	found = 1;
    }
// Slice 86
    i++;
    if(i < 128 && array[86] == key && found == 0)
    {
	index = 86;
	found = 1;
    }
// Slice 87
    i++;
    if(i < 128 && array[87] == key && found == 0)
    {
	index = 87;
	found = 1;
    }
// Slice 88
    i++;
    if(i < 128 && array[88] == key && found == 0)
    {
	index = 88;
	found = 1;
    }
// Slice 89
    i++;
    if(i < 128 && array[89] == key && found == 0)
    {
	index = 89;
	found = 1;
    }
// Slice 90
    i++;
    if(i < 128 && array[90] == key && found == 0)
    {
	index = 90;
	found = 1;
    }
// Slice 91
    i++;
    if(i < 128 && array[91] == key && found == 0)
    {
	index = 91;
	found = 1;
    }
// Slice 92
    i++;
    if(i < 128 && array[92] == key && found == 0)
    {
	index = 92;
	found = 1;
    }
// Slice 93
    i++;
    if(i < 128 && array[93] == key && found == 0)
    {
	index = 93;
	found = 1;
    }
// Slice 94
    i++;
    if(i < 128 && array[94] == key && found == 0)
    {
	index = 94;
	found = 1;
    }
// Slice 95
    i++;
    if(i < 128 && array[95] == key && found == 0)
    {
	index = 95;
	found = 1;
    }
// Slice 96
    i++;
    if(i < 128 && array[96] == key && found == 0)
    {
	index = 96;
	found = 1;
    }
// Slice 97
    i++;
    if(i < 128 && array[97] == key && found == 0)
    {
	index = 97;
	found = 1;
    }
// Slice 98
    i++;
    if(i < 128 && array[98] == key && found == 0)
    {
	index = 98;
	found = 1;
    }
// Slice 99
    i++;
    if(i < 128 && array[99] == key && found == 0)
    {
	index = 99;
	found = 1;
    }
// Slice 100
    i++;
    if(i < 128 && array[100] == key && found == 0)
    {
	index = 100;
	found = 1;
    }
// Slice 101
    i++;
    if(i < 128 && array[101] == key && found == 0)
    {
	index = 101;
	found = 1;
    }
// Slice 102
    i++;
    if(i < 128 && array[102] == key && found == 0)
    {
	index = 102;
	found = 1;
    }
// Slice 103
    i++;
    if(i < 128 && array[103] == key && found == 0)
    {
	index = 103;
	found = 1;
    }
// Slice 104
    i++;
    if(i < 128 && array[104] == key && found == 0)
    {
	index = 104;
	found = 1;
    }
// Slice 105
    i++;
    if(i < 128 && array[105] == key && found == 0)
    {
	index = 105;
	found = 1;
    }
// Slice 106
    i++;
    if(i < 128 && array[106] == key && found == 0)
    {
	index = 106;
	found = 1;
    }
// Slice 107
    i++;
    if(i < 128 && array[107] == key && found == 0)
    {
	index = 107;
	found = 1;
    }
// Slice 108
    i++;
    if(i < 128 && array[108] == key && found == 0)
    {
	index = 108;
	found = 1;
    }
// Slice 109
    i++;
    if(i < 128 && array[109] == key && found == 0)
    {
	index = 109;
	found = 1;
    }
// Slice 110
    i++;
    if(i < 128 && array[110] == key && found == 0)
    {
	index = 110;
	found = 1;
    }
// Slice 111
    i++;
    if(i < 128 && array[111] == key && found == 0)
    {
	index = 111;
	found = 1;
    }
// Slice 112
    i++;
    if(i < 128 && array[112] == key && found == 0)
    {
	index = 112;
	found = 1;
    }
// Slice 113
    i++;
    if(i < 128 && array[113] == key && found == 0)
    {
	index = 113;
	found = 1;
    }
// Slice 114
    i++;
    if(i < 128 && array[114] == key && found == 0)
    {
	index = 114;
	found = 1;
    }
// Slice 115
    i++;
    if(i < 128 && array[115] == key && found == 0)
    {
	index = 115;
	found = 1;
    }
// Slice 116
    i++;
    if(i < 128 && array[116] == key && found == 0)
    {
	index = 116;
	found = 1;
    }
// Slice 117
    i++;
    if(i < 128 && array[117] == key && found == 0)
    {
	index = 117;
	found = 1;
    }
// Slice 118
    i++;
    if(i < 128 && array[118] == key && found == 0)
    {
	index = 118;
	found = 1;
    }
// Slice 119
    i++;
    if(i < 128 && array[119] == key && found == 0)
    {
	index = 119;
	found = 1;
    }
// Slice 120
    i++;
    if(i < 128 && array[120] == key && found == 0)
    {
	index = 120;
	found = 1;
    }
// Slice 121
    i++;
    if(i < 128 && array[121] == key && found == 0)
    {
	index = 121;
	found = 1;
    }
// Slice 122
    i++;
    if(i < 128 && array[122] == key && found == 0)
    {
	index = 122;
	found = 1;
    }
// Slice 123
    i++;
    if(i < 128 && array[123] == key && found == 0)
    {
	index = 123;
	found = 1;
    }
// Slice 124
    i++;
    if(i < 128 && array[124] == key && found == 0)
    {
	index = 124;
	found = 1;
    }
// Slice 125
    i++;
    if(i < 128 && array[125] == key && found == 0)
    {
	index = 125;
	found = 1;
    }
// Slice 126
    i++;
    if(i < 128 && array[126] == key && found == 0)
    {
	index = 126;
	found = 1;
    }
// Slice 127
    i++;
    if(i < 128 && array[127] == key && found == 0)
    {
	index = 127;
	found = 1;
    }

    return index;
}
int main()
{
	return 0;
}
