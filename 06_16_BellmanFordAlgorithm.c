#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int u;
    int v;
    int w;
} Edge;

// Initialize distances and predecessors
void Initialize(int v, int s, int *d, int *pred) {
    for (int i = 0; i < v; i++) {
        d[i] = INT_MAX;
        pred[i] = -1;
    }
    d[s] = 0;
}

// Bellman–Ford algorithm
bool BellmanFordAlgorithm(Edge edgelist[], int vertex, int edge, int s, int *d, int *pred) {
    Initialize(vertex, s, d, pred);

    // Relax edges (V - 1) times
    for (int i = 0; i < vertex - 1; i++) {
        for (int j = 0; j < edge; j++) {
            int u = edgelist[j].u;
            int v = edgelist[j].v;
            int w = edgelist[j].w;
            if (d[u] != INT_MAX && d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pred[v] = u;  
            }
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < edge; j++) {
        int u = edgelist[j].u;
        int v = edgelist[j].v;
        int w = edgelist[j].w;
        if (d[u] != INT_MAX && d[u] + w < d[v]) {
            return false; 
        }
    }

    return true;
}

// Print path using predecessor array
void PrintPath(int v, int *pred) {
    if (pred[v] == -1) {
        printf("%d", v);
        return;
    }
    PrintPath(pred[v], pred);
    printf(" -> %d", v);
}

int main() {
    int v, e;
    printf("Enter number of vertices: ");
    scanf("%d", &v);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    Edge Adjlist[e];
    printf("Enter edges in format (u v w):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &Adjlist[i].u, &Adjlist[i].v, &Adjlist[i].w);
    }

    int distance[v], predecessor[v];
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= v) {
        printf("Invalid source vertex.\n");
        return 0;
    }

    if (BellmanFordAlgorithm(Adjlist, v, e, source, distance, predecessor)) {
        printf("NEGATIVE EDGE CYCLE IS NOT PRESENT.\n");
        printf("Vertex   Distance   Path\n");
        for (int i = 0; i < v; i++) {
            if (distance[i] == INT_MAX) {
                printf("%d\t INF\t (unreachable)\n", i);
            } else {
                printf("%d\t %d\t ", i, distance[i]);
                PrintPath(i, predecessor);
                printf("\n");
            }
        }
    } else {
        printf("NEGATIVE EDGE CYCLE IS PRESENT.\n");
    }

    return 0;
}


// Enter number of vertices: 5
// Enter number of edges: 8
// Enter edges in format (u v w):
// 0 1 -1
// 0 2 4
// 1 2 3
// 1 3 2
// 1 4 2
// 3 2 5
// 3 1 1
// 4 3 -3
// Enter source vertex: 0
// NEGATIVE EDGE CYCLE IS NOT PRESENT.
// Vertex   Distance   Path
// 0        0       0
// 1        -1      0 -> 1
// 2        2       0 -> 1 -> 2
// 3        -2      0 -> 1 -> 4 -> 3
// 4        1       0 -> 1 -> 4


// Enter number of vertices: 4
// Enter number of edges: 5
// Enter edges in format (u v w):
// 0 1 1
// 1 2 -1
// 2 3 -1
// 3 1 -1
// 0 2 4
// Enter source vertex: 0
// NEGATIVE EDGE CYCLE IS PRESENT.