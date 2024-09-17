#include "CSVReader.hpp"
#include <fstream>
#include <sstream>

const char CSV_SEPARATOR = ',';

using namespace std;

CsvReader::CsvReader(string filename)
{
    this->file = ifstream(filename);
    string line;
    getline(this->file, line);
    this->currentLine = new istringstream(line);
}

string CsvReader::GetNextItem()
{
    string item;
    getline(*(this->currentLine), item, CSV_SEPARATOR);
    return item;
}

bool CsvReader::GoToNextLine()
{
    string line;
    if (getline(this->file, line)){
        delete this->currentLine;
        this->currentLine = new istringstream(line);
        return true;
    }
    return false;
}
