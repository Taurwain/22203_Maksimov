#ifndef MAIN_CPP_DOTQUOTEOPERATION_H
#define MAIN_CPP_DOTQUOTEOPERATION_H

#include "Operation.h"
#include "OperationRegistrar.h"

class DotQuoteOperation : public Operation {
    void statement(std::stack<int>& stack, Reader& reader, Writer& writer) override;
};

#endif //MAIN_CPP_DOTQUOTEOPERATION_H
