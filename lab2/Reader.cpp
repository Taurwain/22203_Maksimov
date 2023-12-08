#include "Reader.h"

void Reader::open(const std::string& INPUT_FILE) {
    if (inputFile.is_open()) {
        inputFile.close();
    }
    inputFile.open(INPUT_FILE);
    if (!inputFile.is_open()) {
        throw std::ios_base::failure("Error: The file cannot be opened!");
    }
}

void Reader::readNextLine() {
    std::string codeLine;
    std::getline(std::cin, codeLine);
    std::istringstream newBufStream(codeLine);
    bufStream = std::move(newBufStream);
}

std::string Reader::getWord() {
    std::string word;
    if (inputFile.is_open()) {
        inputFile >> word;
    } else {
        bufStream >> word;
    }
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

    if (inputFile.is_open()) {
        while (inputFile.get(c)) {
            string += c;
            if (c == symbol) {
                break;
            }
        }
    } else {
        while (bufStream.get(c)) {
            string += c;
            if (c == symbol) {
                break;
            }
        }
    }

    return string;
}

Reader::~Reader() {
    if (inputFile) {
        inputFile.close();
    }
}
