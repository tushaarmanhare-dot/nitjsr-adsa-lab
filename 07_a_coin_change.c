#include <stdio.h>

void greedyCoinChange(int coins[], int n, int amount) {
    printf("Coins used to make change for %d:\n", amount);
    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main() {
    // Available coin denominations (sorted in descending order)
    int coins[] = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount: ");
    scanf("%d", &amount);

    greedyCoinChange(coins, n, amount);

    return 0;
}
