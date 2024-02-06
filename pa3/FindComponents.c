#include "Graph.h"
#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "FindComponent.c: invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	FILE* infile = fopen(argv[1], "r");
	if (infile == NULL) {
		fprintf(stderr, "FindComponent.c: error opening file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	FILE* outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		fprintf(stderr, "FindComponent.c: error opening file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	int numVert;
	if (fscanf(in, "%d", &numVert) != 1) {
		fprintf(stderr, "FindComponent.c: error reading num vertices\n");
		exit(EXIT_FAILURE);
	}
	
	Graph G = newGraph(numVert);

	int v1, v2;
	while (true) {
		if (fscanf(in, "%d %d", &v1, &v2) != 2) {
			fprintf(stderr, "FindComponent.c: error reading edge\n");
			exit(EXIT_FAILURE);
		}
	
		if (v1 == 0 && v2 == 0) {
			break;
		}
		addArc(G, v1, v2);
	}
	fprintf(outfile,"Adjacency list representation of G:\n");
	printGraph(outfile,G);
	fprintf(outfile, "\n\n");

	Graph T = transpose(G);
	List S = newList();
	for (int i = 1; i <= numVert; i++) {
		append(S, i);
	}

	DFS(G, S);
	DFS(T, S);

	return(0);
}
