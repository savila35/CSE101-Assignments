//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa6
// BigInteger.cpp
// Implementation file for BigInteger ADT
//------------------------------------------------------------------------------

#include "BigInteger.h"

// Global Constants ------------------------------------------------------------
const int power = 9;
const long base = 1000000000;

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
 	while (s.front() == '0') {
		s.erase(0,1);
	}
    while (s.length() % power != 0) {
        s = "0" + s;
    }
	for (char ch : s) {
        if (!(ch >= 48 && ch <= 57)) {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string\n");
        }
	}
	if (s.empty()) {
		throw std::invalid_argument("BigInteger: Constructor: empty string\n");
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
        long t = tL.moveNext();
        long n = nL.moveNext();
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

void negateList(List& L) {
    L.moveBack();
    while (L.position() > 0) {
        long x = L.movePrev() * -1;
        L.setAfter(x);
    }
}

void sumList(List& S, List A, List B, int sign) {
    S.clear();
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
    while (A.position() > 0 && B.position() > 0) {
        long a = A.movePrev();
        long b = B.movePrev();
        long x = a + (b * sign);
        S.insertAfter(x);
    }
    while (A.position() > 0) {
        long a = A.movePrev();
        S.insertAfter(a);
    }
    while (B.position() > 0) {
        long b = B.movePrev();
        S.insertAfter(b * sign);
    }
}

int normalizeList(List& L) {
    long carry = 0;
    long x = 0;
    L.moveBack();
    while (L.position() > 0) {
        long value = L.movePrev() + carry;
        if (value >= base) {
            if (value % base != 0) {
                x = value - (value % base);
                L.setAfter(value - x);
                carry = x / base;
				continue;
            } 
			carry = value / base;
			L.setAfter(0);
			continue;
        }  
		if (value < 0 && L.position() > 0) {
            if (value % base != 0) {
                x = value - (base + (value % base));
                L.setAfter(value - x);
                carry = x / base;
				continue;
            } 
			carry = value / base;
			L.setAfter(0);
			continue;
        } 
		carry = 0;
		L.setAfter(value);	
    }
    if (carry != 0) {
        L.insertAfter(carry);
        carry = 0;
    }
    while (L.length() > 0 && L.front() == 0) {
        L.moveFront();
        L.eraseAfter(); 
    }
    if (L.length() == 0) {
        return(0);
    }
    if (L.front() > 0) {
        return 1;
    } 
	L.moveBack();
	while (L.position() > 0) {
		long x = L.movePrev() * -1;
		x += carry;
		if (x < 0) {
			L.setAfter(x + base);
			carry = -1;
			continue;
		} 
		L.setAfter(x);
		carry = 0;
    }
    return(-1);
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
        long value = L.movePrev();
        long x = value * m;
        L.setAfter(x);
    }
}


// BigInteger Arithmetic operations --------------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger S;
    if (signum == 1 && N.signum == 1) {
        sumList(S.digits, digits, N.digits, 1);
    } else if (signum == -1 && N.signum == 1) {
        sumList(S.digits, N.digits, digits, -1);
    } else if (signum == 1 && N.signum == -1) {
        sumList(S.digits, digits, N.digits, -1);
    } else if (signum == -1 && N.signum == -1) {
        List tD = digits;;
        negateList(tD);
        sumList(S.digits, tD, N.digits, -1);
    } else {
        sumList(S.digits, digits, N.digits, 1);
        S.signum = (signum == 0) ? N.signum : signum;
        return(S);
    }

    int sign = normalizeList(S.digits);
    S.signum = sign;
    return(S);
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger D;
    if (signum == 1 && N.signum == 1) {
        sumList(D.digits, digits, N.digits, -1);
    } else if (signum == -1 && N.signum == 1) {
        List tD = digits;
        negateList(tD);
        sumList(D.digits, tD, N.digits, -1);
    } else if (signum == 1 && N.signum == -1) {
        sumList(D.digits, digits, N.digits, 1);
    } else if (signum == -1 && N.signum == -1) {
        List tD = digits;
        negateList(tD);
        sumList(D.digits, tD, N.digits, 1);
    }

    int sign = normalizeList(D.digits);
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
    
    int shift = 0;
    List total;
    List temp;
    List tD = digits;
    List D = digits;
    List nD = N.digits;
	D.moveBack();
    while (D.position() > 0) {
        long x = D.movePrev();
		scalarMultList(nD, x);
        sumList(temp, temp, nD, 1);
        normalizeList(temp);
        shiftList(temp, shift);
        sumList(total, total, temp, 1);
        normalizeList(total);
        shift++;
        temp.clear();
        nD = N.digits;
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
