#ifndef LAB2_WRITER_H
#define LAB2_WRITER_H

#include <iostream>
#include <fstream>

class Writer {
public:
    Writer() = default;
    void open(const std::string& OUTPUT_FILE);
    bool isFlagUp() const;
    void flagUp();
    void flagDown();
    void write(int number);
    void write(const std::string& word);
    void write(char symbol);
    void writeRightArrow();
    void writeLeftArrow();
    ~Writer();

private:
    int flag = 1;
    std::ofstream outputFile;
};

#endif //LAB2_WRITER_H
