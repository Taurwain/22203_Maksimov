#include "SubOperation.h"

void SubOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();
    if (Utilities::checkOverflowSub(a, b)) {
        throw std::overflow_error("Error: subtraction overflow");
    } else if (Utilities::checkUnderflowSub(a, b)) {
        throw std::overflow_error("Error: subtraction underflow");
    } else stack.push(a - b);
}

namespace {
    OperationRegistrar<SubOperation> SubOperation("-");
}