#include "base.h"

#define ROWS 8
#define COLS 4096
#define BUFSIZE 8192

u64
math(u32 inputs[ROWS][COLS], bool ops[COLS], u32 rows, u32 cols)
{
    u64 res = 0;
    for (u32 j = 0; j < cols; j++)
    {
        u64 cur;
        if (ops[j]) cur = 0; // addition
        else cur = 1;        // multiplication
        for (u32 i = 0; i < rows; i++)
        {
            if (ops[j]) cur += inputs[i][j];
            else cur *= inputs[i][j];
        }
        res += cur;
    }
    return res;
}

u64
pt1(char bufs[ROWS][BUFSIZE], bool ops[COLS], u32 rows, u32 cols)
{
    u32 input[ROWS][COLS];
    for (u32 i = 0; i < rows; i++)
    {
        char *ptr = bufs[i];
        for (u32 j = 0; j < cols; j++)
        {
            while (*ptr == ' ')
                ptr++;
            assert(sscanf(ptr, "%u", &input[i][j]));
            ptr = strchr(ptr, ' ');
        }
    }
    return math(input, ops, rows, cols);
}

u64
pt2(char bufs[ROWS][BUFSIZE], bool ops[COLS], u32 rows, u32 cols)
{
    u32 input[ROWS][COLS];
    for (u32 j = 0; j < cols; j++)
    {
        for (u32 i = 0; i < rows; i++)
        {
            if (ops[j]) input[i][j] = 0;
            else input[i][j] = 1;
        }
    }
    u32 colIdx = 0;
    u32 rowIdx = 0;
    for (u32 j = 0; j < strlen(bufs[rows]); j++)
    {
        char str[ROWS];
        bool empty = true;
        for (u32 i = 0; i < rows; i++)
        {
            str[i] = bufs[i][j];
            if (isdigit(str[i])) empty = false;
        }
        if (empty)
        {
            colIdx++;
            rowIdx = 0;
        }
        else
        {
            u32 num = atoi(str);
            input[rowIdx++][colIdx] = num;
        }
    }
    return math(input, ops, rows, cols);
}

i32
main(void)
{
    FILE *f = fopen("data/day06.txt", "r");
    char bufs[ROWS][BUFSIZE];
    bool ops[COLS];

    u32 rows = 0;
    u32 cols = 0;
    u32 input1[ROWS][COLS];
    while (fgets(bufs[rows], BUFSIZE, f) != NULL)
        rows += 1;
    rows -= 1;

    for (char *ptr = bufs[rows]; *ptr != '\0'; ptr++)
    {
        if (*ptr == '+') ops[cols++] = true;
        else if (*ptr == '*') ops[cols++] = false;
    }

    printf("day06 pt1: %llu\n", pt1(bufs, ops, rows, cols));
    printf("day06 pt2: %llu\n", pt2(bufs, ops, rows, cols));

    fclose(f);
    return 0;
}
