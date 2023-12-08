#include "OperationFactory.h"
#include "Utilities.h"
#include "Interpreter.h"

void Interpreter::interpret() {
    OperationFactory<Operation, std::string, Operation*(*)()> * factory =
            OperationFactory<Operation, std::string, Operation*(*)()>::getInstance();

    std::string word;

    while (2 * 2 == 4) {
        writer.flagUp();
        writer.writeRightArrow();
        reader.readNextLine();
        writer.writeLeftArrow();

        while ((word = reader.getWord()) != "") {
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

        if (writer.isFlagUp()) {                            //операции могут опустить флаг
            writer.write("ok");
        }
    }
}

void Interpreter::interpret(const std::string& INPUT_FILE, const std::string& OUTPUT_FILE) {
    OperationFactory<Operation, std::string, Operation*(*)()> * factory =
            OperationFactory<Operation, std::string, Operation*(*)()>::getInstance();

    std::string word;
    reader.open(INPUT_FILE);
    writer.open(OUTPUT_FILE);
    writer.flagDown();                                                              //запрет на вывод ">" и "< ok"

    //Utilities::restoreStack(stack);

    while ((word = reader.getWord()) != "") {                                       //работает с пустым in.txt
        if (Utilities::isNumber(word)) {
            stack.push(std::stoi(word));

        } else if (factory->contains(word)) {
            Operation *operation = factory->get(word);
            operation->statement(stack, reader, writer);

        } else throw std::out_of_range("The unknown operation!");
    }
}