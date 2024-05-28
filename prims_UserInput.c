#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int **graph, int V) {
    printf("Edge \tWeight\n");
    int totalWeight = 0;

    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }

    printf("Total Weight of MST is: %d\n", totalWeight);
}

void primMST(int **graph, int V) {
    int *parent = malloc(V * sizeof(int));
    int *key = malloc(V * sizeof(int));
    bool *mstSet = malloc(V * sizeof(bool)); 

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;   
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);

        mstSet[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph, V);

    free(parent);
    free(key);
    free(mstSet);
}

int main() {
    int V;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    int **graph = malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = malloc(V * sizeof(int));
    }

    printf("Enter the adjacency matrix for the graph (%dx%d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, V);
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    return 0;
}