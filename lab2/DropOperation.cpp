#include "DropOperation.h"

void DropOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTheValue(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    stack.pop();
}

namespace {
    OperationRegistrar<DropOperation> DropOperation("DROP");
}