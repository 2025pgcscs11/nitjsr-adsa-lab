#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 100

int adj[MAXV][MAXV];       // adjacency matrix
int visited[MAXV];         // visited array
int stackArr[MAXV];        // current DFS path
int inStack[MAXV];         // check if node is in current path
int top = -1;

int minCycle = INT_MAX, maxCycle = -1;

// Function to print a cycle from stack
void printCycle(int startIdx) {
    printf("Cycle: ");
    for (int i = startIdx; i <= top; i++)
        printf("%d ", stackArr[i]);
    printf("%d\n", stackArr[startIdx]); // close the cycle
}

// DFS to find cycles
void dfs(int u, int V) {
    visited[u] = 1;
    stackArr[++top] = u;
    inStack[u] = 1;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                dfs(v, V);
            } else if (inStack[v]) {
                // Found a cycle: v .. u
                int length = 1;
                int startIdx = top;
                while (stackArr[startIdx] != v) {
                    length++;
                    startIdx--;
                }
                if (length < minCycle) minCycle = length;
                if (length > maxCycle) maxCycle = length;

                // print cycle
                printCycle(startIdx + 1);
            }
        }
    }

    inStack[u] = 0;
    top--;
}

// Find cycles in graph
void findCycles(int V) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    for (int i = 0; i < V; i++)
        if (!visited[i]) dfs(i, V);

    if (minCycle == INT_MAX)
        printf("No cycles found.\n");
    else {
        printf("\nSmallest cycle length: %d\n", minCycle);
        printf("Largest cycle length: %d\n", maxCycle);
    }
}

int main() {
    int V, E, directed;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Is the graph directed? (1=yes, 0=no): ");
    scanf("%d", &directed);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        if (!directed) adj[v][u] = 1; // undirected graph
    }

    findCycles(V);

    return 0;
}
