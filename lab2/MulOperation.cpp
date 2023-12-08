#include "MulOperation.h"

void MulOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();
    int sign = (a/abs(a)) * (b/ abs(b));

    if (sign > 0) {
        if (Utilities::checkOverflowMul(a, b)) {
            throw std::overflow_error("Error: multiplication overflow");
        }
    } else if (Utilities::checkUnderflowMul(a, b)) {
        throw std::overflow_error("Error: multiplication underflow");
    }
    stack.push(a * b);


}

namespace {
    OperationRegistrar<MulOperation> MulOperation("*");
}