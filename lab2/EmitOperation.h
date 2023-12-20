#ifndef LAB2_EMITOPERATION_H
#define LAB2_EMITOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class EmitOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_EMITOPERATION_H
