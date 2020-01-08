/* -----------------------------

Balaram Behera
bbehera@ucsc.edu
CSE 101 - PA5
12/6/2019

File: Graph.c

------------------------------ */


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int time;


// struct -----------------------------------------------------------

typedef struct GraphObj {
    int* instances;
    List* adj;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;
} GraphObj;


// constructors - destructors ---------------------------------------

Graph newGraph(int n) {
    if (n < 1) {
        printf("Graph Error: calling newGraph() on incorrect order.\n");
        exit(1);
    }

    Graph G = malloc(sizeof(GraphObj));

    G->instances = malloc((n + 1) * sizeof(int));
    G->adj = malloc((n + 1) * sizeof(List));
    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->discover = malloc((n + 1) * sizeof(int));
    G->finish = malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;

    for (int x = 0; x <= n; x++) {
        G->instances[x] = 1;
        G->adj[x] = newList();
        G->parent[x] = NIL;
        G->discover[x] = UNDEF;
        G->finish[x] = UNDEF;
    }

    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        free((*pG)->instances);

        for (int x = 0; x <= getOrder(*pG); x++) {
            freeList(&((*pG)->adj[x]));
        }
        free((*pG)->adj);

        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);

        free(*pG);
        *pG = NULL;
    }
}

// private functions -----------------------------------------------

void visit(Graph G, Graph F, double A[], List S, int x) {
    // printf("visiting vertex %d (%f)\n", x, A[x - 1]);
    G->discover[x] = (++time);
    G->color[x] = GRAY;

    moveFront(G->adj[x]);
    while (index(G->adj[x]) >= 0) {
        if (G->color[get(G->adj[x])] == WHITE) {
            // printf("vertex %d (%f) has parent %d (%f)\n", get(G->adj[x]), A[get(G->adj[x]) - 1], x, A[x - 1]);
            G->parent[get(G->adj[x])] = x;
            // printf("adding tree edge\n");
            addArc(F, A, x, get(G->adj[x]));
            // printf("done adding tree edge\n");
            // int y = get(G->adj[x]);
            // printf("visiting next vertex: %d (%f)\n", get(G->adj[x]), A[get(G->adj[x]) - 1]);
            visit(G, F, A, S, get(G->adj[x]));
            // printf("done visiting next vertex\n");
        }
        moveNext(G->adj[x]);
    }
    // printf("done visiting this vetex\n");
    G->color[x] = BLACK;
    G->finish[x] = (++time);
    prepend(S, x);
    // printf("visit ends\n");
}


// access functions -------------------------------------------------

int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: calling getOrder() on NULL Graph reference.\n");
        exit(1);
    }

    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: calling getSize() on NULL Graph reference.\n");
        exit(1);
    }

    return G->size;
}

int getInstance(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getInstance() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getInstance() on incorrect vertex label.\n");
        exit(1);
    }

    return G->instances[u];
}

List getAdj(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getAdj() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getAdj() on incorrect vertex label.\n");
        exit(1);
    }

    return copyList(G->adj[u]);
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() on incorrect vertex label.\n");
        exit(1);
    }

    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDist() on incorrect vertex label.\n");
        exit(1);
    }

    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDist() on incorrect vertex label.\n");
        exit(1);
    }

    return G->finish[u];
}


// manipulation procedures ------------------------------------------

void incrementInstance(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling incrementInstance() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling incrementInstance() on incorrect vertex label(s).\n");
        exit(1);
    }

    G->instances[u]++;
}

void addArc(Graph G, double A[], int u, int v) {
    if (G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addArc() on incorrect vertex label(s).\n");
        exit(1);
    }

    moveFront(G->adj[u]);
    while (index(G->adj[u]) >= 0) {
        if (A[v - 1] < A[get(G->adj[u]) - 1]) {
            insertBefore(G->adj[u], v);
            break;
        }
        if (A[v - 1] == A[get(G->adj[u]) - 1] && v < get(G->adj[u])) {
            insertBefore(G->adj[u], v);
            break;
        }
        moveNext(G->adj[u]);
    }
    if (index(G->adj[u]) < 0) {
        append(G->adj[u], v);
    }

    G->size++;
}

// void addEdge(Graph G, int u, int v) {
//     if (G == NULL) {
//         printf("Graph Error: calling addEdge() on NULL Graph reference.\n");
//         exit(1);
//     }
//     if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
//         printf("Graph Error: calling addEdge() on incorrect vertex label(s).\n");
//         exit(1);
//     }
//
//     addArc(G, u, v);
//     addArc(G, v, u);
//     G->size--;
// }
//
// void visit(Graph G, Graph F, double A[], List S, int x) {
//     printf("visiting vertex %d (%f)\n", x, A[x - 1]);
//     G->discover[x] = (++time);
//     G->color[x] = GRAY;
//
//     moveFront(G->adj[x]);
//     while (index(G->adj[x]) >= 0) {
//         if (G->color[get(G->adj[x])] == WHITE) {
//             printf("vertex %d (%f) has parent %d (%f)\n", get(G->adj[x]), A[get(G->adj[x]) - 1], x, A[x - 1]);
//             G->parent[get(G->adj[x])] = x;
//             printf("adding tree edge\n");
//             addArc(F, A, x, get(G->adj[x]));
//             printf("done adding tree edge\n");
//             // int y = get(G->adj[x]);
//             printf("visiting next vertex: %d (%f)\n", get(G->adj[x]), A[get(G->adj[x]) - 1]);
//             visit(G, F, A, S, get(G->adj[x]));
//             printf("done visiting next vertex\n");
//         }
//         moveNext(G->adj[x]);
//     }
//     printf("done visiting this vetex\n");
//     G->color[x] = BLACK;
//     G->finish[x] = (++time);
//     prepend(S, x);
//     printf("visit ends\n");
// }

