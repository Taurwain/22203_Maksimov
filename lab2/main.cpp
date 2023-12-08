#include <gtest/gtest.h>
#include "Interpreter.h"

int main(int argc, char **argv) {
    Interpreter interpreter;
    interpreter.interpret();
    //"in.txt", "out.txt"

    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    return 0;
}