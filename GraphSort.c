#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

Graph makeGraph(double A[], int n) {
    Graph G = newGraph(n);
    int j;
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            j = 1;
        } else {
            j = i + 1;
        }

        if (A[i - 1] < A[j - 1]) {
            // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[i - 1], A[j - 1], i, j);
            addArc(G, A, i, j);
        } else if (A[i - 1] > A[j - 1]) {
        // } else {
            // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[j - 1], A[i - 1], j, i);
            addArc(G, A, j, i);
        } else {
            if (i < j) {
                addArc(G, A, i, j);
            } else if (i > j) {
                addArc(G, A, j, i);
            }
        }
    }

    return G;
}

void mergeTrees(Graph G, double A[], int n, int x, int y) {
    // printf("merging roots %d and %d\n", x, y);

    int u = x;
    int v = y;

    int* done = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        done[i] = 0;
    }

    while (u != NIL && v != NIL) {
        if (A[u - 1] < A[v - 1]) {
            // printf("good\n");
            int r = u;
            // printGraph(stdout, G, A);
            List L = getAdj(G, u);
            if (length(L) > 0) {
                // TODO (first front that isnt done)
                // u = front(L);
                moveFront(L);
                while (index(L) >= 0) {
                    if (!done[get(L)]) {
                        u = get(L);
                        break;
                    }
                    moveNext(L);
                }
                if (index(L) < 0) {
                    u = NIL;
                }
            } else {
                u = NIL;
            }
            done[r] = 1;
            // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[r - 1], A[v - 1], r, v);
            addArc(G, A, r, v);
            freeList(&L);
        } else if (A[u - 1] > A[v - 1]) {
        // } else {
            int r = v;
            List L = getAdj(G, v);
            if (length(L) > 0) {
                // v = front(L);
                moveFront(L);
                while (index(L) >= 0) {
                    if (!done[get(L)]) {
                        v = get(L);
                        break;
                    }
                    moveNext(L);
                }
                if (index(L) < 0) {
                    v = NIL;
                }
            } else {
                v = NIL;
            }
            done[r] = 1;
            // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[r - 1], A[u - 1], r, u);
            addArc(G, A, r, u);
            freeList(&L);
        } else {
            // printf("u,v: %d, %d\n", u, v);
            if (u < v) {
                int r = u;
                List L = getAdj(G, u);
                if (length(L) > 0) {
                    moveFront(L);
                    while (index(L) >= 0) {
                        if (!done[get(L)]) {
                            u = get(L);
                            break;
                        }
                        moveNext(L);
                    }
                    if (index(L) < 0) {
                        u = NIL;
                    }
                } else {
                    u = NIL;
                }
                done[r] = 1;
                // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[r - 1], A[v - 1], r, v);
                addArc(G, A, r, v);
                freeList(&L);
            } else if (u > v) {
                int r = v;
                List L = getAdj(G, v);
                if (length(L) > 0) {
                    // v = front(L);
                    moveFront(L);
                    while (index(L) >= 0) {
                        if (!done[get(L)]) {
                            v = get(L);
                            break;
                        }
                        moveNext(L);
                    }
                    if (index(L) < 0) {
                        v = NIL;
                    }
                } else {
                    v = NIL;
                }
                done[r] = 1;
                // printf("adding edge from %f to %f (i.e. %d to %d)\n", A[r - 1], A[u - 1], r, u);
                addArc(G, A, r, u);
                freeList(&L);
            }
        }
        // else {
        //     int r = u;
        //     // printGraph(stdout, G, A);
        //     List L = getAdj(G, u);
        //     if (length(L) > 0) {
        //         addArc(G, A, r, v);
        //         addArc(G, A, v, r);
        //         u = front(L);
        //     } else {
        //         r = v;
        //         freeList(&L);
        //         L = getAdj(G, v);
        //         if (length(L) > 0) {
        //             v = front(L);
        //         } else {
        //             v = NIL;
        //         }
        //         addArc(G, A, u, r);
        //         addArc(G, A, r, u);
        //     }
        //     freeList(&L);
        // }
    }
}

