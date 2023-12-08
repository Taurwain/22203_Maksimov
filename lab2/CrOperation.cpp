#include "CrOperation.h"

void CrOperation::statement(std::stack<int>& stack, Reader& reader, Writer& writer) {
    writer.write("\n");
    writer.flagDown();
}

namespace {
    OperationRegistrar<CrOperation> AddOperation("CR");
}