#ifndef LAB2_INTERPRETER_H
#define LAB2_INTERPRETER_H

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include "Reader.h"
#include "Writer.h"

class Interpreter {
public:
    Interpreter() = default;
    void interpret();
    void interpret(const std::string& INPUT_FILE, const std::string& OUTPUT_FILE);

private:
    Reader reader;
    Writer writer;
    std::stack<int> stack;
};

#endif //LAB2_INTERPRETER_H
