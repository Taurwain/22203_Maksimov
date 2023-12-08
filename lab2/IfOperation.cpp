#include "IfOperation.h"

void IfOperation::statement(std::stack<int> &stack, Reader &reader, Writer &writer) {
    if (!Utilities::checkTheValue(stack)) {
        throw std::out_of_range( "Error: not enough operands");
    }
    int cond = stack.top();
    stack.pop();
    OperationFactory<Operation, std::string, Operation *(*)()> *factory =
            OperationFactory<Operation, std::string, Operation *(*)()>::getInstance();
    std::string word;
    int ifCounter = 1;

    if (cond) {
        while ((word = reader.getWord()) != "THEN" && word != "ELSE") {

            if (!writer.isFlagUp()) {
                writer.writeLeftArrow();
                writer.flagUp();
            }

            if (Utilities::isNumber(word)) {
                stack.push(std::stoi(word));

            } /*else if (word == "IF") {
                this->statement(stack, reader, writer);

            }*/
            else if (factory->contains(word)) {
                Operation *operation = factory->get(word);
                operation->statement(stack, reader, writer);

            } else throw std::out_of_range("The unknown operation!");
        }

        if (word == "THEN") ifCounter--;

        while ((word = reader.getWord()) != "") {
            if (word == "IF") {
                ifCounter++;
            }
            if (word == "THEN") {
                ifCounter--;
            }
            if (word == ";") {
                if (!ifCounter) {
                    return;
                } else {
                    throw std::out_of_range("Error: syntax issue with \"if\"");
                }
            }
        }
        throw std::out_of_range("Error: syntax issue with \"if\"");

        } else {
        while ((word = reader.getWord()) != "") {
            if (word == "ELSE") {
                if (ifCounter == 1) {
                    break;
                }
            }
            if (word == "IF") {
                ifCounter++;
            }
            if (word == "THEN") {
                ifCounter--;
            }
            if (word == ";") {
                if (!ifCounter) {
                    return;
                }
            }
        }

        while ((word = reader.getWord()) != "THEN") {

            if (!writer.isFlagUp()) {
                writer.writeLeftArrow();
                writer.flagUp();
            }

            if (Utilities::isNumber(word)) {
                stack.push(std::stoi(word));

            } else if (factory->contains(word)) {
                Operation *operation = factory->get(word);
                operation->statement(stack, reader, writer);

            } else throw std::out_of_range("The unknown operation!");
        }

        if (word == "THEN") ifCounter--;

        while ((word = reader.getWord()) != "") {
            if (word == "THEN") {
                ifCounter--;
            }
            if (word == ";") {
                if (!ifCounter) {
                    return;
                } else {
                    throw std::runtime_error("Error: syntax issue with \"if\"");
                }
            }
        }
        throw std::out_of_range("Error: syntax issue with \"if\"");
    }
}

namespace {
    OperationRegistrar<IfOperation> IfOperation("IF");
}