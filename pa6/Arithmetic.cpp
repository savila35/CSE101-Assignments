//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa6
// Arithmetic.cpp
// Performs several arithmetic operations on given integers
//------------------------------------------------------------------------------

#include "BigInteger.h"
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
    std::string lineA;
    std::string trash;
    std::string lineB;
    std::getline(in, lineA);
    std::getline(in, trash);
    std::getline(in, lineB);
    BigInteger A(lineA);
    BigInteger B(lineB);
    out << A << std::endl << std::endl;
    out << B << std::endl << std::endl; 
    out << A + B << std::endl << std::endl;
    out << A - B << std::endl << std::endl;
    out << A - A << std::endl << std::endl;
    out << ((3 * A) - (2 * B)) << std::endl << std::endl;
    out << A * B << std::endl << std::endl;
    out << A * A << std::endl << std::endl;
    out << B * B << std::endl << std::endl;
    out << ((9 * (A * A * A * A)) + (16 * (B * B * B * B * B))) << std::endl << std::endl;
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
