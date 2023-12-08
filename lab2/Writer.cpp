#include "Writer.h"

void Writer::open(const std::string& OUTPUT_FILE) {
    if (outputFile.is_open()) {
        outputFile.close();
    }
    outputFile.open(OUTPUT_FILE);
    if (!outputFile.is_open()) {
        throw std::ios_base::failure("Error: The file cannot be opened!");
    }
}

bool Writer::isFlagUp() const {
    return flag;
}

void Writer::flagUp() {
    flag = 1;
}

void Writer::flagDown() {
    flag = 0;
}

void Writer::write(int number) {
    if (outputFile.is_open()) {
        outputFile << number << std::endl;
    } else std::cout << number << std::endl;
}

void Writer::write(const std::string& word) {
    if (outputFile.is_open()) {
        outputFile << word << std::endl;
    } else std::cout << word << std::endl;
}

void Writer::write(char symbol) {
    if (outputFile.is_open()) {
        outputFile << symbol << std::endl;
    } else std::cout << symbol << std::endl;
}

void Writer::writeRightArrow() {
    if (!outputFile.is_open()) std::cout << "> ";
}

void Writer::writeLeftArrow() {
    if (!outputFile.is_open()) std::cout << "< ";
}

Writer::~Writer() {
    if (outputFile) {
        outputFile.close();
    }
}