#include "BigInteger.h"

// Global Constants ------------------------------------------------------------
const int power = 1;
const long base = 10;

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
    if (signum == 1 && N.signum == -1) {
        return(1);
    } else if (signum == -1 && N.signum == 1) {
        return(-1);
    }
    int resultMult = (signum == 1) ? 1 : -1;
    if (digits.length() > N.digits.length()) {
        return(1 * resultMult);
    } else if (digits.length() < N.digits.length()) {
        return(-1 * resultMult);
    }
    List tL = digits;
    List nL = N.digits;
    tL.moveFront();
    nL.moveFront();
    while (tL.position() < tL.length()) {
        int t = tL.moveNext();
        int n = nL.moveNext();
        if (t == n) {
            continue;
        }
        return((t > n ? 1 * resultMult : -1 * resultMult));;
    }
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
    if (A.length() == 0) {
        S = B;
		return;
    }
    if (B.length() == 0) {
        S = A;
		return;
    }
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

void subList(List& S, List A, List B, int signA, int signB) {
    A.moveBack();
    B.moveBack();
    long x, a, b;
    while (A.position() > 0 && B.position() > 0) {
        a = A.movePrev() * signA;
        b = B.movePrev() * signB;
        x = a - b;
        S.insertAfter(x);
    }
    while (A.position() > 0) {
        a = A.movePrev() * signA; 
        S.insertAfter(a);
    }
    while (B.position() > 0) {
       b = B.movePrev() * signB * -1; 
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

void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertBefore(0);
    }
}

void scalarMultList(List& L, ListElement m) {
    L.moveBack();
    while (L.position() > 0) {
        int value = L.peekPrev();
        int x = value * m;
        L.setBefore(x);
        L.movePrev();
    }
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
    List vectorSub;
    List tD = digits;
    List nD = N.digits;
    subList(vectorSub, digits, N.digits, signum, N.signum);
    int sign = normalizeList(vectorSub);
    D.digits = vectorSub;
    D.signum = sign;
    return(D);
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger P;
    if (signum == 0 || N.signum == 0) {
        return(P);
    }
    if ((signum == 1 && N.signum == 1) || (signum == -1 && N.signum == -1)) {
        P.signum = 1;
    } else {
        P.signum = -1;
    }
    
    List longer, shorter, total;
    if (digits.length() >= N.digits.length()) {
        longer = digits;
        shorter = N.digits;
    } else {
        longer = N.digits;
        shorter = digits; 
    }
    shorter.moveBack();
    int shift = 0;
    while (shorter.position() > 0) {
        List l = longer;
		List t;
        scalarMultList(l, shorter.movePrev());
        shiftList(l, shift);
        sumList(t, l, total, 1, 1);
        normalizeList(t);
        total = t;
        shift++;
    }
	P.digits = total;
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
    return((A.compare(B) == 0) ? true : false);
}

bool operator<( const BigInteger& A, const BigInteger& B) {
    return((A.compare(B) < 0) ? true : false);
}

bool operator<=( const BigInteger& A, const BigInteger& B) {
    return((A.compare(B) <= 0) ? true : false);
}

bool operator>( const BigInteger& A, const BigInteger& B) {
    return((A.compare(B) > 0) ? true : false);
}

bool operator>=( const BigInteger& A, const BigInteger& B) {
    return((A.compare(B) >= 0) ? true : false);
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return(A.add(B));
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return(A);
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return(A.sub(B));
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return(A);
}

BigInteger operator*( const BigInteger& A, const BigInteger& B) {
    return(A.mult(B));
}

BigInteger operator*=( BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return(A);
}