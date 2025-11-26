#include <stdio.h>

int maxVal = 0;  // To store the maximum value found

void knapSackBT(int W, int wt[], int val[], int n, int i, int currW, int currV) {
    if (i == n) {
        if (currV > maxVal)
            maxVal = currV;
        return;
    }

    // Case 1: Exclude the current item
    knapSackBT(W, wt, val, n, i + 1, currW, currV);

    // Case 2: Include the current item (if it fits)
    if (currW + wt[i] <= W)
        knapSackBT(W, wt, val, n, i + 1, currW + wt[i], currV + val[i]);
}

int main() {
    int val[] = {60, 100, 120};
    int wt[]  = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    knapSackBT(W, wt, val, n, 0, 0, 0);
    printf("Maximum value in Knapsack = %d\n", maxVal);
    return 0;
}
