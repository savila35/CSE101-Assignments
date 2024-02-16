#include "Matrix.h"

#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Sparse.c: invalid command line arguments\n");
		exit(EXIT_FAILURE);
