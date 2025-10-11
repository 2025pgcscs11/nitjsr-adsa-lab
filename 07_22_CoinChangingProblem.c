#include <stdio.h>
#include <stdlib.h>

void coinChangeGreedy(int coins[], int n, int amount) {
    // Sort coins in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (coins[i] < coins[j]) {
                int temp = coins[i];
                coins[i] = coins[j];
                coins[j] = temp;
            }
        }
    }

    printf("Coins used: ");
    int totalCoins = 0;
    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
            totalCoins++;
        }
    }

    printf("\nTotal coins used: %d\n", totalCoins);
}

int main() {
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 2000};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter amount: ");
    scanf("%d", &amount);

    coinChangeGreedy(coins, n, amount);
    return 0;
}
