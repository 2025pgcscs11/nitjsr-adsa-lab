#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct {
    int v;
    int w;
} Edge;

int timeCounter = 0;

void DFSVisit(int u, int **adj, int *deg, int *color, int *disc, int *fin, int *parent, int n) {
    color[u] = GRAY;
    disc[u] = ++timeCounter;

    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];

        if (color[v] == WHITE) {
            printf("Tree Edge: %d -> %d\n", u, v);
            parent[v] = u;
            DFSVisit(v, adj, deg, color, disc, fin, parent, n);
        } 
        else if (color[v] == GRAY) {
            printf("Back Edge: %d -> %d\n", u, v);
        } 
        else if (color[v] == BLACK) {
            if (disc[u] < disc[v]) {
                printf("Forward Edge: %d -> %d\n", u, v);
            } else {
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    color[u] = BLACK;
    fin[u] = ++timeCounter;
}

void DFS(int n, int **adj, int *deg) {
    int *color = calloc(n, sizeof(int));
    int *disc = calloc(n, sizeof(int));
    int *fin = calloc(n, sizeof(int));
    int *parent = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        color[i] = WHITE;
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == WHITE) {
            DFSVisit(i, adj, deg, color, disc, fin, parent, n);
        }
    }

    free(color);
    free(disc);
    free(fin);
    free(parent);
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    int **adj = malloc(n * sizeof(int *));
    int *deg = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        adj[i] = malloc(n * sizeof(int));

    printf("Enter directed edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][deg[u]++] = v;  // directed graph
    }

    printf("\nDFS Edge Classification:\n");
    DFS(n, adj, deg);

    for (int i = 0; i < n; i++)
        free(adj[i]);
    free(adj);
    free(deg);

    return 0;
}
