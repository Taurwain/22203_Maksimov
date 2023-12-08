#ifndef LAB2_READER_H
#define LAB2_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Writer.h"

class Reader {
public:
    void open(const std::string& INPUT_FILE);
    void readNextLine();
    std::string getWord();
    std::string getStringToSymbol(char symbol);
    std::streampos getStreamMark();
    void setStreamMark(std::streampos forPos);
    ~Reader();

private:
    std::ifstream inputFile;
    std::istringstream bufStream;
};

#endif //LAB2_READER_H
