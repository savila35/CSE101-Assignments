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

void sumList(List& S, List A, List B, int sign) {
    A.moveBack();
    B.moveBack();
    long x, a, b;
    while (A.position() > 0 && B.position() > 0) {
        a = A.movePrev();
        b = B.movePrev() * sign;
        x = a + b;
        S.insertAfter(x);
    }
    while (A.position() > 0) {
        a = A.movePrev(); 
        S.insertAfter(a);
    }
    while (B.position() > 0) {
		b = B.movePrev(); 
        S.insertAfter(b) * sign;
    }
}


// BigInteger Arithmetic operations --------------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger S;
    List vectorSum;
	List A = digits;
	List B = N.digits;
	if (signum == 0) {
		S = N;
		return(S);
	} else if (N.signum == 0) {
		S = this;
		return(S);
	}
	if (signnum == N.signum) {
		sumList(vectorSum, A, B, 1);
		if (signum < 0) {
			S.signum = -1;
		} else {
			S.signum = 1;
		}
	} else if (signum < 0) {
		S = N.sub(this);
		return(S);
	} else {
		S = this.sub(N);
		return(S);
	}
    int carry = 0;
    vectorSum.moveBack();
    while (vectorSum.position() > 0) {
        long x = vectorSum.movePrev();
        carry = x / base;
        x = x % base;
        S.digits.insertAfter(x + carry);
    }
	if (S.digits.front() > 0) {
		S.signum = 1;
	} else if (S.digits.front() < 0) {
		S.signum = -1;
	} else {
		S.signum = 0;
	}
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
