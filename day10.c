#include "base.h"

#define SIZE 256
#define V 256
#define MAXQ 256

i32
i16_desc(const void *a, const void *b)
{
    return -cmp(*(i16 *)a, *(i16 *)b);
}

void
print_bits(u16 mask, u16 count)
{
    for (i32 k = count - 1; k >= 0; k--)
        printf("%d ", (mask >> k) & 1);
    printf(" (%d)\n", mask);
}

u64
pt1(u16 indicators[SIZE], u16 buttons[SIZE][32], u32 joltages[SIZE][16], u32 n)
{
    u16 *queue = malloc((1 << 10) * sizeof(u16)); // queued up buttons
    u8 *dist = malloc((1 << 10) * sizeof(u8));    // number of xors

    u64 res = 0;
    for (u32 i = 0; i < n; i++)
    {
        u16 target = indicators[i];
        u16 m = 1 << joltages[i][0];
        u64 head = 0, tail = 0;
        memset(queue, 0, m);
        memset(dist, 0xFF, m);
        dist[0] = 0;
        queue[tail++] = 0;
        bool found = false;
        while (head < tail && !found)
        {
            u16 cur = queue[head++];
            u16 curd = dist[cur];
            for (u32 j = 1; j <= buttons[i][0]; j++)
            {
                u16 next = cur ^ buttons[i][j];
                if (dist[next] == 0xFF)
                {
                    dist[next] = curd + 1;
                    if (next == target)
                    {
                        res += dist[next];
                        found = true;
                        break;
                    }
                    queue[tail++] = next;
                }
            }
        }
    }

    free(queue);
    free(dist);
    return res;
}

u64
dp(u16 target, u16 **tab1, u16 **tab2, u32 n)
{
    for (u32 i = 0; i < n; i++)
    {
    }
}

// u64
// pt2(u16 indicators[SIZE], u16 buttons[SIZE][32], u32 joltages[SIZE][16], u32 n)
// {
//     u16 *queue = malloc((1 << 10) * sizeof(u16)); // queued up buttons
//     u8 *dist = malloc((1 << 10) * sizeof(u8));    // number of xors
//     u64 res = 0;
//     for (u32 i = 0; i < n; i++)
//     {
//         u32 *target = joltages[i];
//         u16 m = joltages[i][0];
//         u16 M = 1 << m;
//         u64 head = 0, tail = 0;
//         memset(queue, 0, M * 16);
//         memset(dist, 0xFF, M);
//         dist[0] = 0;
//         memset(queue[tail++], 0, 16);
//         bool found = false;
//         while (head < tail && !found)
//         {
//             u32 *cur = queue[head++];
//             u16 curd = dist[cur];
//         }
//     }
//     return 0;
// }

i32
main()
{
    FILE *f = fopen("data/day10.txt", "r");
    char buf[SIZE];
    u32 n = 0;
    u16 indicators[SIZE] = { 0 };
    u16 buttons[SIZE][32] = { 0 };
    u32 joltages[SIZE][16] = { 0 };
    while (fgets(buf, SIZE, f) != NULL)
    {
        // indicators
        char *ptr = buf;
        assert(*ptr == '[');
        ptr++;
        for (u32 i = 0; *ptr != ']'; i++, ptr++)
            if (*ptr == '#') indicators[n] |= (1 << i);
        ptr += 2;

        // buttons
        for (u32 i = 1; *ptr == '('; i++)
        {
            while (*ptr != ')')
            {
                ptr++;
                buttons[n][i] |= (1 << (*ptr++ - '0'));
                if (*ptr == ')') break;
            }
            buttons[n][0]++;
            ptr += 2;
        }

        // joltages
        for (u32 i = 1; ptr != NULL; i++)
        {
            ptr++;
            joltages[n][0]++;
            joltages[n][i] = atoi(ptr);
            ptr = strchr(ptr, ',');
        }
        n++;
    }

    printf("day 10 pt1: %llu\n", pt1(indicators, buttons, joltages, n));
    printf("day 10 pt2: %llu\n", pt2(indicators, buttons, joltages, n));
    return 0;
}
