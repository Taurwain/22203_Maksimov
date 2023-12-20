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
    outputLine += std::to_string(number);
}

void Writer::write(const std::string& word) {
    outputLine += word;
}

void Writer::write(char symbol) {
    outputLine += symbol;
}

void Writer::writeOutline(std::string& out) {
    if (out.empty()) {
        return;
    }
    if (outputFile.is_open()) {
        outputFile << out << " ";
    } else {
        std::cout << out << std::endl;
    }
    outputLine = "";
}

std::string Writer::getOutline() {
    std::string output = outputLine;
    outputLine = "";
    return output;
}

void Writer::writeRightArrow() {
    if (!outputFile.is_open()) std::cout << "> ";
}

void Writer::writeLeftArrow() {
    if (!outputFile.is_open()) std::cout << "< ";
}

void Writer::writeOK() {
    if (!outputFile.is_open()) std::cout << "ok" << std::endl;
}

Writer::~Writer() {
    if (outputFile) {
        outputFile.close();
    }
}