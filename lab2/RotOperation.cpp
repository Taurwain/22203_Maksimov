#include "RotOperation.h"

void RotOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkThreeOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int num1 = stack.top();
    stack.pop();
    int num2 = stack.top();
    stack.pop();
    int num3 = stack.top();
    stack.pop();
    stack.push(num2);
    stack.push(num1);
    stack.push(num3);
}

namespace {
    OperationRegistrar<RotOperation> RotOperation("ROT");
}