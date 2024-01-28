#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	printGraph(stdout, G);
	
	BFS(G, 1);
	printf("Distance: %d\n", getDist(G, 5));
	return(0);
}
