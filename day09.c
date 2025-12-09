#include "base.h"

#define BUFSIZE 32
#define SIZE 512

typedef struct vec2 {
    i32 x, y;
} vec2;
typedef vec2 point;

i32
i32_cmp(const void *a, const void *b)
{
    return cmp(*(i32 *)a, *(i32 *)b);
}

void
dedup(i32 arr[SIZE], u32 *size)
{
    u32 newSize = 1;
    for (u32 i = 1; i < *size; i++)
        if (arr[i] != arr[i - 1]) arr[newSize++] = arr[i];
    *size = newSize;
}

u64
pt1(point grid[SIZE], u32 n)
{
    u64 res = 0;
    for (u32 i = 0; i < n; i++)
    {
        for (u32 j = i + 1; j < n; j++)
        {
            u64 w = abs(grid[i].x - grid[j].x) + 1;
            u64 h = abs(grid[i].y - grid[j].y) + 1;
            res = max(res, w * h);
        }
    }
    return res;
}

u64
pt2(point grid[SIZE], u32 n)
{
    i32 xs[SIZE], ys[SIZE];
    u32 nx = n, ny = n;
    for (u32 i = 0; i < n; i++)
    {
        xs[i] = grid[i].x;
        ys[i] = grid[i].y;
    }
    qsort(xs, nx, sizeof(i32), i32_cmp);
    qsort(ys, ny, sizeof(i32), i32_cmp);
    dedup(xs, &nx);
    dedup(ys, &ny);

    return 0;
}

i32
main(void)
{
    FILE *f = fopen("data/day09.test.txt", "r");
    char buf[BUFSIZE];
    point grid[SIZE];
    u32 n = 0;
    while (fscanf(f, "%d,%d\n", &grid[n].x, &grid[n].y) == 2)
        n++;

    printf("day 09 pt1: %llu\n", pt1(grid, n));
    printf("day 09 pt2: %llu\n", pt2(grid, n));

    fclose(f);
    return 0;
}
