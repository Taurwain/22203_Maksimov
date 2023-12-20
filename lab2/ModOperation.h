#ifndef LAB2_MODOPERATION_H
#define LAB2_MODOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class ModOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_MODOPERATION_H
