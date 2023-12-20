#include "Reader.h"

void Reader::open(const std::string& INPUT_FILE) {
    if (is_open()) {
        inputFile.close();
    }
    inputFile.open(INPUT_FILE);
    if (!is_open()) {
        throw std::ios_base::failure("Error: The file cannot be opened!");
    }
}

void Reader::createStringStream(const std::string& in) {
    bufStream = std::move(std::istringstream(in));
}

bool Reader::is_open() {
    return inputFile.is_open();
}

bool Reader::eof() {
    return inputFile.eof();
}

std::string Reader::readNextLine() {
    std::string codeLine;
    if (inputFile.is_open()) {
        std::getline(inputFile, codeLine);
    } else {
        std::getline(std::cin, codeLine);
    }
    std::istringstream newBufStream(codeLine);
    return codeLine;
}

std::string Reader::getWord() {
    std::string word;
    bufStream >> word;
    return word;
}

std::streampos Reader::getStreamMark() {
    if (inputFile.is_open()) {
        return inputFile.tellg();
    } else return bufStream.tellg();
}

void Reader::setStreamMark(std::streampos forPos) {
    if (inputFile.is_open()) {
        inputFile.seekg(forPos);
    } else bufStream.seekg(forPos);
}

std::string Reader::getStringToSymbol(char symbol) {
    std::string string;
    char c;

    while (bufStream.get(c)) {
        string += c;
        if (c == symbol) {
            break;
        }
    }
    return string;
}

Reader::~Reader() {
    if (inputFile) {
        inputFile.close();
    }
}
