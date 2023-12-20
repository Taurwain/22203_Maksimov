#ifndef LAB2_ADDOPERATION_H
#define LAB2_ADDOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class AddOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_ADDOPERATION_H
