#ifndef LAB2_OPERATIONFACTORY_H
#define LAB2_OPERATIONFACTORY_H

#include <string>
#include <map>
#include "Operation.h"

template <class Product, class Id, class Creator>
class OperationFactory {
public:
    static OperationFactory* getInstance() {
        static OperationFactory factory;
        return &factory;
    }

    void registerWord(const Id& word, Creator creator) {
        if (!operationFactory.count(word)) {
            operationFactory[word] = creator;
        }
    }

    Operation* get(const Id& word) {
        auto creator = operationFactory[word];
        return creator();
    }

    bool contains(const Id& word) {
        return operationFactory.count(word);
    }

private:
    std::map<Id, Creator> operationFactory;
    OperationFactory() = default;
};

#endif //LAB2_OPERATIONFACTORY_H
