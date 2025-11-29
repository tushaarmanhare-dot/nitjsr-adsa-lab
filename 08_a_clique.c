#include <stdio.h>

#define MAX 25

int g[MAX][MAX], n, m;
int sel[MAX];

int isClique() {
    for (int i = 0; i < n; i++)
        if (sel[i])
            for (int j = i + 1; j < n; j++)
                if (sel[j] && g[i][j] == 0)
                    return 0;
    return 1;
}

int cntSel() {
    int c = 0;
    for (int i = 0; i < n; i++) if (sel[i]) c++;
    return c;
}

int backtrack(int v) {
    if (cntSel() == m) return isClique();
    if (v == n) return 0;

    sel[v] = 1;
    if (backtrack(v + 1)) return 1;

    sel[v] = 0;
    return backtrack(v + 1);
}

int main() {
    int e, u, v;
    printf("n e: ");
    scanf("%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }

    printf("Enter m: ");
    scanf("%d", &m);

    if (backtrack(0))
        printf("Clique of size %d exists\n", m);
    else
        printf("No clique of size %d\n", m);

    return 0;
}
