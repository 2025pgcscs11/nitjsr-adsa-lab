#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX], disc[MAX], low[MAX], parent[MAX];
int timeCounter = 0;
int V;

// ---------- Add Edge ----------
void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; // for articulation/bridge (undirected)
}

// ---------- Articulation Points & Bridges ----------
void APUtil(int u) {
    int children = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (!adj[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            APUtil(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (parent[u] == -1 && children > 1)
                printf("Articulation Point: %d\n", u);
            if (parent[u] != -1 && low[v] >= disc[u])
                printf("Articulation Point: %d\n", u);
            if (low[v] > disc[u])
                printf("Bridge: %d - %d\n", u, v);
        } else if (v != parent[u])
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
    }
}

// ---------- Strongly Connected Components (Kosaraju’s Algorithm) ----------
void DFS1(int v, int visited[], int stack[], int *top) {
    visited[v] = 1;
    for (int i = 0; i < V; i++)
        if (adj[v][i] && !visited[i])
            DFS1(i, visited, stack, top);
    stack[++(*top)] = v;
}

void DFS2(int v, int visited[], int transpose[MAX][MAX]) {
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 0; i < V; i++)
        if (transpose[v][i] && !visited[i])
            DFS2(i, visited, transpose);
}

void findSCCs() {
    int stack[MAX], top = -1;
    int visited[MAX] = {0};
    for (int i = 0; i < V; i++)
        if (!visited[i])
            DFS1(i, visited, stack, &top);

    int transpose[MAX][MAX] = {0};
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (adj[i][j])
                transpose[j][i] = 1;

    for (int i = 0; i < V; i++)
        visited[i] = 0;

    printf("\nStrongly Connected Components:\n");
    while (top != -1) {
        int v = stack[top--];
        if (!visited[v]) {
            DFS2(v, visited, transpose);
            printf("\n");
        }
    }
}

// ---------- Driver for AP, Bridge, SCC ----------
void graphAnalysis() {
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }

    for (int i = 0; i < V; i++)
        if (!visited[i])
            APUtil(i);
}

int main() {
    int E, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edge (u v): ");
    for (int i = 0; i < E; i++) {
       
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    printf("\n--- Strongly Connected Components ---\n");
    findSCCs();

    printf("\n--- Articulation Points and Bridges ---\n");
    graphAnalysis();

    return 0;
}
