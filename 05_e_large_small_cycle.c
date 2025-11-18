//Identify Largest and Smallest Cycles (Directed Graph)
#include <stdio.h>
#define V 4
int minCycle=1e9, maxCycle=-1;

void DFS(int u, int start, int visited[], int depth, int graph[V][V]) {
    visited[u]=1;
    for(int v=0; v<V; v++){
        if(graph[u][v]){
            if(v==start) {
                if(depth+1<minCycle) minCycle=depth+1;
                if(depth+1>maxCycle) maxCycle=depth+1;
            }
            else if(!visited[v]) DFS(v,start,visited,depth+1,graph);
        }
    }
    visited[u]=0;
}

int main() {
    int graph[V][V]={{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}};
    int visited[V]={0};
    for(int i=0;i<V;i++) DFS(i,i,visited,0,graph);
    if(maxCycle==-1) printf("No cycle\n");
    else printf("Smallest cycle=%d, Largest cycle=%d\n", minCycle, maxCycle);
}
