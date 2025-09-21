#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int w;   // weight
    int u;   // parent
    int v;   // vertex
} edge;

// Heap structure
struct Heap {
    edge *array;
    int count;
    int capacity;
};

struct Heap *CreateHeap(int capacity) {
    struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
    h->count = 0;
    h->capacity = capacity;
    h->array = (edge *)malloc(sizeof(edge) * h->capacity);
    return h;
}

void push(struct Heap *h, edge data) {
    int i = h->count++;
    while (i > 0 && data.w < h->array[(i - 1) / 2].w) {
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = data;
}

int LeftChild(struct Heap *h, int i) {
    int left = 2 * i + 1;
    return (left >= h->count) ? -1 : left;
}

int RightChild(struct Heap *h, int i) {
    int right = 2 * i + 2;
    return (right >= h->count) ? -1 : right;
}

void PercolateDown(struct Heap *h, int i) {
    int l, r, min;
    edge temp;
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if (l != -1 && h->array[l].w < h->array[i].w)
        min = l;
    else
        min = i;
    if (r != -1 && h->array[r].w < h->array[min].w)
        min = r;
    if (min != i) {
        temp = h->array[i];
        h->array[i] = h->array[min];
        h->array[min] = temp;
        PercolateDown(h, min);
    }
}

void pop(struct Heap *h) {
    if (h->count == 0) return;
    h->array[0] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, 0);
}

edge top(struct Heap *h) {
    return h->array[0];
}

void DestroyHeap(struct Heap *h) {
    if (h == NULL) return;
    free(h->array);
    free(h);
}

// Prim’s Algorithm
void PrimAlgorithm(int vertex, edge **list, int *edgeCount, int source) {
    struct Heap *pq = CreateHeap(vertex * vertex);
    int visited[vertex];
    for (int i = 0; i < vertex; i++) visited[i] = 0;

    // Start with dummy edge (weight 0, from -1 to source)
    edge start = {0, -1, source};
    push(pq, start);

    int cost = 0;
    printf("\nEdges in MST:\n");

    while (pq->count != 0) {
        edge e = top(pq);
        pop(pq);

        if (visited[e.v]) continue;
        visited[e.v] = 1;
        cost += e.w;

        if (e.u != -1) { // skip dummy start
            printf("%d - %d (weight %d)\n", e.u, e.v, e.w);
        }

        // Add neighbors
        for (int i = 0; i < edgeCount[e.v]; i++) {
            int v2 = list[e.v][i].v;
            int w2 = list[e.v][i].w;
            if (!visited[v2]) {
                edge next = {w2, e.v, v2};
                push(pq, next);
            }
        }
    }

    printf("Minimum cost: %d\n", cost);
    DestroyHeap(pq);
}

int main() {
    int v, e;
    printf("Enter number of Vertex in the Graph: ");
    scanf("%d", &v);
    printf("Enter number of Edge in the Graph: ");
    scanf("%d", &e);

    edge **Adjlist = malloc(v * sizeof(edge *));
    for (int i = 0; i < v; i++)
        Adjlist[i] = malloc(e * sizeof(edge));

    int edgeCount[v];
    for (int i = 0; i < v; i++) edgeCount[i] = 0;

    printf("Enter the edges (u v w):\n");
    for (int i = 0; i < e; i++) {
        int u, v2, w;
        scanf("%d %d %d", &u, &v2, &w);
        int idx = edgeCount[u]++;
        Adjlist[u][idx].v = v2;
        Adjlist[u][idx].w = w;
        idx = edgeCount[v2]++;
        Adjlist[v2][idx].v = u;
        Adjlist[v2][idx].w = w;
    }

    int source = 0;
    PrimAlgorithm(v, Adjlist, edgeCount, source);

    for (int i = 0; i < v; i++) free(Adjlist[i]);
    free(Adjlist);

    return 0;
}
