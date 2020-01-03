/* -----------------------------

Balaram Behera
bbehera@ucsc.edu
CSE 101 - PA5
12/6/2019

File: Graph.h

------------------------------ */


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h"

/*** constants ***/
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define UNDEF -1
#define NIL 0

/*** Exported Type ***/
typedef struct GraphObj* Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void addArc(Graph G, double A[], int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
// void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, double A[], List S); /* Pre: length(S)==getOrder(G) */
/* Other Functions */
// Graph transpose(Graph G);
Graph copyGraph(Graph G, double A[]);
void printGraph(FILE* out , Graph G);


#endif
