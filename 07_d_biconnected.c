#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ---------- Graph Definition ----------
struct Graph {
    int V;
    int adj[MAX][MAX];
};

void createGraph(struct Graph* g, int vertices) {
    g->V = vertices;
    memset(g->adj, 0, sizeof(g->adj));
}

void addEdge(struct Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// ---------- Utility for DFS ----------
void DFS(struct Graph* g, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < g->V; i++)
        if (g->adj[v][i] && !visited[i])
            DFS(g, i, visited);
}

// ---------- Kosaraju’s Algorithm for SCC ----------
void fillOrder(struct Graph* g, int v, int visited[], int* stack, int* top) {
    visited[v] = 1;
    for (int i = 0; i < g->V; i++)
        if (g->adj[v][i] && !visited[i])
            fillOrder(g, i, visited, stack, top);
    stack[++(*top)] = v;
}

void transpose(struct Graph* g, struct Graph* gt) {
    createGraph(gt, g->V);
    for (int i = 0; i < g->V; i++)
        for (int j = 0; j < g->V; j++)
            if (g->adj[i][j])
                gt->adj[j][i] = 1;
}

void printSCCs(struct Graph* g) {
    int stack[MAX], top = -1;
    int visited[MAX] = {0};

    for (int i = 0; i < g->V; i++)
        if (!visited[i])
            fillOrder(g, i, visited, stack, &top);

    struct Graph gt;
    transpose(g, &gt);

    memset(visited, 0, sizeof(visited));

    printf("\nStrongly Connected Components:\n");
    while (top != -1) {
        int v = stack[top--];
        if (!visited[v]) {
            DFS(&gt, v, visited);
            printf("\n");
        }
    }
}

// ---------- Tarjan’s Algorithm for Articulation Points & Bridges ----------
int timeDFS = 0;

void APBUtil(int u, int parent[], int visited[], int disc[], int low[], struct Graph* g) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeDFS;
    int children = 0;

    for (int v = 0; v < g->V; v++) {
        if (!g->adj[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            APBUtil(v, parent, visited, disc, low, g);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // Articulation Point
            if ((parent[u] == -1 && children > 1) ||
                (parent[u] != -1 && low[v] >= disc[u]))
                printf("Articulation Point: %d\n", u);

            // Bridge
            if (low[v] > disc[u])
                printf("Bridge: %d - %d\n", u, v);
        }
        else if (v != parent[u])
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
    }
}

void findArticulationPointsAndBridges(struct Graph* g) {
    int visited[MAX] = {0}, disc[MAX], low[MAX], parent[MAX];

    for (int i = 0; i < g->V; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }

    for (int i = 0; i < g->V; i++)
        if (!visited[i])
            APBUtil(i, parent, visited, disc, low, g);
}

// ---------- Main ----------
int main() {
    struct Graph g;
    int vertices, edges, u, v, choice;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    createGraph(&g, vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    printf("\n1. Strongly Connected Components (directed)");
    printf("\n2. Articulation Points & Bridges (undirected)");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        printSCCs(&g);
    else
        findArticulationPointsAndBridges(&g);

    return 0;
}
