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
			if ((*pM)->row[i] == NULL) {
				continue;
			}
			for (moveFront((*pM)->row[i]); index((*pM)->row[i]) >= 0; moveNext((*pM)->row[i])) {
				Entry E = (Entry) get((*pM)->row[i]);
				freeEntry(&E);
			}
			freeList(&(*pM)->row[i]);
		}
		free((*pM)->row);
		free(*pM);
		*pM = NULL;
	}
}

Entry newEntry(int c, double v) {
	Entry E = malloc(sizeof(EntryObj));
	E->col = c;
	E->val = v;
	return(E);
}


// Access functions
int size(Matrix M) {
	return(M->size);
}

int NNZ(Matrix M) {
	return(M->NNZ);
}

int equals(Matrix A, Matrix B) {
	if (A->size != B->size || A->NNZ != B->NNZ) {
		return(0);
	}
	for (int i = 1; i <= A->size; i++) {
		if (A->row[i] == NULL && B->row[i] == NULL) {
			continue;
		}
		if (A->row[i] == NULL || B->row[i] == NULL) {
			return(0);
		}
		moveFront(A->row[i]);
		moveFront(B->row[i]);
		while (1) {
			if (index(A->row[i]) < 0 && index(B->row[i]) < 0) {
				break;
			}
			if (index(A->row[i]) < 0 || index(B->row[i]) < 0) {			
				return(0);
			}
			Entry aE = get(A->row[i]);
			Entry bE = get(B->row[i]);
			if (aE->val != bE->val) {
				return(0);
			}
			moveNext(A->row[i]);
			moveNext(B->row[i]);
		}
	}
	return(1);
}


// Manipulation procedures
void makeZero(Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] == NULL) {
			continue;
		}
		for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
			Entry E = get(M->row[i]);
			freeEntry(&E);
		}
		freeList(&(M->row[i]));
		M->row[i] = NULL;
	}
	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
	if (1 > i || i > M->size || 1 > j || j > M->size) {
		fprintf(stderr, "Matrix.c: error calling changeEntry() with invalid coordinates: \
			 (%d,%d)\n", i, j);
		exit(EXIT_FAILURE);
	}
	if (M->row[i] == NULL) {
		M->row[i] = newList();
	}
	for (moveFront(M->row[i]); index(M->row[i]); moveNext(M->row[i])) {
		if (length(M->row[i]) == 0) {
			if (x != 0) {
				Entry nE = newEntry(j, x);
				append(M->row[i], nE);
				M->NNZ++;
				return;
			}
			break;
		}
		Entry E = get(M->row[i]);
		if (E->col == j) {
			if (x == 0) {
				freeEntry(get(M->row[i]));
				delete(M->row[i]);
				M->NNZ--;
				return;
			}
			E->val = x;
			return;
		}
		if (E->col > j) {
			if (x == 0) {
				return;
			}
			Entry N = newEntry(j, x);
			insertBefore(M->row[i], N);
			M->NNZ++;
			return;
		}
	}
	if (x != 0) {
		Entry E = newEntry(j, x);
		append(M->row[i], E);
		M->NNZ++;
	}
	if (length(M->row[i]) == 0) {
		freeList(&M->row[i]);
	}
}


// Matrix Arithmetic operations ------------------------------------------------
Matrix copy(Matrix A) {
	Matrix C = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		if (A->row[i] == NULL) {
			continue;
		}
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = get(A->row[i]);
			changeEntry(C, i, E->col, E->val);
		}
	}
	return(C);
}

Matrix transpose(Matrix A) {
	Matrix T = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		if (A->row[i] == NULL) {
			continue;
		}
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = get(A->row[i]);
			changeEntry(T,E->col, i, E->val);
		}
	}			
	return(T);
}

Matrix scalarMult(double x, Matrix A) {
	Matrix xA = newMatrix(A->size);
	if (x == 0) {
		xA->NNZ = 0;
		return(xA);
	}
	for (int i = 1; i <= A->size; i++) {
		if (A->row[i] == NULL) {
			continue;
		}
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = get(A->row[i]);
			changeEntry(xA, i, E->col, x * E->val);
		}
	}
	return(xA);
}

double vectorDot(List P, List C) {
	int sum = 0;
	Entry pE;
	Entry cE;
	if (P == NULL || C == NULL) {	
		return(0);
	}
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		pE = get(P);
		cE = get(C);
		if (pE->col < cE->col) {
			moveNext(P);
		} else if (pE->col > cE->col) {
			moveNext(C);
		} else {
			sum += pE->val * cE->val;
			moveNext(P);
			moveNext(C);
		}
	}
	return(sum);
}

