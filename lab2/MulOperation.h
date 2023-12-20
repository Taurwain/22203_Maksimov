#ifndef LAB2_MULOPERATION_H
#define LAB2_MULOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class MulOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_MULOPERATION_H
