#ifndef MAIN_CPP_FOROPERATION_H
#define MAIN_CPP_FOROPERATION_H

#include "Operation.h"
#include "OperationFactory.h"
#include "OperationRegistrar.h"

class ForOperation : public Operation {
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //MAIN_CPP_FOROPERATION_H
