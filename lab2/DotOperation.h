#ifndef LAB2_DOTOPERATION_H
#define LAB2_DOTOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class DotOperation : public Operation {
public:
    void statement(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_DOTOPERATION_H
