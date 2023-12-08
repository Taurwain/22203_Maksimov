#include "DupOperation.h"

void DupOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTheValue(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    stack.push(stack.top());
}

namespace {
    OperationRegistrar<DupOperation> AddOperation("DUP");
}