//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa2
// GraphTest.c
// Tests for Graph ADT implementation
//-----------------------------------------------------------------------------

#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 5, 2);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	printGraph(stdout, G);
	assert(getOrder(G) == 6);
	assert(getSize(G) == 8);
	
	BFS(G, 1);
	assert(getDist(G, 5) == 2);
	assert(getParent(G, 5) == 2);

	makeNull(G);
	assert(getOrder(G) == 6);
	assert(getSize(G) == 0);

	List L = newList();
	List L2 = newList();
	addEdge(G, 1, 4);
	addEdge(G, 1, 3);
	addEdge(G, 6, 2);
	addEdge(G, 2, 1);
	addEdge(G, 4, 2);
	addEdge(G, 3, 6);
	BFS(G, 3);
	getPath(L, G, 1);
	append(L2, 3);
	append(L2, 1);
	assert(equals(L, L2));
	BFS(G, 2);
	getPath(L, G, 2);
	append(L2, 2);
	printList(stdout, L);
	printf("\n");
	printList(stdout, L2);
	printf("\n");
	assert(equals(L, L2));

	makeNull(G);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	BFS(G,1);
	clear(L);
	assert(getDist(G,3) == 2);
	BFS(G,3);
	assert(getDist(G,1) == INF);
	printGraph(stdout,G);
	
	freeGraph(&G);
	freeList(&L);
	freeList(&L2);
	return(0);
}
