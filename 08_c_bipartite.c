#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int n;

// Function to check if the graph is bipartite using BFS
int isBipartite(int start) {
    int queue[MAX], front = 0, rear = 0;

    color[start] = 1;  // Assign first color
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                // If vertex v is not colored, assign opposite color
                if (color[v] == 0) {
                    color[v] = -color[u];
                    queue[rear++] = v;
                }
                // If adjacent vertex has the same color → not bipartite
                else if (color[v] == color[u]) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int main() {
    int e, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix and color array
    for (int i = 0; i < n; i++) {
        color[i] = 0;
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;  // Undirected graph
    }

    int isBip = 1;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {  // Unvisited vertex
            if (!isBipartite(i)) {
                isBip = 0;
                break;
            }
        }
    }

    if (isBip)
        printf("\nThe graph is Bipartite.\n");
    else
        printf("\nThe graph is NOT Bipartite.\n");

    return 0;
}
