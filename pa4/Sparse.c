//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2023 Winter CSE101 pa4
// Sparse.c
// Does matrix arithmetic using two given matrices
//------------------------------------------------------------------------------

#include "Matrix.h"

#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Sparse.c: invalid command line arguments\n");
		exit(EXIT_FAILURE);
	}

	FILE* infile = fopen(argv[1], "r");
	if (infile == NULL) {
		fprintf(stderr, "Sparse.c: error opening file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE* outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		fprintf(stderr, "Sparse.c: error opening file: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int n, a, b;
	if (fscanf(infile, "%d %d %d", &n, &a, &b) != 3) {
		fprintf(stderr,"Sparse.c: error reading infile\n");
		exit(EXIT_FAILURE);
	}

	Matrix A = newMatrix(n);
	int r = 0, c = 0;
	double x = 0;
	for (int i = 0; i < a; i++) {
		if (fscanf(infile, "%d %d %lf", &r, &c, &x) != 3) {
			fprintf(stderr,"Sparse.c: error reading entry\n");
			exit(EXIT_FAILURE);
		}
		changeEntry(A, r, c, x);
	}

	Matrix B = newMatrix(n);
	for (int i = 0; i < b; i++) {
		if (fscanf(infile, "%d %d %lf", &r, &c, &x) != 3) {
			fprintf(stderr,"Sparse.c: error reading entry\n");
			exit(EXIT_FAILURE);
		}
		changeEntry(B, r, c, x);
	}
	if (fclose(infile) == EOF) {
		fprintf(stderr, "Sparse.c: error closing infile\n");
		exit(EXIT_FAILURE);
	}

	fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(outfile, A);
	fprintf(outfile,"\n");

	fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(outfile, B);
	fprintf(outfile,"\n");

	fprintf(outfile, "(1.5)*A =\n");
	Matrix xA = scalarMult(1.5, A);
	printMatrix(outfile, xA);
	fprintf(outfile,"\n");
	freeMatrix(&xA);

	fprintf(outfile, "A+B =\n");
	Matrix A_B = sum(A, B);
	printMatrix(outfile, A_B);
	fprintf(outfile,"\n");
	freeMatrix(&A_B);

	fprintf(outfile, "A+A =\n");
	Matrix AA = sum(A, A);
	printMatrix(outfile, AA);
	fprintf(outfile,"\n");
	freeMatrix(&AA);

	fprintf(outfile, "B-A =\n");
	Matrix B_A = diff(B, A);
	printMatrix(outfile, B_A);
	fprintf(outfile,"\n");
	freeMatrix(&B_A);

	fprintf(outfile, "A-A =\n");
	Matrix A_A = diff(A, A);
	printMatrix(outfile, A_A);
	fprintf(outfile,"\n");
	freeMatrix(&A_A);

	fprintf(outfile, "Transpose(A) =\n");
	Matrix At = transpose(A);
	printMatrix(outfile, At);
	fprintf(outfile,"\n");
	freeMatrix(&At);

	fprintf(outfile, "A*B = \n");
	Matrix AB = product(A, B);
	printMatrix(outfile, AB);
	fprintf(outfile,"\n");
	freeMatrix(&AB);

	fprintf(outfile, "B*B = \n");
	Matrix BB = product(B, B);
	printMatrix(outfile, BB);
	fprintf(outfile,"\n");
	freeMatrix(&BB);

	freeMatrix(&A);
	freeMatrix(&B);

	if (fclose(outfile) == EOF) {
		fprintf(stderr, "Sparse.c: error closing outfile\n");
		exit(EXIT_FAILURE);
	}

	return(0);
}
