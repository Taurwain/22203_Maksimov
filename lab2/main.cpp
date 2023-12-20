#include <gtest/gtest.h>
#include "Interpreter.h"
#include "Reader.h"
#include "Writer.h"

int main(int argc, char **argv) {
    //Reader _reader;
    //Writer _writer;
    //_reader.open("in.txt");
    //_writer.open("out.txt");
    //Interpreter interpreter(std::move(_reader), std::move(_writer));
    //interpreter.interpret();
    //interpreter.interpret("in.txt", "out.txt");
    //"in.txt", "out.txt"

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //return 0;
}