#ifndef LAB2_WRITER_H
#define LAB2_WRITER_H

#include <iostream>
#include <fstream>

class Writer {
public:
    Writer() = default;
    Writer(Writer&& otherWriter) noexcept : outputFile(std::move(otherWriter.outputFile)),
        outputLine(std::move(otherWriter.outputLine)), flag(otherWriter.flag) {};
    void open(const std::string& OUTPUT_FILE);
    bool isFlagUp() const;
    void flagUp();
    void flagDown();
    void write(int number);
    void write(const std::string& word);
    void write(char symbol);
    void writeOutline(std::string& out);
    std::string getOutline();
    void writeRightArrow();
    void writeLeftArrow();
    void writeOK();
    ~Writer();

private:
    int flag = 1;
    std::ofstream outputFile;
    std::string outputLine;
};

#endif //LAB2_WRITER_H
