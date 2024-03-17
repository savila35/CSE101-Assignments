//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa8
// WordFrequency.cpp
// Counts the frequency of words in given file using Dictionary ADT
//------------------------------------------------------------------------------

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

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

    std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    std::string line, token;
    size_t begin, end, length;
    Dictionary D;

    while (getline(in, line)) {
        length = line.length();
        begin = std::min(line.find_first_not_of(delim, 0), length);
        end   = std::min(line.find_first_of(delim, begin), length);
        token = line.substr(begin, end-begin);
        while (token != "") {
            for (char& letter : token) {
                letter = std::tolower(letter);
            }
            if (D.contains(token)) {
                D.getValue(token)++;
            } else {
                D.setValue(token, 1);
            }
            begin = std::min(line.find_first_not_of(delim, end+1), length);
            end   = std::min(line.find_first_of(delim, begin), length);
            token = line.substr(begin, end-begin);
        }
    }
    out << D << std::endl;
    in.close();
    out.close();
	return(EXIT_SUCCESS);
}
