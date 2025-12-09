#include "base.h"

#define SIZE 2048

typedef struct {
    u64 m, M;
} interval;

typedef struct interval_tree_node interval_tree_node;
struct interval_tree_node {
    interval_tree_node *left;
    interval_tree_node *right;
    u64 center;
    u32 numIntervals;
    interval intervals[SIZE];
};

i32
u64_cmp(const void *a, const void *b)
{
    return cmp(*(u64 *)a, *(u64 *)b);
}

i32
interval_cmp(const void *a, const void *b)
{
    return cmp((*(interval *)a).m, (*(interval *)b).m);
}

void
dedup(u64 arr[SIZE], u32 *size)
{
    u32 newSize = 1;
    for (u32 i = 1; i < *size; i++)
        if (arr[i] != arr[i - 1]) arr[newSize++] = arr[i];
    *size = newSize;
}

interval_tree_node *
build_interval_tree(interval intervals[SIZE], u32 numVertices)
{
    if (numVertices == 0) return NULL;
    i32 centerIdx = numVertices / 2;
    u64 center = intervals[centerIdx].m;
    interval_tree_node *node = (interval_tree_node *)malloc(sizeof(interval_tree_node));
    node->center = center;
    u32 num = 0;
    u32 numLeft = 0;
    u32 numRight = 0;
    interval left[SIZE];
    interval right[SIZE];
    for (i32 i = 0; i < numVertices; i++)
    {
        if (center >= intervals[i].m && center <= intervals[i].M) node->intervals[num++] = intervals[i];
        else if (center < intervals[i].m) right[numRight++] = intervals[i];
        else /* center > intervals[i].M */ left[numLeft++] = intervals[i];
    }
    node->numIntervals = num;
    node->left = build_interval_tree(left, numLeft);
    node->right = build_interval_tree(right, numRight);
    return node;
}

void
free_interval_tree(interval_tree_node *node)
{
    if (!node) return;
    if (node->left) free_interval_tree(node->left);
    if (node->right) free_interval_tree(node->right);
    free(node);
}

bool
intersect(interval_tree_node *node, interval query)
{
    if (!node || query.M < query.m) return false;
    for (u32 i = 0; i < node->numIntervals; i++)
    {
        interval cur = node->intervals[i];
        if ((query.m >= cur.m) && (query.m <= cur.M)) return true;
        if ((query.M >= cur.m) && (query.M <= cur.M)) return true;
    }
    if (query.M < node->center) return intersect(node->left, query);
    else return intersect(node->right, query);
}

u64
pt1(interval intervals[SIZE], u32 numIntervals, u64 queries[SIZE], u64 numQueries)
{
    qsort(intervals, numIntervals, sizeof(interval), interval_cmp);
    interval_tree_node *node = build_interval_tree(intervals, numIntervals);
    u64 res = 0;
    for (i32 i = 0; i < numQueries; i++)
    {
        if (intersect(node, (interval){ queries[i], queries[i] }))
        {
            res++;
        }
    }
    free_interval_tree(node);
    return res;
}

u64
pt2(interval intervals[SIZE], u32 numIntervals)
{
    qsort(intervals, numIntervals, sizeof(interval), interval_cmp);
    interval_tree_node *node = build_interval_tree(intervals, numIntervals);
    u64 endpoints[SIZE];
    u32 numEndpoints = numIntervals * 2;
    for (u32 i = 0; i < numIntervals; i++)
    {
        endpoints[2 * i] = intervals[i].m;
        endpoints[2 * i + 1] = intervals[i].M;
    }
    qsort(endpoints, numEndpoints, sizeof(u64), u64_cmp);
    dedup(endpoints, &numEndpoints);

    interval subints[SIZE];
    for (u32 i = 0; i < numEndpoints - 1; i++)
    {
        subints[i].m = endpoints[i] + 1;
        subints[i].M = endpoints[i + 1] - 1;
    }

    u64 res = numEndpoints;
    bool inSegment = false;
    u32 entered = 0;
    for (u32 i = 0; i < numEndpoints - 1; i++)
    {
        if (intersect(node, subints[i]))
        {
            res += subints[i].M - subints[i].m + 1;
        }
    }

    free_interval_tree(node);
    return res;
}

i32
main(void)
{
    FILE *f = fopen("data/day05.txt", "r");
    interval intervals[SIZE];
    u64 queries[SIZE];
    u32 numQueries = 0;
    u32 numIntervals = 0;
    char buf[SIZE];

    while (fgets(buf, SIZE, f))
    {
        if (sscanf(buf, "%llu-%llu\n", &intervals[numIntervals].m, &intervals[numIntervals].M) == 2)
        {
            numIntervals++;
        }
        else if (sscanf(buf, "%llu\n", &queries[numQueries]) == 1)
        {
            numQueries++;
        }
    }
    printf("day05 pt1: %llu\n", pt1(intervals, numIntervals, queries, numQueries));
    printf("day05 pt2: %llu\n", pt2(intervals, numIntervals));
    fclose(f);
    return 0;
}
