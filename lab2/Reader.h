#ifndef LAB2_READER_H
#define LAB2_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Writer.h"

class Reader {
public:
    Reader() = default;
    Reader(Reader&& otherReader) noexcept : inputFile(std::move(otherReader.inputFile)),
        bufStream(std::move(otherReader.bufStream)) {};
    void open(const std::string& INPUT_FILE);
    std::string readNextLine();
    void createStringStream(const std::string& in);
    void setStreamMark(std::streampos forPos);
    std::string getWord();
    std::string getStringToSymbol(char symbol);
    std::streampos getStreamMark();
    bool is_open();
    bool eof();
    ~Reader();

private:
    std::ifstream inputFile;
    std::istringstream bufStream;
};

#endif //LAB2_READER_H
