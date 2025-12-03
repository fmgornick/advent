#include "base.h"

i32
pt1(const char *buf, size_t size)
{
    const char *ptr = buf;
    i32 pass = 0;
    i32 dial = 50;

    while (ptr < buf + size)
    {
        char dir = *ptr++;
        i32 count = atoi(ptr);
        while (*ptr != '\n' && ptr < buf + size)
            ptr++;
        ptr++;

        if (dir == 'L') dial -= count;
        else if (dir == 'R') dial += count;
        else return -1;

        dial = mod(dial, 100);
        if (dial == 0) pass++;
    }

    return pass;
}

i32
pt2(const char *buf, size_t size)
{
    const char *ptr = buf;
    i32 pass = 0;
    i32 dial = 50;

    while (ptr < buf + size)
    {
        char dir = *ptr++;
        i32 count = atoi(ptr);
        while (*ptr != '\n' && ptr < buf + size)
            ptr++;
        ptr++;

        if (dir == 'L')
        {
            pass += (count + (100 - dial)) / 100;
            if (dial == 0) pass -= 1;
            dial -= count;
        }
        else if (dir == 'R')
        {
            pass += (count + dial) / 100;
            dial += count;
        }
        else return -1;

        dial = mod(dial, 100);
    }

    return pass;
}

i32
main()
{
    FILE *f = fopen("data/day01.txt", "r");
    fseek(f, 0, SEEK_END);
    i64 filesize = ftell(f);
    rewind(f);

    char *buf = (char *)malloc(filesize * sizeof(char));
    fread(buf, sizeof(char), filesize, f);

    printf("day01 pt1: %d\n", pt1(buf, filesize));
    printf("day01 pt2: %d\n", pt2(buf, filesize));

    free(buf);
    fclose(f);

    return 0;
}
