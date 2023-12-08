#include "AddOperation.h"
#include "OperationRegistrar.h"
#include "OperationFactory.h"

void AddOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();
    if (Utilities::checkOverflowAdd(a, b)) {
        throw std::overflow_error("Error: addition overflow");
    } else if (Utilities::checkUnderflowAdd(a, b)) {
        throw std::overflow_error("Error: addition underflow");
    } else stack.push(a + b);
}

namespace {
    OperationRegistrar<AddOperation> AddOperation("+");
}
