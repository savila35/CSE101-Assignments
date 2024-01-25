//------------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//------------------------------------------------------------------------------
#include "Graph.h"
#include <stdio.h>

// structs ---------------------------------------------------------------------

// private Graph type
typedef struct GraphObj* Graph;

// private GraphObj type
typedef struct GraphObj{
	List* neighbors;
	int* color;
	int* parent;
	int* distance;
	int order;
	int size;
	int source;
} GraphObj;

// Constructors-Destructors ----------------------------------------------------
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = malloc(sizeof(List) * n + 1);
	G->color = malloc(sizeof(int) * n + 1);
	G->parent = malloc(sizeof(int) * n + 1);
	G->distance = malloc(sizeof(int) * n + 1);
	for (int i = 1; i <= n; i++) {
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return(G);
}

void freeGraph(Graph *pG) {
	if (pG != NULL && *pG != NULL) {
		for (int i = 0; i <= n; i++) {
			freeList(&neighbors[i]);
		}
		free(color);
		free(parent);
		free(distance);
		free(*pG);
		*pG = NULL;
	}
	return;
}

// Access functions ------------------------------------------------------------
int getOrder(Graph G) {
	return(G->order);
}

int getSize(Graph G) {
	return(G->size);
}

int getSource(Graph G) {
	return(G->source);
}

int getParent(Graph G, int u) {
	return(G->parent[u]);
}

int getDist(Graph G, int u) {
	return(G->distance);
}

void getPath(List L, Graph G, int u) {
	 
