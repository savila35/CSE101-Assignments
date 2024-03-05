//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE 101 pa6
// BigIntegerTest.cpp
// Test cases for BigInteger implemenation
//------------------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include "BigInteger.h"

int main() {
	long x = 5447;
	BigInteger I(x);
	std::cout << I << std::endl;
	std::string s = "1350";
	BigInteger S(s);
	std::cout << S << std::endl;
	BigInteger A = S.add(I);
	std::cout << A << std::endl;
	BigInteger B = S.sub(I);
	std::cout << B << std::endl;
	BigInteger C = I.mult(S);
	std::cout << C << std::endl;
	assert(S < I);
	assert(S <= S);
	assert(I > S);
	assert(I >= I);
	assert(B == B);
	std::cout << 2*A + B << std::endl;
	
	A = BigInteger("111122223333");
    B = BigInteger("-111122223333");
	C = A + B;
	int y = C.sign();
	printf("%d\n",y);
	std::cout << C << std::endl;

	A = BigInteger("-0000000000041085449");
	std::cout << A << std::endl;
	A = BigInteger("+111122223333");
	BigInteger D = BigInteger("212244446666");
	B = BigInteger("101122223333");
	B.negate();
    C = B - A;
	std::cout << C << std::endl;
	D.negate();
	std::cout << D << std::endl;
	
	A = BigInteger(-120);
	B = BigInteger(-90);
	std::cout << A + B << std::endl;
	std::cout << A - B << std::endl;

	A = BigInteger("-221211110000");
	B = BigInteger("-112122223333");
    D = BigInteger("-333333333333");
    C = A + B;
	std::cout << C << std::endl;

	A = BigInteger("-111122223333");
	B = BigInteger("110122223333");
	std::cout << A - B << std::endl;

	A = BigInteger("-111122223333");
    B = BigInteger("-112122223333");
    D = BigInteger("1000000000");
	std::cout << A - B << std::endl;


	return(EXIT_SUCCESS);
}
