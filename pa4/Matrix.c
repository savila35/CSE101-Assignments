#include "Matrix.h"

// structs ---------------------------------------------------------------------

// private Matrix type
typedef MatrixObj* Matrix;

// private MatrixObj type
typedef struct MatrixObj {
	List* row;
	int size;
	int NNZ;
};

// private Entry type
typedef EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj {
	int col;
	double val;
}

// Constructor-Deconstructor ---------------------------------------------------
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->row = calloc(sizeof(List), n+1)
	M->size = n;
	M->NNZ = 0;
	for (int i = 1; i <= n; i++) {
		row[i] = NULL;
	}
}

void freeMatrix(Matrix *pM) {
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= (*pM)->size; i++) {
			for (moveFront((*pM)->row[i]); index((*pM)->row[i]) >= 0; moveNext((*pM)->row[i])) {
				freeEntry(&(get((*pM)->row[i])));
			}
			freeList(&(*pM)->row);
		}
	}
}

Entry makeEntry(int c, double v) {
	Entry E = malloc(sizeof(EntryObj));
	E->col = c;
	E->val = v;
}

void freeEntry(Entry *pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

// Access functions


// Manipulation procedures
void makeZero(Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] != NULL) {
			for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
				freeEntry(&(get(M->row[i])));
			}
			freeList(M->row[i]);
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
		if (get(M->row[i])->col == j) {
			if (x == 0) {
				freeEntry(get(M->row[i]));
				delete(M-row[i]);
				return;
			}
			get(M->row[i])->val = x;
			return;
		}
		if (get(M->row[i])->col > j) {
			if (x == 0) {
				return;
			}
			Entry E = makeEntry(j, x);
			insertBefore(M->row[i], E);
			return;
		}
	}
}


// Matrix Arithmetic operations ------------------------------------------------



// Other operations ------------------------------------------------------------
void printMatrix(FILE* out, Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] != NULL) {
			fprintf(out, "%d:", i);
			for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
				fprintf(out, "(%d, %.1f) ", M->row[i]->col,  M->row[i]->val);
			}
			fprintf(out, "/n");
		}
}
