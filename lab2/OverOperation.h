#ifndef LAB2_OVEROPERATION_H
#define LAB2_OVEROPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class OverOperation : public Operation {
public:
    void statement(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_OVEROPERATION_H
