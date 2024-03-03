#include <iostream>
#include "BigInteger.h"

int main() {
	long x = 102;
	BigInteger I(x);
	std::cout << I << std::endl;
	std::string s = "-3145";
	BigInteger S(s);
	std::cout << S << std::endl;
	BigInteger A = S.add(I);
	std::cout << A << std::endl;
	return(EXIT_SUCCESS);
}
