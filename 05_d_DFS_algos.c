#include <stdio.h>
#define V 5

int time = 0;

void DFSUtil(int u, int visited[], int disc[], int finish[], int graph[V][V]) {
    visited[u] = 1;
    disc[u] = ++time;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFSUtil(v, visited, disc, finish, graph);
            } 
            else if (finish[v] == 0) {
                // v is discovered but not finished → back edge
                printf("Back Edge: %d -> %d\n", u, v);
            } 
            else if (disc[u] < disc[v]) {
                // v is finished and discovered after u → forward edge
                printf("Forward Edge: %d -> %d\n", u, v);
            } 
            else {
                // v is finished and discovered before u → cross edge
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    finish[u] = ++time;
}

void DFS(int graph[V][V]) {
    int visited[V] = {0}, disc[V] = {0}, finish[V] = {0};

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            DFSUtil(i, visited, disc, finish, graph);
    }
}

int main() {
    int graph[V][V] = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 1, 0}
    };

    DFS(graph);
    return 0;
}