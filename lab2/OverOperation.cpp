#include <stack>
#include "OverOperation.h"

void OverOperation::expression(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int num1 = stack.top();
    stack.pop();
    int num2 = stack.top();
    stack.push(num1);
    stack.push(num2);
}

namespace {
    OperationRegistrar<OverOperation> OverOperation("OVER");
}