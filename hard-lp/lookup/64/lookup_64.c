int lookup_64(int array[], int key)
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


int lookup_64_unr_full(int array[], int key)
{
    int found = 0, index = 0, i = 0;
    // Slice 0
    i++;
    if(i < 64 && array[0] == key && found == 0)
    {
	index = 0;
	found = 1;
    }
// Slice 1
    i++;
    if(i < 64 && array[1] == key && found == 0)
    {
	index = 1;
	found = 1;
    }
// Slice 2
    i++;
    if(i < 64 && array[2] == key && found == 0)
    {
	index = 2;
	found = 1;
    }
// Slice 3
    i++;
    if(i < 64 && array[3] == key && found == 0)
    {
	index = 3;
	found = 1;
    }
// Slice 4
    i++;
    if(i < 64 && array[4] == key && found == 0)
    {
	index = 4;
	found = 1;
    }
// Slice 5
    i++;
    if(i < 64 && array[5] == key && found == 0)
    {
	index = 5;
	found = 1;
    }
// Slice 6
    i++;
    if(i < 64 && array[6] == key && found == 0)
    {
	index = 6;
	found = 1;
    }
// Slice 7
    i++;
    if(i < 64 && array[7] == key && found == 0)
    {
	index = 7;
	found = 1;
    }
// Slice 8
    i++;
    if(i < 64 && array[8] == key && found == 0)
    {
	index = 8;
	found = 1;
    }
// Slice 9
    i++;
    if(i < 64 && array[9] == key && found == 0)
    {
	index = 9;
	found = 1;
    }
// Slice 10
    i++;
    if(i < 64 && array[10] == key && found == 0)
    {
	index = 10;
	found = 1;
    }
// Slice 11
    i++;
    if(i < 64 && array[11] == key && found == 0)
    {
	index = 11;
	found = 1;
    }
// Slice 12
    i++;
    if(i < 64 && array[12] == key && found == 0)
    {
	index = 12;
	found = 1;
    }
// Slice 13
    i++;
    if(i < 64 && array[13] == key && found == 0)
    {
	index = 13;
	found = 1;
    }
// Slice 14
    i++;
    if(i < 64 && array[14] == key && found == 0)
    {
	index = 14;
	found = 1;
    }
// Slice 15
    i++;
    if(i < 64 && array[15] == key && found == 0)
    {
	index = 15;
	found = 1;
    }
// Slice 16
    i++;
    if(i < 64 && array[16] == key && found == 0)
    {
	index = 16;
	found = 1;
    }
// Slice 17
    i++;
    if(i < 64 && array[17] == key && found == 0)
    {
	index = 17;
	found = 1;
    }
// Slice 18
    i++;
    if(i < 64 && array[18] == key && found == 0)
    {
	index = 18;
	found = 1;
    }
// Slice 19
    i++;
    if(i < 64 && array[19] == key && found == 0)
    {
	index = 19;
	found = 1;
    }
// Slice 20
    i++;
    if(i < 64 && array[20] == key && found == 0)
    {
	index = 20;
	found = 1;
    }
// Slice 21
    i++;
    if(i < 64 && array[21] == key && found == 0)
    {
	index = 21;
	found = 1;
    }
// Slice 22
    i++;
    if(i < 64 && array[22] == key && found == 0)
    {
	index = 22;
	found = 1;
    }
// Slice 23
    i++;
    if(i < 64 && array[23] == key && found == 0)
    {
	index = 23;
	found = 1;
    }
// Slice 24
    i++;
    if(i < 64 && array[24] == key && found == 0)
    {
	index = 24;
	found = 1;
    }
// Slice 25
    i++;
    if(i < 64 && array[25] == key && found == 0)
    {
	index = 25;
	found = 1;
    }
// Slice 26
    i++;
    if(i < 64 && array[26] == key && found == 0)
    {
	index = 26;
	found = 1;
    }
// Slice 27
    i++;
    if(i < 64 && array[27] == key && found == 0)
    {
	index = 27;
	found = 1;
    }
// Slice 28
    i++;
    if(i < 64 && array[28] == key && found == 0)
    {
	index = 28;
	found = 1;
    }
// Slice 29
    i++;
    if(i < 64 && array[29] == key && found == 0)
    {
	index = 29;
	found = 1;
    }
// Slice 30
    i++;
    if(i < 64 && array[30] == key && found == 0)
    {
	index = 30;
	found = 1;
    }
// Slice 31
    i++;
    if(i < 64 && array[31] == key && found == 0)
    {
	index = 31;
	found = 1;
    }
// Slice 32
    i++;
    if(i < 64 && array[32] == key && found == 0)
    {
	index = 32;
	found = 1;
    }
// Slice 33
    i++;
    if(i < 64 && array[33] == key && found == 0)
    {
	index = 33;
	found = 1;
    }
// Slice 34
    i++;
    if(i < 64 && array[34] == key && found == 0)
    {
	index = 34;
	found = 1;
    }
// Slice 35
    i++;
    if(i < 64 && array[35] == key && found == 0)
    {
	index = 35;
	found = 1;
    }
// Slice 36
    i++;
    if(i < 64 && array[36] == key && found == 0)
    {
	index = 36;
	found = 1;
    }
// Slice 37
    i++;
    if(i < 64 && array[37] == key && found == 0)
    {
	index = 37;
	found = 1;
    }
// Slice 38
    i++;
    if(i < 64 && array[38] == key && found == 0)
    {
	index = 38;
	found = 1;
    }
// Slice 39
    i++;
    if(i < 64 && array[39] == key && found == 0)
    {
	index = 39;
	found = 1;
    }
// Slice 40
    i++;
    if(i < 64 && array[40] == key && found == 0)
    {
	index = 40;
	found = 1;
    }
// Slice 41
    i++;
    if(i < 64 && array[41] == key && found == 0)
    {
	index = 41;
	found = 1;
    }
// Slice 42
    i++;
    if(i < 64 && array[42] == key && found == 0)
    {
	index = 42;
	found = 1;
    }
// Slice 43
    i++;
    if(i < 64 && array[43] == key && found == 0)
    {
	index = 43;
	found = 1;
    }
// Slice 44
    i++;
    if(i < 64 && array[44] == key && found == 0)
    {
	index = 44;
	found = 1;
    }
// Slice 45
    i++;
    if(i < 64 && array[45] == key && found == 0)
    {
	index = 45;
	found = 1;
    }
// Slice 46
    i++;
    if(i < 64 && array[46] == key && found == 0)
    {
	index = 46;
	found = 1;
    }
// Slice 47
    i++;
    if(i < 64 && array[47] == key && found == 0)
    {
	index = 47;
	found = 1;
    }
// Slice 48
    i++;
    if(i < 64 && array[48] == key && found == 0)
    {
	index = 48;
	found = 1;
    }
// Slice 49
    i++;
    if(i < 64 && array[49] == key && found == 0)
    {
	index = 49;
	found = 1;
    }
// Slice 50
    i++;
    if(i < 64 && array[50] == key && found == 0)
    {
	index = 50;
	found = 1;
    }
// Slice 51
    i++;
    if(i < 64 && array[51] == key && found == 0)
    {
	index = 51;
	found = 1;
    }
// Slice 52
    i++;
    if(i < 64 && array[52] == key && found == 0)
    {
	index = 52;
	found = 1;
    }
// Slice 53
    i++;
    if(i < 64 && array[53] == key && found == 0)
    {
	index = 53;
	found = 1;
    }
// Slice 54
    i++;
    if(i < 64 && array[54] == key && found == 0)
    {
	index = 54;
	found = 1;
    }
// Slice 55
    i++;
    if(i < 64 && array[55] == key && found == 0)
    {
	index = 55;
	found = 1;
    }
// Slice 56
    i++;
    if(i < 64 && array[56] == key && found == 0)
    {
	index = 56;
	found = 1;
    }
// Slice 57
    i++;
    if(i < 64 && array[57] == key && found == 0)
    {
	index = 57;
	found = 1;
    }
// Slice 58
    i++;
    if(i < 64 && array[58] == key && found == 0)
    {
	index = 58;
	found = 1;
    }
// Slice 59
    i++;
    if(i < 64 && array[59] == key && found == 0)
    {
	index = 59;
	found = 1;
    }
// Slice 60
    i++;
    if(i < 64 && array[60] == key && found == 0)
    {
	index = 60;
	found = 1;
    }
// Slice 61
    i++;
    if(i < 64 && array[61] == key && found == 0)
    {
	index = 61;
	found = 1;
    }
// Slice 62
    i++;
    if(i < 64 && array[62] == key && found == 0)
    {
	index = 62;
	found = 1;
    }
// Slice 63
    i++;
    if(i < 64 && array[63] == key && found == 0)
    {
	index = 63;
	found = 1;
    }

    return index;
}
int main()
{
	return 0;
}
