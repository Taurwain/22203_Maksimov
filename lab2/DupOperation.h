#ifndef LAB2_DUPOPERATION_H
#define LAB2_DUPOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class DupOperation : public Operation {
public:
    void statement(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_DUPOPERATION_H
