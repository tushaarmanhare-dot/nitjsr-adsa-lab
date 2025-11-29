#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;

// Check if vertex v can be added to path[pos]
int isSafe(int v, int pos) {
    // Check if current vertex is adjacent to the previous vertex
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    // Check if vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

// Recursive utility function to find Hamiltonian cycle
int hamCycleUtil(int pos) {
    // Base case: if all vertices are included
    if (pos == n) {
        // Check if last vertex connects to the first
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    // Try different vertices as next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1) == 1)
                return 1;

            // Backtrack
            path[pos] = -1;
        }
    }

    return 0;
}

// Function to solve Hamiltonian Cycle problem
int hamCycle() {
    // Initialize path[]
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0; // Start at vertex 0

    if (hamCycleUtil(1) == 0) {
        printf("\nNo Hamiltonian Cycle exists.\n");
        return 0;
    }

    printf("\nHamiltonian Cycle found:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]); // Return to start
    return 1;
}

int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1; // undirected graph
    }

    hamCycle();

    return 0;
}
