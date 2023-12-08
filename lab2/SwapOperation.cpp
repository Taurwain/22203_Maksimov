#include "SwapOperation.h"

void SwapOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int num1 = stack.top();
    stack.pop();
    int num2 = stack.top();
    stack.pop();
    stack.push(num1);
    stack.push(num2);
}

namespace {
    OperationRegistrar<SwapOperation> SwapOperation("SWAP");
}