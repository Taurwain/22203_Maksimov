#ifndef LAB2_DROPOPERATION_H
#define LAB2_DROPOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class DropOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_DROPOPERATION_H
