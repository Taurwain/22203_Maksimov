#include "DotQuoteOperation.h"

void DotQuoteOperation::statement(std::stack<int> &stack, Reader &reader, Writer &writer) {
    std::string newString = reader.getStringToSymbol('\"');
    if (newString[newString.size() - 1] != '\"') {
        throw std::out_of_range(R"(Error: syntax issue with "."")");
    }
    newString.erase(newString.size() - 1);
    newString.erase(newString.begin());
    writer.write(newString);
    writer.flagDown();
}

namespace {
    OperationRegistrar<DotQuoteOperation> DotQuotOperation(".\"");
}