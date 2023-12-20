#include "CrOperation.h"

void CrOperation::expression(std::stack<int>& stack, Reader& reader, Writer& writer) {
    writer.write("\n");
    writer.flagDown();
}

namespace {
    OperationRegistrar<CrOperation> CrOperation("CR");
}