List vectorSum(List P, List C) {
	Entry pE;
	Entry cE;
	if (P == NULL && C == NULL) {	
		return(NULL);
	}
	if (P == NULL) {
		return(C);
	}
	if (C == NULL) {
		return(P);
	}
	List sum = newList();
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		pE = get(P);
		cE = get(C);
		if (pE->col < cE->col) {
			Entry E = newEntry(pE->col, pE->val);
			append(sum, E);
			moveNext(P);
		} else if (pE->col > cE->col) {
			Entry E = newEntry(cE->col, cE->val);
			append(sum, E);
			moveNext(C);
		} else {
			Entry sE = newEntry(pE->col, pE->val + cE->val);
			append(sum, sE);
			moveNext(P);
			moveNext(C);
		}
	}
	 while (index(P) >= 0) {
		Entry E = newEntry(pE->col, pE->val);
		append(sum, E);
                moveNext(P);
        }
        while (index(C) >= 0) {
		Entry E = newEntry(cE->col, cE->val);
		append(sum, E);
                moveNext(C);
        }
	return(sum);
}

List vectorDiff(List P, List C) {
	Entry cE;
	if (P == NULL && C == NULL) {	
		return(NULL);
	}
	if (C == NULL) {
		return(P);
	}
	List diff = newList();
	if (P == NULL) {
		for (moveFront(C); index(C) >= 0; moveNext(C)) {
			cE = get(C);
			Entry dE = newEntry(cE->col, 0 - cE->val);
			append(diff, dE);
		}
		return(diff);
	}
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		Entry pE = get(P);
		Entry cE = get(C);
		if (pE->col < cE->col) {
			Entry E = newEntry(pE->col, pE->val);
			append(diff, E);
			moveNext(P);
		} else if (pE->col > cE->col) {
			Entry E = newEntry(cE->col, 0 - cE->val);
			append(diff, E);
			moveNext(C);
		} else {
			if (pE->val - cE->val != 0) {
				Entry dE = newEntry(pE->col, pE->val - cE->val);
				append(diff, dE);
			}
			moveNext(P);
			moveNext(C);
			
		}
	}
	while (index(P) >= 0) {
		Entry pE = get(P);
		Entry E = newEntry(pE->col, pE->val);
		append(diff, E);
		moveNext(P);
	}
	while (index(C) >= 0) {
		cE = get(C);
		Entry dE = newEntry(cE->col, 0 - cE->val);
		append(diff, dE);
		moveNext(C);
	}
	if (length(diff) == 0) {
		freeList(&diff);
		return(NULL);
	}
	return(diff);
}

Matrix sum(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling sum() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix S = newMatrix(A->size);
	S->NNZ = A->NNZ > B->NNZ ? A->NNZ : B->NNZ;
	for (int i = 1; i <= S->size; i++) {
		S->row[i] = vectorSum(A->row[i], B->row[i]);
	}
	return(S);
}

Matrix diff(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling diff() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix D = newMatrix(A->size);
	for (int i = 1; i <= D->size; i++) {
		D->row[i] = vectorDiff(A->row[i], B->row[i]);
	}
	return(D);
}

Matrix product(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling product() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix P = newMatrix(A->size);
	Matrix Bt = transpose(B);
	for (int i = 1; i <= P->size; i++) {
		if (A->row[i] == NULL) {
			continue;
		}
		P->row[i] = newList();
		for (int j = 1; j <= P->size; j++) {
			if (Bt->row[i] == NULL) {
				continue;
			}
			int val = vectorDot(A->row[i], Bt->row[j]);
			if (val == 0) {
				continue;
			}
			changeEntry(P,i, j, val);
		}
		if (length(P->row[i]) == 0) {
			freeList(&P->row[i]);
		}
	}
	freeMatrix(&Bt);
	return(P);
}


// Other operations ------------------------------------------------------------
void printMatrix(FILE* out, Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (M->row[i] == NULL) {
			continue;
		}
		fprintf(out, "%d:", i);
		for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
			Entry E = get(M->row[i]);
			fprintf(out, "(%d, %.1f) ", E->col,  E->val);
		}
		fprintf(out, "\n");
	}
}
