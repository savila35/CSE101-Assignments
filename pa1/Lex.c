#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define BUFFSIZE 500

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Lex.c: too few arguments\n");
		exit(EXIT_FAILURE);
	}
	
	FILE *fin = fopen(argv[1], "r");
	if (fin == NULL) {
		fprintf(stderr, "Lex.c: error opening file");
		exit(EXIT_FAILURE);
	}	
	char c;
	int numLines = 0;
	for (c = getc(fin); c != EOF; c = getc(fin)) {
		if (c == '\n') {
			numLines++;
		}
	}
	printf("%d\n", numLines);
	
	fseek(fin, 0, SEEK_SET);
	char **lines = malloc(numLines * sizeof(char*));
	for (int i = 0; i < numLines; i++) {
		lines[i] = (char*) malloc(500 * sizeof(lines[i]));
		if (fgets(lines[i], BUFFSIZE, fin) == NULL) {
			fprintf(stderr, "Lex.c: error reading file");
		}
		lines[i][strlen(lines[i]) - 1] = '\0';
	}
	List L = newList();
	int currIndex;
	for (int j = 0; j < numLines; j++) {
		printf("what is happening\n");
		
		if (length(L) == 0) {
			append(L, j);
			continue;
		}
		moveFront(L);
		printf("curr: %s\n", index(L) >=0 ? "good" : "fuck you pussy");
		while (index(L) >= 0) {
			currIndex = get(L);
			printf("%d\n", currIndex);
			if (strcmp(lines[currIndex], lines[j]) > 0) {
				insertBefore(L, j);
				break;
			}
			if (index(L) == length(L) - 1) { 
				append(L, j);
				break;
			}
			printf("str1: %s str2: %s\n",lines[currIndex], lines[j]);
			moveNext(L);
		}
	}
	
	printList(stdout, L);
	printf("\n");
	return 0;
}
