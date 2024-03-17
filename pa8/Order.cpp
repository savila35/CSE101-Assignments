//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa7
// Order.cpp
// Reads strings from file and adds to dictionary with value of line number in source file
//------------------------------------------------------------------------------

#include "Dictionary.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
		return(EXIT_FAILURE);
	}
	
	std::ifstream in;
	std::ofstream out;
	in.open(argv[1]);
    if( !in.is_open() ){
        std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
        return(EXIT_FAILURE);
    }
	int line = 0;
	std::string word;
	Dictionary D;
	while (std::getline(in, word)) {
		line++;
		D.setValue(word, line);
	}
	out << D << std::endl;
	out << D.pre_string() << std::endl;
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
