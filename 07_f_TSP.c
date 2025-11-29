#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100

// Function to generate random distances (symmetric matrix)
void generateGraph(int n, int graph[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 100 + 1; // random distance 1–100
        }
    }
}

// Nearest Neighbor Heuristic for TSP
int tspNearestNeighbor(int n, int graph[MAX][MAX]) {
    int visited[MAX] = {0};
    int totalCost = 0;
    int current = 0; // start from vertex 0
    visited[current] = 1;

    for (int count = 1; count < n; count++) {
        int next = -1, minDist = 1e9;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current][j] < minDist) {
                minDist = graph[current][j];
                next = j;
            }
        }
        visited[next] = 1;
        totalCost += minDist;
        current = next;
    }

    totalCost += graph[current][0]; // return to start
    return totalCost;
}

// Function to measure execution time
double measureTime(int n) {
    int graph[MAX][MAX];
    generateGraph(n, graph);

    clock_t start = clock();
    tspNearestNeighbor(n, graph);
    clock_t end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));

    int sizes[] = {10, 20, 40, 60, 100};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nTSP Execution Time (Nearest Neighbor Heuristic)\n");
    printf("------------------------------------------------\n");
    printf("Nodes\tExecution Time (seconds)\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < numSizes; i++) {
        double timeTaken = measureTime(sizes[i]);
        printf("%d\t\t%.6f\n", sizes[i], timeTaken);
    }

    return 0;
}
