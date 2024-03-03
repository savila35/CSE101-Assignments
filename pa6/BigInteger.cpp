#include "BigInteger.h"

// Global Constants ------------------------------------------------------------
const int power = 2;
const long base = 100;

// Private Constructor ---------------------------------------------------------

// Class Constructors & Destructors --------------------------------------------

BigInteger::BigInteger() {
    signum = 0;
}

BigInteger::BigInteger(long x) {
    if (x > 0) {
        signum = 1;
    } else if (x < 0) {
        signum = -1;
		x *= -1;
    } else {
        signum = 0;
    }
    while (x > 0) {
        digits.insertAfter(x % base);
        x /= base;
    }
}

BigInteger::BigInteger(std::string s) {
    if (s == "0") {
        signum = 0;
        return;
    }
    if (s.front() == '-') {
        signum = -1;
        s.erase(0,1);
    } else {
        signum = 1;
        if (s.front() == '+') {
            s.erase(0,1);
        }
    }
    while (s.length() % power != 0) {
        s = "0" + s;
    }
    int front = 0;
    std::string sub;
    digits.moveFront();
    while (front <= (int) s.length() - power) {
        sub = s.substr(front, power);
        digits.insertBefore(std::stol(sub));
        front += power;
    }
}

BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits;	
}


// Access functions ------------------------------------------------------------

int BigInteger::sign() const{
    return(signum);
}

int BigInteger::compare(const BigInteger& N) const{
    return(0);
}


// Manipulation procedures -----------------------------------------------------

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    if (signum == 0) {
        return;
    }
    signum *= -1;
}


//------ Helper functions ------------------------------------------------------

void sumList(List& S, List A, List B, int signA, int signB) {
    A.moveBack();
    B.moveBack();
    long x, a, b;
    while (A.position() > 0 && B.position() > 0) {
        a = A.movePrev() * signA;
        b = B.movePrev() * signB;
        x = a + b;
        S.insertAfter(x);
    }
    while (A.position() > 0) {
        a = A.movePrev() * signA; 
        S.insertAfter(a);
    }
    while (B.position() > 0) {
       b = B.movePrev() * signB; 
        S.insertAfter(b);
    }
}

int normalizeList(List& L) {
    if (L.length() == 0) {
        return(0);
    }
    int carry = 0;
    L.moveBack(); // Start from the least significant digit
    while (L.position() > 0) {
        int value = L.peekPrev() + carry; // Add carry from the previous digit
		int x = (L.position() == 1) ? value % base : std::abs(value % base);
        L.setBefore(x); // Set current digit to the remainder of division by base
        carry = value / base; // Calculate new carry
        L.movePrev(); // Move to the next most significant digit
    }
    if (carry > 0) { // If there's a carry left after the most significant digit
        L.moveFront();
        L.insertAfter(carry); // Insert new most significant digit
    }

    // Optional: Remove leading zeros, if any, after normalization
    while (L.length() > 1 && L.front() == 0) {
        L.moveFront();
        L.eraseAfter(); // Remove leading zero
    }
	int sign = (L.front() > 0) ? 1 : -1;
	int x  = std::abs(L.front());
	L.moveFront();
	L.setAfter(x);
    return(sign);
}


// BigInteger Arithmetic operations --------------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger S;
    List vectorSum;
    List tD = digits;
    List nD = N.digits;
    sumList(vectorSum, digits, N.digits, signum, N.signum);
    int sign = normalizeList(vectorSum);
    S.digits = vectorSum;
    S.signum = sign;
    return(S);
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger D;
    return(D);
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger P;
    return(P);
}


// Other functions -------------------------------------------------------------

std::string BigInteger::to_string() {
    if (signum == 0) {
        return("0");
    }
    std::string s = "";
    if (signum < 0) {
        s += "-";
    }
    digits.moveFront();
	std::string t;
	bool first = true;
    while (digits.position() < digits.length()) {
        t = std::to_string(digits.moveNext());
		while (t.length() < std::to_string(base).length() - 1 && !first) {
			t = "0" + t;
		}
		s += t;
		first = false;
    }
    return(s);
}


// Overriden Operators ---------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, BigInteger N) {
    return(stream << N.to_string());
}

bool operator==( const BigInteger& A, const BigInteger& B) {
    return(true);
}

bool operator<( const BigInteger& A, const BigInteger& B) {
    return(true);
}

bool operator<=( const BigInteger& A, const BigInteger& B) {
    return(true);
}

bool operator>( const BigInteger& A, const BigInteger& B) {
    return(true);
}

bool operator>=( const BigInteger& A, const BigInteger& B) {
    return(true);
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return(A.add(B));
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return(A);
}
