#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int n, e, m;
int found = 0;

// Function to check if the current subset of size k forms a clique
int is_clique(int subset[], int k) {
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (!graph[subset[i]][subset[j]])
                return 0;
        }
    }
    return 1;
}

// Recursive backtracking to generate subsets and check for clique
void find_clique(int start, int subset[], int k) {
    if (k == m) {
        if (is_clique(subset, m)) {
            found = 1;
            printf("Clique of size %d found: ", m);
            for (int i = 0; i < m; i++)
                printf("%d ", subset[i]);
            printf("\n");
        }
        return;
    }

    for (int i = start; i < n; i++) {
        subset[k] = i;
        find_clique(i + 1, subset, k + 1);
    }
}

int main() {
    printf("Enter number of vertices (n) and edges (e): ");
    scanf("%d %d", &n, &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    printf("Enter clique size (m): ");
    scanf("%d", &m);

    int subset[MAX];
    find_clique(0, subset, 0);

    if (!found)
        printf("No clique of size %d found.\n", m);

    return 0;
}

// Enter number of vertices (n) and edges (e): 5 6
// Enter the edges (u v):
// 0 1
// 0 2
// 1 2
// 1 3
// 2 3
// 3 4
// Enter clique size (m): 3
// Clique of size 3 found: 0 1 2 
// Clique of size 3 found: 1 2 3 