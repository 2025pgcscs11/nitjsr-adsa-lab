#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapSackBackTracking(int i, int W, int wt[], int val[], int n) {
    if (i == n || W == 0)
        return 0;

    if (wt[i] > W)
        return knapSackBackTracking(i + 1, W, wt, val, n);

    int include = val[i] + knapSackBackTracking(i + 1, W - wt[i], wt, val, n);
    int exclude = knapSackBackTracking(i + 1, W, wt, val, n);

    return max(include, exclude);
}

int main() {
    int val[] = {60, 100, 120};
    int wt[]  = {10, 20, 30};
    int W = 50;
    int n = sizeof(val)/sizeof(val[0]);

    printf("Maximum value in Knapsack = %d\n", knapSackBackTracking(0, W, wt, val, n));
    return 0;
}
// Maximum value in Knapsack = 220