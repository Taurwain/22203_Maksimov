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
    Interpreter(Reader&& _reader, Writer&& _writer)
        : reader(std::move(_reader)), writer(std::move(_writer)) {};
    void interpret();
    void stringInterpret(const std::string& in, std::string& out);

private:
    Reader reader;
    Writer writer;
    std::stack<int> stack;
};

#endif //LAB2_INTERPRETER_H
