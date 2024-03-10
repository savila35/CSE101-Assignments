#include "Dictionary.h"
#include <iostream>
#include <assert.h>

int main() {
	Dictionary A;
	std::string words[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	for (int i = 1; i <= 26; i++) {
		A.setValue(words[i - 1], i);
		assert(A.size() == i);
	}
	assert(A.contains("blah") == false);
	assert(A.contains("a") == true);
	assert(A.getValue("z") == 26);
	assert(A.hasCurrent() == false);
	A.begin();
	assert(A.hasCurrent() == true);
	assert(A.currentKey() == "a");
	assert(A.currentVal() == 1);
	A.next();
	assert(A.currentKey() == "b");
	A.prev();
	assert(A.currentVal() == 1);
	A.end();
	assert(A.currentKey() == "z");
	A.setValue("a", 100);
	assert(A.getValue("a") == 100);
	Dictionary B = A;
	assert(A == B);
	assert(B.equals(A));
	B.remove("a");
	assert(!(A == B));
	B.clear();
	assert(B.size() == 0);
	assert(B.contains("a") == false);
	std::cout << A << std::endl;
	std::cout << A.pre_string() << std::endl;
	A.end();
	A.remove("z");
	assert(A.hasCurrent() == false);
	return(0);
}
