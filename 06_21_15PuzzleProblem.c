#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

typedef struct Node {
    int mat[N][N];
    int x, y;   // Blank tile coordinates
    int cost;   // Cost (misplaced tiles)
    int level;  // Number of moves
    struct Node* parent;
} Node;

int isSafe(int x, int y) { return (x >= 0 && x < N && y >= 0 && y < N); }

int calculateCost(int initial[N][N], int final[N][N]) {
    int count = 0;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent, int final[N][N]) {
    Node* node = (Node*) malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));

    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->cost = calculateCost(node->mat, final);
    node->level = level;
    node->parent = parent;
    node->x = newX;
    node->y = newY;

    return node;
}

void printMatrix(int mat[N][N]) {
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

void solve(int initial[N][N], int x, int y, int final[N][N]) {
    Node* root = newNode(initial, x, y, x, y, 0, NULL, final);
    root->cost = calculateCost(initial, final);

    Node* pq[1000]; // Simple priority queue
    int size = 0;
    pq[size++] = root;

    while (size) {
        int minIndex = 0;
        for (int i=1;i<size;i++)
            if (pq[i]->cost + pq[i]->level < pq[minIndex]->cost + pq[minIndex]->level)
                minIndex = i;

        Node* minNode = pq[minIndex];
        pq[minIndex] = pq[--size];

        if (minNode->cost == 0) {
            printPath(minNode);
            return;
        }

        for (int i=0;i<4;i++) {
            int newX = minNode->x + row[i];
            int newY = minNode->y + col[i];
            if (isSafe(newX, newY)) {
                Node* child = newNode(minNode->mat, minNode->x, minNode->y, newX, newY, minNode->level+1, minNode, final);
                pq[size++] = child;
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int final[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    int x = 1, y = 2; // Blank tile position
    solve(initial, x, y, final);

    return 0;
}

//  1  2  3  4 
//  5  6  0  8 
//  9 10  7 12 
// 13 14 11 15 

//  1  2  3  4 
//  5  6  7  8 
//  9 10  0 12 
// 13 14 11 15 

//  1  2  3  4 
//  5  6  7  8 
//  9 10 11 12 
// 13 14  0 15 

//  1  2  3  4 
//  5  6  7  8 
//  9 10 11 12 
// 13 14 15  0 
