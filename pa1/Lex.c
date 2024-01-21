//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa1
// Lex.c
// File line sorter
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define BUFFSIZE 500

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Lex.c: invalid arguments\nUsage: ./Lex.c <input.txt> <output.txt>\n");
		exit(EXIT_FAILURE);
	}
	
	FILE *fin = fopen(argv[1], "r");
	if (fin == NULL) {
		fprintf(stderr, "Lex.c: error opening file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}	

	FILE *fout = fopen(argv[2], "w");
	if (fout == NULL) {
		fprintf(stderr, "Lex.c: error opening file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}	
	
	char c;
	int numLines = 0;
	for (c = getc(fin); c != EOF; c = getc(fin)) {
		if (c == '\n') {
			numLines++;
		}
	}
	
	fseek(fin, 0, SEEK_SET);
	char **lines = malloc(numLines * sizeof(char*));
	for (int i = 0; i < numLines; i++) {
		lines[i] = (char*) malloc(500 * sizeof(lines[i]));
		if (fgets(lines[i], BUFFSIZE, fin) == NULL) {
		}
		lines[i][strlen(lines[i]) - 1] = '\0';
	}
	List L = newList();
	int currIndex;
	for (int j = 0; j < numLines; j++) {
		
		if (length(L) == 0) {
			append(L, j);
			continue;
		}
		moveFront(L);
		while (index(L) >= 0) {
			currIndex = get(L);
			if (strcmp(lines[currIndex], lines[j]) > 0) {
				insertBefore(L, j);
				break;
			}
			if (index(L) == length(L) - 1) { 
				append(L, j);
				break;
			}
			moveNext(L);
		}
	}
	
	
	moveFront(L);
	while (index(L) >= 0) {
		currIndex = get(L);
		fprintf(fout, "%s\n", lines[currIndex]);
		moveNext(L);
	}
	
	for (int h = 0; h < numLines; h++) {
		free(lines[h]);
	}
	free(lines);
	freeList(&L);
	fclose(fin);
	fclose(fout);

	return 0;
}
