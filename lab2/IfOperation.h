#ifndef LAB2_IFOPERATION_H
#define LAB2_IFOPERATION_H

#include "Operation.h"
#include "OperationFactory.h"
#include "OperationRegistrar.h"

class IfOperation : public Operation {
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_IFOPERATION_H
