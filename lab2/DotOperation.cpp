#include <iostream>
#include "DotOperation.h"

void DotOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTheValue(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    writer.write(stack.top());
    writer.flagDown();
    stack.pop();
}

namespace {
    OperationRegistrar<DotOperation> DotOperation(".");
}