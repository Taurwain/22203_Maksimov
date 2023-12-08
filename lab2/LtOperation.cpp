#include "LtOperation.h"

void LtOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();
    stack.push(a < b);
}

namespace {
    OperationRegistrar<LtOperation> LtOperation("<");
}