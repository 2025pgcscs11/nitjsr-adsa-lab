#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], stack[MAX], top = -1, V;

void topoDFS(int v) {
    visited[v] = 1;
    for (int i = 0; i < V; i++)
        if (adj[v][i] && !visited[i])
            topoDFS(i);
    stack[++top] = v;
}

int main() {
    int E, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    for (int i = 0; i < V; i++)
        if (!visited[i])
            topoDFS(i);

    printf("\nTopological Sort Order:\n");
    while (top != -1)
        printf("%d ", stack[top--]);
    printf("\n");

    return 0;
}
