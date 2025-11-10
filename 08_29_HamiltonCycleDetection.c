#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;

// Check if current vertex can be added to the path
int isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

int hamCycleUtil(int pos) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return 1;
            path[pos] = -1;
        }
    }
    return 0;
}

int main() {
    int e;
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
        path[i] = -1;
    path[0] = 0;  // start from vertex 0

    if (hamCycleUtil(1)) {
        printf("Hamiltonian cycle found: ");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]); // return to start
    } else {
        printf("No Hamiltonian cycle exists.\n");
    }

    return 0;
}

// Enter number of vertices (n) and edges (e): 5 7
// Enter edges (u v):
// 0 1
// 0 2
// 1 2
// 1 3
// 2 3
// 3 4
// 4 0
// Hamiltonian cycle found: 0 1 2 3 4 0