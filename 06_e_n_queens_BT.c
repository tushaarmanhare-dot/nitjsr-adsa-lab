#include <stdio.h>
#include <stdlib.h>
#define N 8  // Change N for different board sizes

int board[N];

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || (abs(board[i] - col) == abs(i - row)))
            return 0;
    return 1;
}

void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%s ", (board[i] == j) ? "Q" : ".");
        printf("\n");
    }
    printf("\n");
}

void solveNQueens(int row) {
    if (row == N) {  // All queens placed
        printSolution();
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solveNQueens(row + 1);
        }
    }
}

int main() {
    solveNQueens(0);
    return 0;
}
