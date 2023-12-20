#ifndef LAB2_GTOPERATION_H
#define LAB2_GTOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class GtOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_GTOPERATION_H
