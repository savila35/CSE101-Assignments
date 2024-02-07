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
	if (fscanf(infile, "%d", &numVert) != 1) {
		fprintf(stderr, "FindComponent.c: error reading num vertices\n");
		exit(EXIT_FAILURE);
	}
	
	Graph G = newGraph(numVert);

	int v1, v2;
	while (true) {
		if (fscanf(infile, "%d %d", &v1, &v2) != 2) {
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
	fprintf(outfile, "\n");

	Graph T = transpose(G);
	List S = newList();
	for (int i = 1; i <= numVert; i++) {
		append(S, i);
	}

	DFS(G, S);
	DFS(T, S);

	int num_scc = 0;
	for (moveFront(S); index(S) >= 0; moveNext(S)) {
		if (getParent(T, get(S)) == NIL) {
			num_scc++;
		}
	}
	
	fprintf(outfile, "G contains %d strongly connected components:\n", num_scc);
	

	List* components = malloc((num_scc + 1) * sizeof(List));
	for (int j = 1; j <= num_scc; j++) {
		components[j] = newList();
	}

	int curr = 1;
	for (moveBack(S); index(S) >= 0; movePrev(S)) {
		prepend(components[curr], get(S));
		if (getParent(T, get(S)) == NIL) {
			fprintf(outfile, "Component %d: ", curr);
			printList(outfile, components[curr]);
			fprintf(outfile, "\n");
			freeList(&components[curr]);
			curr++;
		}
	}
	
	free(components);
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);

	fclose(infile);
	fclose(outfile);

	return(0);
}
