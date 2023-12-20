#ifndef LAB2_EQOPERATION_H
#define LAB2_EQOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class EqOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_EQOPERATION_H
