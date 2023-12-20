#ifndef LAB2_DIVOPERATION_H
#define LAB2_DIVOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class DivOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};


#endif //LAB2_DIVOPERATION_H
