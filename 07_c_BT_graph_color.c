#include <stdio.h>
#define V 4   // Number of vertices

// Function to print the solution
void printSolution(int color[]) {
    printf("One possible coloring:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);
}

// Check if the color assignment is safe for vertex v
int isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return 0;  // adjacent vertex has the same color
    return 1;
}

// Recursive utility function to solve graph coloring
int graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V)
        return 1;  // all vertices colored

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;  // assign color
            if (graphColoringUtil(graph, m, color, v + 1))
                return 1;
            color[v] = 0;  // backtrack
        }
    }

    return 0;  // no color could be assigned
}

// Main function to solve the m-coloring problem
void graphColoring(int graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(graph, m, color, 0))
        printSolution(color);
    else
        printf("No solution exists using %d colors\n", m);
}

int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3;  // Number of colors
    graphColoring(graph, m);

    return 0;
}
