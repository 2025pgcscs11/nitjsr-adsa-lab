#include <stdio.h>
#include <limits.h>

#define N 10
#define INF 99999

int n;
int dist[N][N];
int dp[1 << N][N];

// ---------- Recursive DP for TSP ----------
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0)
            ans = (ans < dist[pos][city] + tsp(mask | (1 << city), city)) ?
                    ans : dist[pos][city] + tsp(mask | (1 << city), city);
    }
    return dp[mask][pos] = ans;
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);
    printf("Enter distance matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    printf("Minimum cost of travelling: %d\n", tsp(1, 0));

    return 0;
}
