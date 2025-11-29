#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define INF 999999

// Structure to represent a state (node) in the search tree
typedef struct Node {
    int mat[N][N];
    int x, y;        // Blank tile coordinates
    int cost;        // Heuristic cost
    int level;       // Depth level
    struct Node *parent;
} Node;

// Goal state
int final[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9,10,11,12},
    {13,14,15,0}
};

// Directions: up, down, left, right
int row[] = { 1, -1, 0, 0 };
int col[] = { 0, 0, -1, 1 };

// Utility to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    *node = *parent;
    node->parent = parent;

    // Swap the blank tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    return node;
}

// Heuristic: number of misplaced tiles
int calculateCost(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != final[i][j])
                count++;
    return count;
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Recursive function to print path
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Branch and Bound solver
void solve(int initial[N][N], int x, int y) {
    Node* root = (Node*)malloc(sizeof(Node));
    *root = (Node){0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            root->mat[i][j] = initial[i][j];

    root->x = x;
    root->y = y;
    root->parent = NULL;
    root->level = 0;
    root->cost = calculateCost(initial);

    int minCost = INF;
    Node* best = NULL;

    // Simple array-based priority queue (inefficient but clear)
    Node* queue[10000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* min = NULL;
        int minIndex = -1;

        // Pick node with lowest (cost + level)
        for (int i = front; i < rear; i++) {
            if (!min || queue[i]->cost + queue[i]->level < min->cost + min->level) {
                min = queue[i];
                minIndex = i;
            }
        }

        // Remove from queue
        for (int i = minIndex; i < rear - 1; i++)
            queue[i] = queue[i + 1];
        rear--;

        if (min->cost == 0) {
            best = min;
            break;
        }

        // Generate child states
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat);
                queue[rear++] = child;
            }
        }
    }

    printf("Steps to solve the puzzle:\n");
    printPath(best);
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9,10,7,12},
        {13,14,11,15}
    };

    solve(initial, 1, 2);  // Blank tile coordinates (1,2)
    return 0;
}
