//------------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//------------------------------------------------------------------------------
#include "Graph.h"
#include <stdio.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

// structs ---------------------------------------------------------------------

// private Graph type
typedef struct GraphObj* Graph;

// private GraphObj type
typedef struct GraphObj{
	List* adjacent;
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
	G->adjacent = calloc(sizeof(List), n + 1);
	G->color = calloc(sizeof(int), n + 1);
	G->parent = calloc(sizeof(int), n + 1);
	G->distance = calloc(sizeof(int), n + 1);
	for (int i = 1; i <= n; i++) {
		G->adjacent[i] = newList();
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
		for (int i = 0; i <= (*pG)->order; i++) {
			freeList(&(*pG)->adjacent[i]);
		}
		free((*pG)->adjacent);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
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
	if (1 > u || u > G->order) {
		fprintf(stderr, "Graph error: calling getParent() with invalid vertex (%d)\n", u);
		exit(EXIT_FAILURE);
	}
	return(G->parent[u]);
}

int getDist(Graph G, int u) {
	if (1 > u || u > G->order) {
		fprintf(stderr, "Graph error: calling getDist() with invalid vertex (%d)\n", u);
		exit(EXIT_FAILURE);
	}
	return(G->distance[u]);
}

void getPath(List L, Graph G, int u) {
	if (getSource(G) == NIL) {
		fprintf(stderr, "Graph error: calling getPath() on undefined source\n");
		exit(EXIT_FAILURE);
	}
	if (1 > u || u > G->order) {
		fprintf(stderr, "Graph error: calling getPath() with invalid vertex (%d)\n", u);
		exit(EXIT_FAILURE);
	}
	if (u == G->source) {
		append(L, G->source);
		return;
	} else if (G->parent[u] == NIL) {
		append(L, NIL);
		return;
	} else {
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}


// Manipulation procedures -----------------------------------------------------
void makeNull(Graph G) {
	for (int i = 1; i <= G->size; i++) {
		clear(G->adjacent[i]);
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->size = 0;
	G->source = NIL;
}

void addEdge(Graph G, int u, int v) {
	if (1 > u || u > G->order || 1 > v || v > G->order) {
		fprintf(stderr, "Graph error: \
			calling addEdge() with invalid vertex (%d or/and %d)\n", u, v);
		exit(EXIT_FAILURE);
	}
	if (length(G->adjacent[u]) == 0) {
		append(G->adjacent[u], v);
	} else {
		moveFront(G->adjacent[u]);
		while (index(G->adjacent[u]) >= 0) {
			if (v < get(G->adjacent[u])) {
				insertBefore(G->adjacent[u], v);
				break;
			}
			if (index(G->adjacent[u]) == length(G->adjacent[u]) - 1) {
				append(G->adjacent[u], v);
				break;
			}
			moveNext(G->adjacent[u]);
		}	
	}
	if (length(G->adjacent[v]) == 0) {
		append(G->adjacent[v], u);
	} else {
		moveFront(G->adjacent[v]);
		while (index(G->adjacent[v]) >= 0) {
			if (u < get(G->adjacent[v])) {
				insertBefore(G->adjacent[v], u);
				break;
			}
			if (index(G->adjacent[v]) == length(G->adjacent[v]) - 1) {
				append(G->adjacent[v], u);
				break;
			}
			moveNext(G->adjacent[v]);
		}	
	}
	G->size++;
}

void addArc(Graph G, int u, int v) {
	if (1 > u || u > G->order || 1 > v || v > G->order) {
                fprintf(stderr, "Graph error: \
                        calling addArc() with invalid vertex (%d or/and %d)\n", u, v);
                exit(EXIT_FAILURE);
        }
        if (length(G->adjacent[u]) == 0) {
                append(G->adjacent[u], v);
        } else {
                moveFront(G->adjacent[u]);
                while (index(G->adjacent[u]) >= 0) {
                        if (v < get(G->adjacent[u])) {
                                insertBefore(G->adjacent[u], v);
                                break;
                        }
                        if (index(G->adjacent[u]) == length(G->adjacent[u]) - 1) {
                                append(G->adjacent[u], v);
				break;
                        }
                        moveNext(G->adjacent[u]);
                }
	}
	G->size++;
}

void BFS(Graph G, int s) {
	G->source = s;
	for (int i = 1; i <= G->order; i++) {
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	append(L, s);
	while (length(L) > 0) {
		int x = front(L);
		deleteFront(L);
		moveFront(G->adjacent[x]);
		while (index(G->adjacent[x]) >= 0) {
			int j = get(G->adjacent[x]);
			if (G->color[j] == WHITE) {
				G->color[j] = GRAY;
				G->distance[j] = G->distance[x] + 1;
				G->parent[j] = x;
				append(L,j);
			}
			G->color[j] = BLACK;
			moveNext(G->adjacent[x]);
		}
	}
	freeList(&L);
}


// Other operations ------------------------------------------------------------
void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out,"\n");
	}
}
