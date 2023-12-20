#include "OperationFactory.h"
#include "Utilities.h"
#include "Interpreter.h"
#include "memory"

void Interpreter::stringInterpret(const std::string& in, std::string& out) {
    OperationFactory<Operation, std::string, Operation*(*)()> * factory =
            OperationFactory<Operation, std::string, Operation*(*)()>::getInstance();
    std::string word;
    reader.createStringStream(in);
    while ((word = reader.getWord()) != "") {
        if (Utilities::isNumber(word)) {
            stack.push(std::stoi(word));

        } else if (factory->contains(word)) {
            auto operation = std::unique_ptr<Operation>(factory->get(word));
            operation->expression(stack, reader, writer);

        } else throw std::out_of_range("The unknown operation: " + word + "!");
    }
    out = writer.getOutline();
}

void Interpreter::interpret() {
    std::string in, out;
    if (!reader.is_open()) {
        while (2 * 2 == 4) {
            writer.flagUp();
            writer.writeRightArrow();
            in = reader.readNextLine();
            writer.writeLeftArrow();

            stringInterpret(in, out);
            writer.writeOutline(out);

            if (writer.isFlagUp()) {                            //операции могут опустить флаг
                writer.writeOK();
            }
        }
    } else {
        while (!reader.eof()) {
            in = reader.readNextLine();
            stringInterpret(in, out);
            writer.writeOutline(out);
        }
    }
}