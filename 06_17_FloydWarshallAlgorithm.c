#include <stdio.h>
#include <limits.h>

void Print2DArray(int n, int arr[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

int min(int a,int b){
    return a<b?a:b;
}

void FloydWarshallAlgorithm(int v, int mat[v][v], int pi[v][v]) {
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (mat[i][k] != INT_MAX && mat[k][j] != INT_MAX) {
                    if (mat[i][j] > mat[i][k] + mat[k][j]) {
                        pi[i][j] = pi[k][j];
                    }
                    mat[i][j] = min(mat[i][j],mat[i][k] + mat[k][j]);
                }
            }
        }
    }
}

void PrintPath(int v,int pi[v][v], int s, int d,int c) {
    if (pi[s][d] == -1) {
        printf("No path from %d to %d\n", s,d );
        return;
    }

    int path[v];
    int count = 0;

    int current = d;
    path[count++] = d;

    while (current != s) {
        current = pi[s][current];
        if (current == -1) {
            printf("No path from %d to %d\n", s, d);
            return;
        }
        path[count++] = current;
    }

    // Print path in correct order
    printf("Path from %d to %d: ", s, d);
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i != 0) printf(" -> ");
    }
    printf(" and it cost %d",c);
    printf("\n");
}

int main() {
    int v, e;
    printf("Enter number of vertices: ");
    scanf("%d", &v);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    int EdgeMatrix[v][v];
    int Pi[v][v];

    // Initialize adjacency matrix
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i == j)
                EdgeMatrix[i][j] = 0;
            else
                EdgeMatrix[i][j] = INT_MAX;
        }
    }

    // Input edges
    printf("Enter the edge with its weight (u v w):\n");
    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        EdgeMatrix[u][v] = w;
    }

    // Initialize Pi matrix
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            Pi[i][j] = -1;
            if (i != j && EdgeMatrix[i][j] < INT_MAX)
                Pi[i][j] = i;
        }
    }

    // From any node to any node cost and route
    FloydWarshallAlgorithm(v,EdgeMatrix,Pi);
    int source,destination;
    printf("Enter source and destination: ");
    scanf("%d %d",&source,&destination);
    if(source>=0 && source<v && destination>=0 && destination<v){
        PrintPath(v,Pi,source,destination,EdgeMatrix[source][destination]);
    }
    else{
        printf("Invalid Source and Destibation vertices has typed.\n");
    }
    // printf("\nShortest Path Matrix:\n");
    // Print2DArray(v, EdgeMatrix);

    // printf("\nPredecessor Matrix:\n");
    // Print2DArray(v, Pi);

    return 0;
}

// Enter number of vertices: 5
// Enter number of edges: 9
// Enter the edge with its weight (u v w):
// 0 1 3
// 0 2 8
// 0 4 -4
// 1 3 1
// 1 4 7
// 2 1 4
// 3 2 -5
// 3 0 2
// 4 3 6
// Enter source and destination: 0 2
// Path from 0 to 2: 0 -> 4 -> 3 -> 2 and it cost -3