#ifndef LAB2_SUBOPERATION_H
#define LAB2_SUBOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class SubOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_SUBOPERATION_H
