#include <stdio.h>

#define MAX 20
#define UNCOLORED -1
#define RED 0
#define BLUE 1

int graph[MAX][MAX];
int color[MAX];
int n, e;

int isBipartite() {
    int queue[MAX], front = 0, rear = 0;

    for (int start = 0; start < n; start++) {
        if (color[start] == UNCOLORED) {
            color[start] = RED;
            queue[rear++] = start;

            while (front != rear) {
                int u = queue[front++];

                for (int v = 0; v < n; v++) {
                    if (graph[u][v]) {
                        if (color[v] == UNCOLORED) {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            return 0; // same color conflict
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    printf("Enter number of vertices (n) and edges (e): ");
    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++)
        color[i] = UNCOLORED;

    if (isBipartite())
        printf("Graph is Bipartite.\n");
    else
        printf("Graph is NOT Bipartite.\n");

    return 0;
}

// Enter number of vertices (n) and edges (e): 4 4
// Enter edges (u v):
// 0 1
// 0 3
// 2 1
// 2 3
// Graph is Bipartite