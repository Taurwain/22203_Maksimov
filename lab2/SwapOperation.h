#ifndef LAB2_SWAPOPERATION_H
#define LAB2_SWAPOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class SwapOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_SWAPOPERATION_H
