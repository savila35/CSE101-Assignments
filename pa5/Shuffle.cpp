#include "List.h"
#include <iostream>


void shuffle(List& D) {
	int n = D.length();
	int half = n/2;
	List L;
	List R;
	int x;
	for (int i = 0; i < half; i++) {
		x = D.moveNext();
		L.insertBefore(x);
	}
	for (int j = half; j < n; j++) {
		x = D.moveNext();
		R.insertBefore(x);
	}
	L.moveFront();
	R.moveFront();
	D.clear();
	for (int k = 1; k <= n; k++) {
		if (k % 2) {
			int r = R.moveNext();
			D.insertBefore(r);
		} else {
			int l = L.moveNext();
			D.insertBefore(l);
		}
	}
	D.moveFront();
}


int main(int argc, char** argv) {
	if (argc != 2) {
		throw std::invalid_argument("Shuffle: main(): invalid argument or missing argument");
	}
	char* arg = argv[1];
	int n = 0;
	for (int i = 0; arg[i] != '\0'; i++) {
		if ('0' <= arg[i] && arg[i] <= '9') {
			n = n * 10 + (arg[i] - '0');
		} else {
			throw std::invalid_argument("Shuffle: main(): argument not a positive integer");
		}
	}

	std::cout << "deck size       shuffle count\n";
	std::cout << "------------------------------\n";
	List D;
	for (int i = 0; i < n; i++) {
		int size = i + 1;
		D.insertBefore(i);
		List C = D;
		int count = 0;
		while (1) {
			shuffle(C);
			count++;
			if (C == D) {
				break;
			}		
		}
		printf("%-16d %-12d\n", size, count);
	} 
	return 0;
}
