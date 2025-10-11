#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6   // number of vertices (you can change)

// Find vertex with minimum distance not yet processed
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the solution
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];       // Output array: shortest distance from src
    bool sptSet[V];    // True if vertex is included in shortest path tree

    // Initialize distances and processed set
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        // Update distances of neighbors
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && sptSet[v] == false &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the result
    printSolution(dist);
}

int main() {
    // Example graph represented as adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int source = 0;
    printf("Dijkstra starting from vertex %d:\n", source);
    dijkstra(graph, source);

    return 0;
}

