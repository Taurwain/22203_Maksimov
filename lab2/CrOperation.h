#ifndef LAB2_CROPERATION_H
#define LAB2_CROPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class CrOperation : public Operation {
public:
    void expression(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //LAB2_CROPERATION_H
