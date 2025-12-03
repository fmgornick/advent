#include "base.h"

i32
pt1(const char *data)
{
    const char *ptr = data;
    i32 pass = 0;
    i32 dial = 50;
    char dir;
    u32 count;

    while (1)
    {
        dir = *ptr++;
        if (sscanf(ptr, "%u", &count) != 1) break;
        if (dir == 'L') dial -= count;
        else if (dir == 'R') dial += count;
        else return -1;

        dial = mod(dial, 100);
        if (dial == 0) pass++;
        ptr = strchr(ptr, '\n');
        if (!ptr) break;
        ptr++;
    }

    return pass;
}

i32
pt2(const char *data)
{
    const char *ptr = data;
    i32 pass = 0;
    i32 dial = 50;
    char dir;
    u32 count;

    while (1)
    {
        dir = *ptr++;
        if (sscanf(ptr, "%u", &count) != 1) break;
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
        ptr = strchr(ptr, '\n');
        if (!ptr) break;
        ptr++;
    }

    return pass;
}

i32
main()
{
    FILE *f = fopen("data/day01.txt", "r");
    fseek(f, 0, SEEK_END);
    i64 filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char *)malloc(filesize * sizeof(char));
    fread(buf, sizeof(char), filesize, f);

    printf("day01 pt1: %d\n", pt1(buf));
    printf("day01 pt2: %d\n", pt2(buf));

    free(buf);
    fclose(f);

    return 0;
}