List merge(Graph G, double A[], int n) {
    // printf("p: %d\n", getParent(G, 2));
    // printf("shit inside merge function\n");
    List roots = newList();
    for (int x = 1; x <= n; x++) {
        if (getParent(G, x) == NIL) {
            append(roots, x);
            List L = getAdj(G, x);
            if (length(L) > 0) {
                int l = front(L);
                int r = back(L);
                // printf("l: %d, %r: %d\n", l, r);
                if (l != r) {
                    // printf("shit1\n");
                    mergeTrees(G, A, n, l, r);
                }
                // printf("shit2\n");
            }
            freeList(&L);
        }
    }
    // printf("roots: "); printList(stdout, roots, A); printf("\n");

    List newRoots = newList();
    moveFront(roots);
    while (index(roots) >= 0 && index(roots) < length(roots) - 1) {
        int r = get(roots);
        moveNext(roots);
        int s = get(roots);
        moveNext(roots);
        if (A[r - 1] < A[s - 1]) {
            append(newRoots, r);
        } else if (A[r - 1] > A[s - 1]) {
        // } else {
            append(newRoots, s);
        } else {
            if (r < s) {
                append(newRoots, r);
            } else if (r > s) {
                append(newRoots, s);
            }
        }
        mergeTrees(G, A, n, r, s);
    }
    if (index(roots) == length(roots) - 1) {
        append(newRoots, back(roots));
    }
    // printGraph(stdout, G, A);
    // printf("new roots: "); printList(stdout, newRoots, A); printf("\n");

    // printf("yay\n");
    return copyList(newRoots);
}

double* graphSort(double A[], double* B, int n) {
    // generate corresponding graph
    Graph G = makeGraph(A, n);
    // printf("corresponding graph\n"); printGraph(stdout, G, A);

    // find min and max of A
    int min = 1;
    int max = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[min - 1]) {
            min = i + 1;
        }
        if (A[i] > A[max - 1]) {
            max = i + 1;
        }
    }
    // printf("min: %d, max: %d\n", min, max);

    // generate model stack
    List L = newList();
    for (int i = min; i <= n; i++) {
        if (i != max) {
            append(L, i);
        }
    }
    for (int i = 1; i < min; i++) {
        if (i != max) {
            append(L, i);
        }
    }
    append(L, max);
    // printf("L: "); printList(stdout, L, A); printf("\n");

    // merge/DFS process
    List S = copyList(L);
    int trees = n + 1;
    while (trees > 1) {
        // printf("trees right now: %d\n", trees);
        // printf("S: "); printList(stdout, L, A); printf("\n");
        DFS(G, A, S);
        // printf("we done with dfs now\n");
        freeList(&S);
        // printf("after dfs: \n"); printGraph(stdout, G, A);
        // printf("starting merge\n");
        S = merge(G, A, n);
        // printf("merge is done\n");
        trees = length(S);
        // printf("yay\n");
        // printf("trees: %d\n", trees);
        // printf("after merge: \n"); printGraph(stdout, G, A);
        // freeList(&S);
    }
    // printf("yoo we done merging\n");
    S = copyList(L);
    DFS(G, A, S);
    // printf("last graph\n"); printGraph(stdout, G, A);
    // printf("yooo "); printList(stdout, S, A); printf("\n");

    int j = 0;
    while (length(S) > 0) {
        B[j] = A[front(S) - 1];
        deleteFront(S);
        j++;
    }

    freeGraph(&G);

    // return sorted array
    return B;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main() {
    int runs = 300, iter = 50;
    // int runs = 100, iter = 100;
    double gs[runs], qs[runs];
    for (int i = 1; i <= runs; i++) {
        // double A[] = {3, 1, 7, 5, 8, 5, 1, 4, 5, 1, 4, 11, 2, 3, 3, 10, 11, 3, 1, 7, 5, 8, 5, 1, 4, 5, 1, 4, 11, 2, 3, 3, 10, 11};
        // int n = sizeof(A) / sizeof(double);
        int n = i*iter;
        double A[n];
        for (int i = 0; i < n; i++) {
            A[i] = (double)(((int)((double)rand()/RAND_MAX*10000.))*1.);
        }

        printf("Unsorted A:");
        for (int i = 0; i < n; i++) {
            printf(" (%d, %f)", i + 1, A[i]);
        }
        printf("\n\n\n");

        double* B = malloc(n * sizeof(double));

        // sorting
        clock_t start, end;

        start = clock();
        graphSort(A, B, n);
        end = clock();
        double gs_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

        start = clock();
        qsort(A, n, sizeof(double), cmpfunc);
        end = clock();
        double qs_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;


        printf("Sorted A:");
        for (int i = 0; i < n; i++) {
            printf(" %f", B[i]);
        }
        printf("\n\n");

        for (int i = 1; i < n; i++) {
            if (B[i - 1] > B[i]) {
                printf("INCORRECT SORT!\n");
                return 0;
            }
        }
        printf("CORRECT SORT!\n");
        printf("Sorted array with %d elements\n", n);
        printf("Execution Time for GraphSort: %f s\n", gs_elapsed);
        printf("Execution Time for QuickSort: %f s\n", qs_elapsed);

        gs[i - 1] = gs_elapsed;
        qs[i - 1] = qs_elapsed;
    }

    printf("\n\nLENGTH \t GRAPH SORT EXEC TIME \t QUICKSORT EXEC TIME:\n");
    for (int i = 0; i < runs; i++) {
        printf("%d \t %f \t %f\n", (i + 1)*iter, gs[i], qs[i]);
    }

    return 0;
}
