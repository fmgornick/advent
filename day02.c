#include "base.h"

u64
pt1(const char *data)
{
    const char *ptr = data;
    char buf[32];
    u64 lo, hi;
    u64 res = 0;

    while (sscanf(ptr, "%llu-%llu", &lo, &hi) == 2)
    {
        for (u64 id = lo; id <= hi; id++)
        {
            snprintf(buf, sizeof(buf), "%llu", id);
            u32 len = strlen(buf);
            u32 half_len = len / 2;
            if (len % 2 == 0)
            {
                if (strncmp(buf, buf + half_len, half_len) == 0)
                {
                    res += id;
                }
            }
        }
        ptr = strchr(ptr, ',');
        if (!ptr) break;
        ptr++;
    }

    return res;
}

u64
pt2(const char *data)
{
    const char *ptr = data;
    char buf[32];
    u64 lo, hi;
    u64 res = 0;

    while (sscanf(ptr, "%llu-%llu", &lo, &hi) == 2)
    {
        for (u64 id = lo; id <= hi; id++)
        {
            snprintf(buf, sizeof(buf), "%llu", id);
            u32 len = strlen(buf);
            bool has_repitition = false;
            for (u32 seg_len = 1; seg_len <= len / 2; seg_len++)
            {
                if (len % seg_len != 0) continue;
                u32 num_segs = len / seg_len;
                bool repeated = true;
                for (u32 i = 0; i < num_segs; i++)
                {
                    if (strncmp(buf, buf + (seg_len * i), seg_len) != 0)
                    {
                        repeated = false;
                        break;
                    }
                }
                if (repeated) has_repitition = true;
            }
            if (has_repitition) res += id;
        }
        ptr = strchr(ptr, ',');
        if (!ptr) break;
        ptr++;
    }

    return res;
}

i32
main(void)
{
    FILE *f = fopen("data/day02.txt", "r");
    fseek(f, 0, SEEK_END);
    i64 size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char *)malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';

    printf("day02 pt1: %llu\n", pt1(buf));
    printf("day02 pt2: %llu\n", pt2(buf));

    free(buf);
    fclose(f);

    return 0;
}
