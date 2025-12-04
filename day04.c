#include "base.h"

#define SIZE 512

u32
adj(const bool grid[SIZE][SIZE], u32 row, u32 col)
{
    u32 count = 0;
    if (grid[row - 1][col - 1]) count++;
    if (grid[row - 1][col]) count++;
    if (grid[row - 1][col + 1]) count++;
    if (grid[row][col - 1]) count++;
    if (grid[row][col + 1]) count++;
    if (grid[row + 1][col - 1]) count++;
    if (grid[row + 1][col]) count++;
    if (grid[row + 1][col + 1]) count++;
    return count;
}

u64
pt1(const bool grid[SIZE][SIZE], u32 rows, u32 cols)
{
    u64 res = 0;
    for (u32 i = 1; i < rows - 1; i++)
    {
        for (u32 j = 1; j < cols - 1; j++)
        {
            if (grid[i][j] && adj(grid, i, j) < 4)
            {
                res++;
            }
        }
    }
    return res;
}

u64
pt2(bool grid[SIZE][SIZE], u32 rows, u32 cols)
{
    u64 res = 0;
    while (true)
    {
        u64 intermediate = 0;
        for (u32 i = 1; i < rows - 1; i++)
        {
            for (u32 j = 1; j < cols - 1; j++)
            {
                if (grid[i][j] && adj(grid, i, j) < 4)
                {
                    intermediate++;
                    // this will cause other grid elements to possibly be
                    // removed earlier than they should, but it doesn't matter
                    // since they will be removed at some point anyway
                    grid[i][j] = false;
                }
            }
        }
        res += intermediate;
        if (intermediate == 0) break;
    }
    return res;
}

i32
main(void)
{
    FILE *f = fopen("data/day04.txt", "r");
    char buf[SIZE];
    bool grid[SIZE][SIZE] = { false };

    fgets(buf, SIZE, f);
    u32 dim = strlen(buf) - 1;
    rewind(f);

    u32 rows = dim + 2;
    u32 cols = dim + 2;
    for (u32 i = 1; fgets(buf, SIZE, f) && i < rows - 1; i++)
        for (u32 j = 1; j < cols - 1; j++)
            grid[i][j] = buf[j - 1] == '@';

    printf("day04 pt1: %llu\n", pt1(grid, rows, cols));
    printf("day04 pt2: %llu\n", pt2(grid, rows, cols));
    fclose(f);
    return 0;
}
