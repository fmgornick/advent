#include "base.h"

#define SIZE 256

u64
pt1(const bool grid[SIZE][SIZE], u32 start, u32 rows, u32 cols)
{
    bool line[SIZE] = { false };
    line[start + 1] = true;
    u64 res = 0;
    for (u32 i = 0; i < rows; i++)
    {
        for (u32 j = 0; j < cols; j++)
        {
            if (grid[i][j] && line[j + 1])
            {
                line[j] = true;
                line[j + 2] = true;
                res++;
            }
        }
        for (u32 j = 0; j < cols; j++)
        {
            if (grid[i][j]) line[j + 1] = false;
        }
    }
    return res;
}

u64
pt2(const bool grid[SIZE][SIZE], u32 start, u32 rows, u32 cols)
{
    u64 line[SIZE] = { 0 };
    line[start + 1] = 1;
    for (u32 i = 0; i < rows; i++)
    {
        for (u32 j = 0; j < cols; j++)
        {
            if (grid[i][j] && line[j + 1])
            {
                line[j] += line[j + 1];
                line[j + 2] += line[j + 1];
            }
        }
        for (u32 j = 0; j < cols; j++)
        {
            if (grid[i][j]) line[j + 1] = 0;
        }
    }
    u64 res = 0;
    for (u32 i = 1; i <= rows; i++)
    {
        res += line[i];
    }
    return res;
}

i32
main(void)
{
    FILE *f = fopen("data/day07.txt", "r");
    char buf[SIZE];
    bool grid[SIZE][SIZE] = { false };
    fgets(buf, SIZE, f);

    u32 rows = 0;
    u32 cols = strchr(buf, '\n') - buf;
    u32 start = strchr(buf, 'S') - buf;
    while (fgets(buf, SIZE, f) != NULL)
    {
        for (u32 j = 0; j < cols; j++)
            if (buf[j] == '^') grid[rows][j] = true;
        rows++;
    }

    printf("day07 pt1: %llu\n", pt1(grid, start, rows, cols));
    printf("day07 pt2: %llu\n", pt2(grid, start, rows, cols));

    fclose(f);
    return 0;
}
