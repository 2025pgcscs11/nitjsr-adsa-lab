#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
typedef struct {
    int u, v, w;  // vertices and weight
} Edge;

// Structure for Disjoint Set Union (DSU)
typedef struct {
    int *parent;
    int *rank;
    int n;
} DSU;

// Create DSU
DSU* createDSU(int n) {
    DSU* dsu = (DSU*)malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

// Find with path compression
int find(DSU* dsu, int x) {
    if (dsu->parent[x] != x)
        dsu->parent[x] = find(dsu, dsu->parent[x]);
    return dsu->parent[x];
}

// Union by rank
void unionSet(DSU* dsu, int x, int y) {
    int rootX = find(dsu, x);
    int rootY = find(dsu, y);

    if (rootX != rootY) {
        if (dsu->rank[rootX] < dsu->rank[rootY]) {
            dsu->parent[rootX] = rootY;
        } else if (dsu->rank[rootX] > dsu->rank[rootY]) {
            dsu->parent[rootY] = rootX;
        } else {
            dsu->parent[rootY] = rootX;
            dsu->rank[rootX]++;
        }
    }
}

// Comparator for sorting edges by weight
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->w - e2->w;
}

// Kruskal’s Algorithm
void KruskalAlgorithm(int v, Edge edges[], int e) {
    qsort(edges, e, sizeof(Edge), compareEdges);

    DSU* dsu = createDSU(v);

    int cost = 0;
    printf("\nEdges in MST:\n");

    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v2 = edges[i].v;
        int w = edges[i].w;

        if (find(dsu, u) != find(dsu, v2)) {
            printf("%d - %d (weight %d)\n", u, v2, w);
            cost += w;
            unionSet(dsu, u, v2);
        }
    }

    printf("Minimum cost: %d\n", cost);

    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int main() {
    int v, e;
    printf("Enter number of Vertex in the Graph: ");
    scanf("%d", &v);
    printf("Enter number of Edge in the Graph: ");
    scanf("%d", &e);

    Edge* edges = (Edge*)malloc(e * sizeof(Edge));

    printf("Enter the edges (u v w):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    KruskalAlgorithm(v, edges, e);

    free(edges);
    return 0;
}
