#ifndef LAB2_ROTOPERATION_H
#define LAB2_ROTOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class RotOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_ROTOPERATION_H
