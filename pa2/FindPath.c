#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "FindPath.c: invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	FILE* in = fopen(argv[1], "r");
	if (in == NULL) {
		fprintf(stderr, "FindPath.c: error opening file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	FILE* out = fopen(argv[2], "w");
	if (out == NULL) {
		fprintf(stderr, "FindPath.c: error opening file: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	int numVert;
	if (fscanf(in, "%d", &numVert) != 1) {
		fprintf(stderr, "FindPath.c: error reading num vertices\n");
		exit(EXIT_FAILURE);
	}
	
	Graph G = newGraph(numVert);

	int v1, v2;
	while (true) {
		if (fscanf(in, "%d %d", &v1, &v2) != 2) {
			fprintf(stderr, "FindPath.c: error reading edges\n");
			exit(EXIT_FAILURE);
		}
	
		if (v1 == 0 && v2 == 0) {
			break;
		}
		addEdge(G, v1, v2);
	}
	printGraph(out,G);
	
	int s, d;
	List path = newList();
	while (true) {
		if (fscanf(in, "%d %d", &s, &d) != 2) {
			fprintf(stderr, "FindPath.c: error reading edges\n");
			exit(EXIT_FAILURE);
		}
	
		if (s == 0 && d == 0) {
			break;
		}
		BFS(G, s);
		if (getDist(G, s) == INF) {
			fprintf(out, "\nThe distance from %d to %d is infinity\n", s, d);
		} else {
			fprintf(out, "\nThe distance from %d to %d is %d\n", s, d, getDist(G, s));
		}
		getPath(path, G, d);
		if (front(path) == NIL) {
			fprintf(out, "No %d-%d path exists\n", s, d);
		} else {
			fprintf(out, "A shortest %d-%d path is: ", s, d);
			printList(out, path);
			fprintf(out, "\n");
		}
		clear(path);
	}
	fclose(in);
	fclose(out);
	freeList(&path);
	freeGraph(&G);
		
	return 0;
}
