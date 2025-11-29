#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent the graph
struct Graph {
    int V;                  // Number of vertices
    int adj[MAX][MAX];      // Adjacency matrix
};

// Function to create a graph
void createGraph(struct Graph* g, int vertices) {
    g->V = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Function to add an edge (u -> v)
void addEdge(struct Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// Recursive function for DFS
void topologicalSortUtil(struct Graph* g, int v, int visited[], int stack[], int* top) {
    visited[v] = 1;

    // Visit all adjacent vertices
    for (int i = 0; i < g->V; i++) {
        if (g->adj[v][i] && !visited[i]) {
            topologicalSortUtil(g, i, visited, stack, top);
        }
    }

    // Push current vertex to stack
    stack[++(*top)] = v;
}

// Function to perform Topological Sort
void topologicalSort(struct Graph* g) {
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;

    // Call recursive helper function for all vertices
    for (int i = 0; i < g->V; i++) {
        if (!visited[i])
            topologicalSortUtil(g, i, visited, stack, &top);
    }

    // Print contents of the stack (reverse order)
    printf("Topological Sort Order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

// Main function
int main() {
    struct Graph g;
    int vertices, edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    createGraph(&g, vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) meaning u -> v:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    topologicalSort(&g);

    return 0;
}
