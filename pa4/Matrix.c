#include "Matrix.h"

// structs ---------------------------------------------------------------------

// private Matrix type
typedef struct MatrixObj* Matrix;

// private MatrixObj type
typedef struct MatrixObj {
	List* row;
	int size;
	int NNZ;
} MatrixObj;

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj {
	int col;
	double val;
} EntryObj;

// Constructor-Deconstructor ---------------------------------------------------
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->row = calloc(sizeof(List), n+1);
	M->size = n;
	M->NNZ = 0;
	for (int i = 1; i <= n; i++) {
		M->row[i] = NULL;
	}
	return(M);
}

void freeEntry(Entry *pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

void freeMatrix(Matrix *pM) {
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= (*pM)->size; i++) {
			for (moveFront((*pM)->row[i]); index((*pM)->row[i]) >= 0; moveNext((*pM)->row[i])) {
				Entry E = get((*pM)->row[i]);
				freeEntry(&E);
			}
			freeList(&(*pM)->row[i]);
		}
	}
}

Entry makeEntry(int c, double v) {
	Entry E = malloc(sizeof(EntryObj));
	E->col = c;
	E->val = v;
	return(E);
}


// Access functions


// Manipulation procedures
void makeZero(Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] != NULL) {
			for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
				Entry E = get(M->row[i]);
				freeEntry(&E);
			}
			freeList(&(M->row[i]));
		}
	}
	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
	if (1 > i || i > M->size || 1 > j || j > M->size) {
		fprintf(stderr, "Matrix.c: error calling changeEntry() with invalid coordinates: \
			 (%d,%d)\n", i, j);
		exit(EXIT_FAILURE);
	}
	for (moveFront(M->row[i]); index(M->row[i]); moveNext(M->row[i])) {
		Entry E = get(M->row[i]);
		if (E->col == j) {
			if (x == 0) {
				freeEntry(get(M->row[i]));
				delete(M->row[i]);
				return;
			}
			E->val = x;
			return;
		}
		if (E->col > j) {
			if (x == 0) {
				return;
			}
			Entry N = makeEntry(j, x);
			insertBefore(M->row[i], N);
			return;
		}
	}
}


// Matrix Arithmetic operations ------------------------------------------------
Matrix copy(Matrix A) {
	Matrix C = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		if (A->row[i] != NULL) {
			for (moveFront(A->row[i]); index(A->row[i]); moveNext(A->row[i])) {
				append(C->row[i], get(A->row[i]));
			}
		}
	}
	return(C);
}

Matrix transpose(Matrix A) {
	Matrix T = newMatrix(A->size);
	return(T);
}


// Other operations ------------------------------------------------------------
void printMatrix(FILE* out, Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] != NULL) {
			fprintf(out, "%d:", i);
			for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
				Entry E = get(M->row[i]);
				fprintf(out, "(%d, %.1f) ", E->col,  E->val);
			}
			fprintf(out, "/n");
		}
	}
}
