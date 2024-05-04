#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EDGES 50
#define MAX_NODES 20

struct Edge {
    char source, destination;
    int weight;
};

struct Graph {
    int V, E;
    struct Edge edges[MAX_EDGES];
};

struct Subset {
    int parent;
    int rank;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V - 1]; 
    int e = 0;
    int totalWeight = 0; 
    int i = 0;

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), myComp);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.source - 'A');
        int y = find(subsets, next_edge.destination - 'A');

        if (x != y) {
            result[e++] = next_edge;
            totalWeight += next_edge.weight;
            Union(subsets, x, y);
        }
    }

    printf("Following are the edges in the constructed MST:\n");
    for (int j = 0; j < e; ++j)
        printf("%c -- %c == %d\n", result[j].source, result[j].destination, result[j].weight);

    printf("Total weight of the MST: %d\n", totalWeight);

    free(subsets);
}
int main() {
    //Hard Coded
    // int V = 4;
    // int E = 5;

    // struct Graph* graph = createGraph(V, E);

    // graph->edges[0] = (struct Edge){'A', 'B', 10};
    // graph->edges[1] = (struct Edge){'B', 'C', 15};
    // graph->edges[2] = (struct Edge){'C', 'D', 5};
    // graph->edges[3] = (struct Edge){'A', 'D', 20};
    // graph->edges[4] = (struct Edge){'B', 'D', 25};

    // KruskalMST(graph);
    // free(graph);

    //Dynamic (User Input)

    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter the source, destination (as letters A, B, C, ...), and weight for each edge:\n");
    for (int i = 0; i < E; ++i) {
        char src, dest;
        int weight;
        scanf(" %c %c %d", &src, &dest, &weight);
        graph->edges[i].source = src;
        graph->edges[i].destination = dest;
        graph->edges[i].weight = weight;
    }

    KruskalMST(graph);

    return 0;
}
