#include <stdio.h>
#include <stdlib.h>

typedef struct {int u,v,w;} Edge;

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int find(int parent[], int i) {
    return parent[i]==i ? i : (parent[i]=find(parent,parent[i]));
}

void unionSet(int parent[], int x, int y) {
    parent[find(parent,x)] = find(parent,y);
}

void kruskal(Edge edges[], int E, int V) {
    qsort(edges,E,sizeof(edges[0]),cmp);
    int parent[V]; for(int i=0;i<V;i++) parent[i]=i;
    printf("Edge\tWeight\n");
    for(int i=0,count=0;i<E && count<V-1;i++){
        int u=edges[i].u, v=edges[i].v;
        if(find(parent,u)!=find(parent,v)){
            printf("%d-%d\t%d\n", u,v,edges[i].w);
            unionSet(parent,u,v); count++;
        }
    }
}

int main() {
    int V=4, E=5;
    Edge edges[]={{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}};
    kruskal(edges,E,V);
}
