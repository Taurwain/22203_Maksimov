#include "DivOperation.h"

void DivOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range("Error: not enough operands");
    }
    int b = stack.top();
    if (Utilities::checkZeroDivision(b)) {
        throw std::runtime_error("Error: division by zero");
    }
    stack.pop();
    int a = stack.top();
    stack.pop();
    stack.push(a / b);
}

namespace {
    OperationRegistrar<DivOperation> DivOperation("/");
}