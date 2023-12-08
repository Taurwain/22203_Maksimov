#ifndef MAIN_CPP_OPERATIONREGISTRAR_H
#define MAIN_CPP_OPERATIONREGISTRAR_H

#include "OperationFactory.h"
#include "Operation.h"

template<class SomeOperation>
class OperationRegistrar{
public:
    OperationRegistrar(const std::string& Id) {
        OperationFactory<Operation, std::string, Operation *(*)()>::getInstance()
                ->registerWord(Id, createOperation);
    }

private:
    static Operation* createOperation() {
        return new SomeOperation();
    }
};

#endif //MAIN_CPP_OPERATIONREGISTRAR_H
