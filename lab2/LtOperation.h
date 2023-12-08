#ifndef LAB2_LTOPERATION_H
#define LAB2_LTOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class LtOperation : public Operation {
public:
    void statement(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_LTOPERATION_H