void iterVisit(Graph G, Graph F, double A[], List L, int x) {
    List stack = newList();
    prepend(stack, x);

    while (length(stack) > 0) {
        int y = front(stack);
        deleteFront(stack);

        if (G->color[y] == WHITE) {
            G->discover[y] = (++time);
            G->color[y] = GRAY;
        }

        moveBack(G->adj[y]);
        while (index(G->adj[y]) >= 0) {
            if (G->color[get(G->adj[y])] == WHITE) {
                prepend(stack, get(G->adj[y]));
            }
            movePrev(G->adj[y]);
        }
    }
}

void iterDFS(Graph G, double A[], List S) {
    if (G == NULL) {
        printf("Graph Error: calling iterDFS() on NULL Graph reference.\n");
        exit(1);
    }

    Graph F = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }

    time = 0;

    List L = newList();

    moveFront(S);
    while (index(S) >= 0) {
        if (G->color[get(S)] == WHITE) {
            iterVisit(G, F, A, L, get(S));
        }
        moveNext(S);
    }

    // copy dfs tree to G and stack to S

    for (int x = 1; x <= getOrder(G); x++) {
        clear(G->adj[x]);
    }
    G->size = 0;

    for (int i = 1; i <= getOrder(F); i++) {
        moveFront(F->adj[i]);
        while (index(F->adj[i]) >= 0) {
            addArc(G, A, i, get(F->adj[i]));
            moveNext(F->adj[i]);
        }
    }

    clear(S);
    moveFront(L);
    while (index(L) >= 0) {
        append(S, get(L));
        moveNext(L);
    }

    freeList(&L);
}

void DFS(Graph G, double A[], List S) {
    if (G == NULL) {
        printf("Graph Error: calling DFS() on NULL Graph reference.\n");
        exit(1);
    }
    // if (length(S) != getOrder(G)) {
    //     printf("Graph Error: calling DFS() on incorrect vertex ordering.\n");
    //     exit(1);
    // }

    Graph F = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }

    time = 0;

    List L = newList();

    moveFront(S);
    while (index(S) >= 0) {
        if (G->color[get(S)] == WHITE) {
            visit(G, F, A, L, get(S));
        }
        moveNext(S);
    }

    // freeGraph(&G);
    // G = copyGraph(F, A);

    for (int x = 1; x <= getOrder(G); x++) {
        clear(G->adj[x]);
    }
    G->size = 0;

    for (int i = 1; i <= getOrder(F); i++) {
        moveFront(F->adj[i]);
        while (index(F->adj[i]) >= 0) {
            addArc(G, A, i, get(F->adj[i]));
            moveNext(F->adj[i]);
        }
    }

    clear(S);
    moveFront(L);
    while (index(L) >= 0) {
        append(S, get(L));
        moveNext(L);
    }

    freeList(&L);
}


// other operations -------------------------------------------------

// Graph transpose(Graph G) {
//     if (G == NULL) {
//         printf("Graph Error: calling transpose() on NULL Graph reference.\n");
//         exit(1);
//     }
//
//     Graph T = newGraph(getOrder(G));
//     for (int i = 1; i <= getOrder(G); i++) {
//         moveFront(G->adj[i]);
//         while (index(G->adj[i]) >= 0) {
//             addArc(T, get(G->adj[i]), i);
//             moveNext(G->adj[i]);
//         }
//     }
//
//     return T;
// }

Graph copyGraph(Graph G, double A[]) {
    if (G == NULL) {
        return NULL;
    }

    Graph C = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) >= 0) {
            addArc(C, A, i, get(G->adj[i]));
            moveNext(G->adj[i]);
        }
    }

    return C;
}

void printGraph(FILE* out, Graph G, double A[]) {
    if (out == NULL) {
        printf("Graph Error: calling addArc() on NULL File reference.\n");
        exit(1);
    }
    if (G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference.\n");
        exit(1);
    }

    for (int x = 1; x <= getOrder(G); x++) {
        fprintf(out, "%d (%f): ", x, A[x - 1]);
        moveFront(G->adj[x]);
        while (index(G->adj[x]) >= 0) {
            fprintf(out, "%d (%f)", get(G->adj[x]), A[get(G->adj[x]) - 1]);
            moveNext(G->adj[x]);
            if (index(G->adj[x]) >= 0) {
                fprintf(out, ", ");
            }
        }
        fprintf(out, "\n");
    }
}
