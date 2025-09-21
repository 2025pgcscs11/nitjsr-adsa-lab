#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int x;
    int y;
} pair;

// Implementing Min Queue for priority Queue

// structure of the heap node
struct Heap
{
    pair *array;
    int count;
    int capacity;
};

// Initialize heap
struct Heap *CreateHeap(int capacity)
{
    struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
    if (h == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    h->count = 0;
    h->capacity = capacity;
    h->array = (pair *)malloc(sizeof(pair) * h->capacity);
    if (h->array == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    return h;
}

// Insert data(weight,vertex) in the heap
void push(struct Heap *h, pair data)
{
    int i;
    h->count++;
    i = h->count - 1;
    while (i > 0 && data.x < h->array[(i - 1) / 2].x)
    {
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = data;
}

// Return left child of a node
int LeftChild(struct Heap *h, int i)
{
    int left = 2 * i + 1;
    if (left >= h->count)
        return -1;
    return left;
}

// Return right child of a node
int RightChild(struct Heap *h, int i)
{
    int right = 2 * i + 2;
    if (right >= h->count)
        return -1;
    return right;
}

// Heapify the element at loction i
void PercolateDown(struct Heap *h, int i)
{
    int l, r, min;
    pair temp;
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if (l != -1 && h->array[l].x < h->array[i].x)
        min = l;
    else
        min = i;
    if (r != -1 && h->array[r].x < h->array[min].x)
        min = r;
    if (min != i)
    {
        temp = h->array[i];
        h->array[i] = h->array[min];
        h->array[min] = temp;
        PercolateDown(h, min);
    }
}

// Delete  root element of a heap
void pop(struct Heap *h)
{
    h->array[0] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, 0);
}

// Return min value of heap
pair top(struct Heap *h)
{
    return h->array[0];
}

// Destroy  the heap
void DestroyHeap(struct Heap *h)
{
    if (h == NULL)
        return;
    free(h->array);
    free(h);
    h = NULL;
}

// Utility Function for Dijkstra's Algorithm

// Initialize all the vertex with initial values
void Initilaize(int v, int s, int *d, int *pred)
{
    for (int i = 0; i < v; i++)
    {
        if (i != s)
        {
            d[i] = INT_MAX;
            pred[i] = -1;
        }
    }
    d[s] = 0;
    pred[s] = -1;
}

// Dijkstra's Algorithm
void DijkstraAlgorithm(int v, pair **list, int *edge, int s, int *d, int *pred)
{
    Initilaize(v, s, d, pred);
    struct Heap *pq = CreateHeap(v);
    pair curr;
    int visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    curr.x = d[s];
    curr.y = s;
    push(pq, curr);
    while (pq->count != 0)
    {
        int u = top(pq).y;
        pop(pq);
        for (int i = 0; i < edge[u]; i++)
        {
            int p = list[u][i].x;
            int q = list[u][i].y;
            if ((d[q] > d[u] + p) && visited[q] != 1)
            {
                d[q] = d[u] + p;
                pred[q] = u;
                curr.x = p;
                curr.y = q;
                push(pq, curr);
            }
            visited[u] = 1;
        }
    }
}

// Function to check distance from any source node
void check_distance_and_route_to_shortest_path(int v, pair **list, int *edge, int source, int destination, int *d, int *pred)
{
    DijkstraAlgorithm(v, list, edge, source, d, pred);
    printf("Shortest Distance between %d to %d is: %d\n", source, destination, d[destination]);
    int arr[v];
    int top = -1;
    int i = destination;
    while (i != source)
    {
        arr[++top] = i;
        i = pred[i];
    }
    arr[++top] = i;
    printf("The shortest route is:");
    while (top != -1)
    {
        if (top >= 1)
            printf(" %d ->", arr[top]);
        else
            printf(" %d", arr[top]);
        top--;
    }
}

int main()
{
    int v, e;
    printf("Enter number of Vertex in the Graph: ");
    scanf("%d", &v);
    printf("Enter number of Edge in the Graph:");
    scanf("%d", &e);
    pair **Adjlist = malloc(v * sizeof(pair *));
    for (int i = 0; i < v; i++)
        Adjlist[i] = malloc(e * sizeof(pair));

    int edge[v];
    for (int i = 0; i < v; i++)
        edge[i] = 0;
    printf("Enter the edge vertex with its weight: \n");
    for (int i = 1; i <= e; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        int idx = edge[u]++;
        Adjlist[u][idx].y = v;
        Adjlist[u][idx].x = w;
        idx = edge[v]++;
        Adjlist[v][idx].y = u;
        Adjlist[v][idx].x = w;
    }
    int distance[v];
    int predecessor[v];
    int source, destination;

    printf("Enter source and desination: ");
    scanf("%d %d", &source, &destination);
    if (source >= 0 && source < v)
    {
        if (destination >= 0 && destination < v)
        {
            check_distance_and_route_to_shortest_path(v, Adjlist, edge, source, destination, distance, predecessor);
        }
        else{
            printf("Invalid destination vertex is typed.\n");
        }
    }
    else{
        printf("Invalid source vertex is typed.\n");
    }
    return 0;
}