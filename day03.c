#include "base.h"

#define BUFSIZE 128

internal u64
calculate_charge(const char *bank, u32 battery_size)
{
    u32 len = strlen(bank) - 1;
    i32 max_idx = -1;
    u64 res = 0;
    for (i32 i = 0; i < battery_size; i++)
    {
        u32 max = 0;
        for (i32 j = max_idx + 1; j < len - (battery_size - 1 - i); j++)
        {
            if (bank[j] > max)
            {
                max = bank[j];
                max_idx = j;
            }
        }
        res += pow(10, battery_size - 1 - i) * (max - '0');
    }
    return res;
}

u64
pt1(FILE *f)
{
    char buf[BUFSIZE];
    u64 res = 0;
    while (fgets(buf, BUFSIZE, f))
    {
        res += calculate_charge(buf, 2);
    }
    return res;
}

u64
pt2(FILE *f)
{
    char buf[BUFSIZE];
    u64 res = 0;
    while (fgets(buf, BUFSIZE, f))
    {
        res += calculate_charge(buf, 12);
    }
    return res;
}

i32
main(void)
{
    FILE *f = fopen("data/day03.txt", "r");
    printf("day02 pt1: %llu\n", pt1(f));
    rewind(f);
    printf("day02 pt2: %llu\n", pt2(f));
    fclose(f);
    return 0;
}
