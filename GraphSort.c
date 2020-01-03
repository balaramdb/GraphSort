#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

Graph makeGraph(double A[]) {

}

void mergeTrees(Graph G, double A[], int x, int y) {

}

int merge(Graph G, double A[]) {

}

double* graphSort(double A[]) {
    // length of array
    int n = sizeof(A) / sizeof(double);

    // generate corresponding graph
    Graph G = makeGraph(A);

    // find min and max of A
    int min = 0;
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[min]) {
            min = i;
        }
        if (A[i] > A[max]) {
            max = i;
        }
    }

    // generate model stack
    List L = newList();
    for (int i = min + 1; i <= n; i++) {
        if (i != max + 1) {
            append(L, i);
        }
    }
    for (int i = 1; i <= min; i++) {
        if (i != max + 1) {
            append(L, i);
        }
    }
    append(L, max);

    // merge/DFS process
    int trees = n + 1;
    while (trees > 1) {
        List S = copyList(L);
        DFS(G, A, S);
        trees = merge(G, A);
        freeList(&S);
    }
    List S = copyList(L);
    DFS(G, A, S);

    // convert list to array
    double B[n];
    int j = 0;
    while (length(S) > 0) {
        B[j] = front(S);
        deleteFront(S);
    }

    // return sorted array
    return B;
}

int main() {
    double A[] = {0.5, 5, 2, 10, 7, 8.5, 1.1};

    printf("Unsorted A:");
    for (int i = 0; i < sizeof(A)/sizeof(double); i++) {
        printf(" %f", A[i]);
    }
    printf("\n");

    double* B = graphSort(A);

    printf("Sorted A:");
    for (int i = 0; i < sizeof(B)/sizeof(double); i++) {
        printf(" %f", B[i]);
    }
    printf("\n");
}
