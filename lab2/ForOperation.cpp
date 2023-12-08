#include <vector>
#include "ForOperation.h"

void ForOperation::statement(std::stack<int> &stack, Reader &reader, Writer &writer) {
    if (!Utilities::checkTwoOperands(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int begin = stack.top();
    stack.pop();
    int end = stack.top();
    stack.pop();
    OperationFactory<Operation, std::string, Operation *(*)()> *factory =
            OperationFactory<Operation, std::string, Operation *(*)()>::getInstance();

    std::string word;

    std::streampos forPos = reader.getStreamMark();

    for (int i = begin; i < end; i++) {
        while ((word = reader.getWord()) != "LOOP") {
            if (!writer.isFlagUp()) {
                writer.writeLeftArrow();
                writer.flagUp();
            }

            if (Utilities::isNumber(word)) {
                stack.push(std::stoi(word));

            } else if (word == "I") {
                stack.push(i);

            } else if (factory->contains(word)) {
                Operation *operation = factory->get(word);
                operation->statement(stack, reader, writer);

            } else throw std::out_of_range("The unknown operation!");
        }

        if (i < end - 1) {
            reader.setStreamMark(forPos);
        }
    }

    if ((word = reader.getWord()) == ";") {
        return;
    } else {
        throw std::out_of_range("Error: syntax issue with \"for\"");
    }
}

namespace {
    OperationRegistrar<ForOperation> ForOperation("DO");
}