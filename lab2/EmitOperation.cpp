#include <iostream>
#include "EmitOperation.h"

void EmitOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    if (!Utilities::checkTheValue(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    writer.write(char(stack.top()));
    stack.pop();
    writer.flagDown();
}

namespace {
    OperationRegistrar<EmitOperation> EmitOperation("EMIT");
}