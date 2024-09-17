#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Error.hpp"


using namespace std;

class CsvReader
{
private:
    ifstream file;
    istringstream* currentLine;
public:
    CsvReader(string filename);
    string GetNextItem();
    bool GoToNextLine();
};

#endif