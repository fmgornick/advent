#include "base.h"

#define BUFSIZE 32

typedef struct vertex {
    u32 x, y, z;
} vertex;

typedef struct edge {
    u32 u, v;
} edge;

typedef struct forest {
    u32 *parent;
    u32 *partitionSize;
} forest;

forest
init_forest(u32 n)
{
    u32 *parent = malloc(n * sizeof(u32));
    u32 *partitionSize = malloc(n * sizeof(u32));
    for (u32 i = 0; i < n; i++)
    {
        parent[i] = i;
        partitionSize[i] = 1;
    }
    return (forest){ parent, partitionSize };
}

void
free_forest(forest f)
{
    free(f.parent);
    free(f.partitionSize);
}

u32
find(forest f, u32 i)
{
    if (f.parent[i] == i) return i;
    else return find(f, f.parent[i]);
}

void
merge(forest f, u32 i, u32 j)
{
    u32 irep = find(f, i);
    u32 jrep = find(f, j);
    f.parent[irep] = jrep;
    f.partitionSize[jrep] += f.partitionSize[irep];
    f.partitionSize[irep] = 0;
}

u64
weight(vertex u, vertex v)
{
    i64 dx = (i64)u.x - v.x;
    i64 dy = (i64)u.y - v.y;
    i64 dz = (i64)u.z - v.z;
    return (dx * dx) + (dy * dy) + (dz * dz);
}

void
quicksort_helper(edge *E, u64 *aux, i32 lo, i32 hi)
{
    if (lo >= hi) return;
    u64 pivot = aux[hi];
    i32 i = lo - 1;
    for (i32 j = lo; j <= hi - 1; j++)
    {
        if (aux[j] < pivot)
        {
            i++;
            edge eTmp = E[i];
            E[i] = E[j];
            E[j] = eTmp;
            u64 auxTmp = aux[i];
            aux[i] = aux[j];
            aux[j] = auxTmp;
        }
    }
    i32 pivotIdx = i + 1;
    edge eTmp = E[pivotIdx];
    E[pivotIdx] = E[hi];
    E[hi] = eTmp;
    u64 auxTmp = aux[pivotIdx];
    aux[pivotIdx] = aux[hi];
    aux[hi] = auxTmp;
    quicksort_helper(E, aux, lo, pivotIdx - 1);
    quicksort_helper(E, aux, pivotIdx + 1, hi);
}

void
quicksort(edge *E, vertex *V, u32 n)
{
    u64 *aux = malloc(n * sizeof(u64));
    for (u32 i = 0; i < n; i++)
    {
        aux[i] = weight(V[E[i].u], V[E[i].v]);
    }
    quicksort_helper(E, aux, 0, n - 1);
    free(aux);
}

u64
pt1(vertex *V, edge *E, u32 v, u32 e, u32 n)
{
    forest f = init_forest(v);
    for (u32 i = 0; i < n; i++)
    {
        if (find(f, E[i].u) != find(f, E[i].v))
        {
            merge(f, E[i].u, E[i].v);
        }
    }

    u64 res = 1;
    for (u32 i = 0; i < 3; i++)
    {
        u32 max = 0, maxIdx = 0;
        for (u32 j = 0; j < v; j++)
        {
            u32 sz = f.partitionSize[j];
            if (f.partitionSize[j] > max)
            {
                max = f.partitionSize[j];
                maxIdx = j;
            }
        }
        f.partitionSize[maxIdx] = 0;
        res *= max;
    }

    free_forest(f);
    return res;
}

u64
pt2(vertex *V, edge *E, u32 v, u32 e)
{
    forest f = init_forest(v);
    u32 connections = 0;
    for (u32 i = 0; i < e; i++)
    {
        if (find(f, E[i].u) != find(f, E[i].v))
        {
            merge(f, E[i].u, E[i].v);
            connections++;
            if (connections == v - 1)
            {
                return V[E[i].u].x * V[E[i].v].x;
            }
        }
    }
    return 0;
}

i32
main(void)
{
    FILE *f = fopen("data/day08.txt", "r");
    char buf[BUFSIZE];
    u32 v = 0;
    while (fgets(buf, BUFSIZE, f) != NULL)
        v++;
    rewind(f);

    vertex *V = malloc(v * sizeof(vertex));
    for (u32 i = 0; i < v; i++)
    {
        u32 x, y, z;
        assert(fscanf(f, "%u,%u,%u\n", &x, &y, &z) == 3);
        V[i] = (vertex){ x, y, z };
    }

    u32 e = (v * (v - 1)) / 2;
    edge *E = malloc(e * sizeof(edge));
    u32 idx = 0;
    for (u32 i = 0; i < v; i++)
    {
        for (u32 j = i + 1; j < v; j++)
        {
            E[idx++] = (edge){ i, j };
        }
    }
    quicksort(E, V, e);

    printf("day 08 pt1: %llu\n", pt1(V, E, v, e, 1000));
    printf("day 08 pt2: %llu\n", pt2(V, E, v, e));

    free(V);
    free(E);
    fclose(f);
    return 0;
}
