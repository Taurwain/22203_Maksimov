#ifndef LAB2_OPERATION_H
#define LAB2_OPERATION_H

#include <string>
#include <stack>
#include <stdexcept>
#include "Utilities.h"
#include "Reader.h"
#include "Writer.h"

class Operation {
public:
    virtual void statement(std::stack<int>& stack, Reader& reader, Writer& writer) = 0;
};

#endif //LAB2_OPERATION_H