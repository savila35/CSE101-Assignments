//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa2
// Graph.h
// Header file for Graph ADT
//------------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"
#include <stdlib.h>
#include <stdbool.h>

#define INF -1
#define NIL 0

// Exported Types --------------------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-destructors ----------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);


// Access functions ------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void getPath(List L, Graph G, int u);


// Manipulation procedures -----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);


// Other operations ------------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
