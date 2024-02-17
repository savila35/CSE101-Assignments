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
		M->row[i] = newList();
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
		makeZero(*pM);
		for (int i = 1; i <= (*pM)->size; i++) {
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
	if (A->size != B->size) {
		return(0);
	}
	Entry aE;
	Entry bE;
	for (int i = 1; i <= A->size; i++) {
		if (length(A->row[i]) != length(B->row[i])) {
			return(0);
		}
		moveFront(A->row[i]);
		moveFront(B->row[i]);
		while(index(A->row[i]) >= 0) {
			aE = (Entry) get(A->row[i]);
			bE = (Entry) get(B->row[i]);
			if (bE->col != aE->col || bE->val != aE->val) {
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
	Entry E;
	for (int i = 1; i <= M->size; i++) {
		for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
			E = (Entry) get(M->row[i]);
			freeEntry(&E);
		}
		clear(M->row[i]);
	}
	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
	if (1 > i || i > M->size || 1 > j || j > M->size) {
		fprintf(stderr, "Matrix.c: error calling changeEntry() with invalid coordinates: (%d,%d)\n", i, j);
		exit(EXIT_FAILURE);
	}
	Entry E;
	Entry nE;
	if (x == 0) {
		for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
			E = (Entry) get(M->row[i]);
			if (E->col > j) {
				return;
			}
			if (E->col == j) {
				freeEntry(&E);
				delete(M->row[i]);
				M->NNZ--;
				return;
			}
		}
		return;
	}

	if (length(M->row[i]) == 0) {
		nE = newEntry(j, x);
		append(M->row[i], nE);
		M->NNZ++;
		return;
 	}
 	for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
 		E = (Entry) get(M->row[i]);
 		if (E->col == j) {
 			E->val = x;
 			return;
 		}
 		if (E->col > j) {
 			nE = newEntry(j, x);
 			insertBefore(M->row[i], nE);
 			M->NNZ++;
 			return;
 		}
 	}
 	nE = newEntry(j, x);
 	append(M->row[i], nE);
 	M->NNZ++;
 	return;
 }


// Matrix Arithmetic operations ------------------------------------------------
Matrix copy(Matrix A) {
	Matrix C = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = (Entry) get(A->row[i]);
			changeEntry(C, i, E->col, E->val);
		}
	}
	return(C);
}

Matrix transpose(Matrix A) {
	Matrix T = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = (Entry) get(A->row[i]);
			changeEntry(T,E->col, i, E->val);
		}
	}			
	return(T);
}

Matrix scalarMult(double x, Matrix A) {
	Matrix xA = newMatrix(A->size);
	if (x == 0) {
		return(xA);
	}
	for (int i = 1; i <= A->size; i++) {
		for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
			Entry E = (Entry) get(A->row[i]);
			changeEntry(xA, i, E->col, (x * E->val));
		}
	}
	return(xA);
}

List vectorSum(List P, List C) {
	Entry pE;
	Entry cE;
	Entry E;
	List sum = newList();
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		pE = (Entry) get(P);
		cE = (Entry) get(C);
		if (pE->col < cE->col) {
			E = newEntry(pE->col, pE->val);
			append(sum, E);
			moveNext(P);
		} else if (pE->col > cE->col) {
			E = newEntry(cE->col, cE->val);
			append(sum, E);
			moveNext(C);
		} else {
			if (pE->val + cE->val == 0) {
				moveNext(P);
				moveNext(C);
				continue;
			}
			E = newEntry(pE->col, pE->val + cE->val);
			append(sum, E);
			moveNext(P);
			moveNext(C);
		}
	}
	while (index(P) >= 0) {
		pE = get(P);
		E = newEntry(pE->col, pE->val);
		append(sum, E);
		moveNext(P);
	}
	while (index(C) >= 0) {
		cE = get(C);
		E = newEntry(cE->col, cE->val);
		append(sum, E);
		moveNext(C);
	}
	return(sum);
}

Matrix sum(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling sum() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	if (equals(A, B)) {
		Matrix S = scalarMult(2, A);
		return(S);
	}
	Matrix S = newMatrix(A->size);
	S->NNZ = A->NNZ > B->NNZ ? A->NNZ : B->NNZ;
	for (int i = 1; i <= S->size; i++) {
		freeList(&S->row[i]);
		S->row[i] = vectorSum(A->row[i], B->row[i]);
	}
	return(S);
}

List vectorDiff(List P, List C) {
	Entry cE;
	Entry pE;
	Entry E;
	List diff = newList();
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		pE = get(P);
		cE = get(C);
		if (pE->col < cE->col) {
			E = newEntry(pE->col, pE->val);
			append(diff, E);
			moveNext(P);
		} else if (pE->col > cE->col) {
			E = newEntry(cE->col, 0 - cE->val);
			append(diff, E);
			moveNext(C);
		} else {
			if (pE->val - cE->val != 0) {
				E = newEntry(pE->col, pE->val - cE->val);
				append(diff, E);
			}
			moveNext(P);
			moveNext(C);
			
		}
	}
	while (index(P) >= 0) {
		pE = get(P);
		E = newEntry(pE->col, pE->val);
		append(diff, E);
		moveNext(P);
	}
	while (index(C) >= 0) {
		cE = get(C);
		E = newEntry(cE->col, 0 - cE->val);
		append(diff, E);
		moveNext(C);
	}
	return(diff);
}

Matrix diff(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling diff() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix D = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		freeList(&D->row[i]);
		List row = vectorDiff(A->row[i], B->row[i]);
		D->row[i] = row;
		D->NNZ += length(row);
	}
	//Matrix nB = scalarMult(-1,B);
	//Matrix D = sum(A, nB);
	//freeMatrix(&nB);
	return(D);
}

double vectorDot(List P, List C) {
	double sum = 0;
	Entry pE;
	Entry cE;
	if (length(P) == 0 || length(C) == 0) {	
		return(0);
	}
	moveFront(P);
	moveFront(C);
	while (index(P) >= 0 && index(C) >= 0) {
		pE = (Entry) get(P);
		cE = (Entry) get(C);
		if (pE->col < cE->col) {
			moveNext(P);
		} else if (pE->col > cE->col) {
			moveNext(C);
		} else {
			double val = pE->val * cE->val;
			sum += val;
			moveNext(P);
			moveNext(C);
		}
	}
	return(sum);
}

Matrix product(Matrix A, Matrix B) {
	if (A->size != B->size) {
		fprintf(stderr, "Matrix.c: error calling product() with differently sized matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix P = newMatrix(A->size);
	Matrix Bt = transpose(B);
	for (int i = 1; i <= P->size; i++) {
		for (int j = 1; j <= P->size; j++) {
			double val = vectorDot(A->row[i], Bt->row[j]);
			if (val != 0) {
				changeEntry(P,i, j, val);
			}
		}
	}
	freeMatrix(&Bt);
	return(P);
}


// Other operations ------------------------------------------------------------
void printMatrix(FILE* out, Matrix M) {
	for (int i = 1; i <= M->size; i++) {
		if (length(M->row[i]) == 0) {
			continue;
		}
		fprintf(out, "%d:", i);
		for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
			Entry E = (Entry) get(M->row[i]);
			fprintf(out, "(%d, %.1f) ", E->col,  E->val);
		}
		fprintf(out, "\n");
	}
}
