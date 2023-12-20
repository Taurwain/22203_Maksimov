#include <gtest/gtest.h>
#include "Interpreter.h"
#include "Operation.h"
#include "Utilities.h"

TEST(Tests, arithmeticOperations) {
    Reader _reader;
    Writer _writer;
    //_reader.open("in.txt");
    //_writer.open("out.txt");

    std::vector<std::pair<std::string, std::string>> correctExpressionTestDataset = {
            {"3", ""},
            {"3 .", "3"},
            {"-3 .", "-3"},
            {"1 2 + .", "3"},
            {"5 3 - .", "2"},
            {"2 3 * .", "6"},
            {"6 2 / .", "3"},
            {"4 2 MOD .", "0"},
            {"2147483647 1 - .", "2147483646"},
            {"-2147483648 -1 - .", "-2147483647"},
            {"6 2 / 8 * 10 + -5 - 4 MOD .", "3"},
            {"10 5 + 7 + 10 + 100 + 1000 + -1132 + .", "0"},
            {"1 2 * 10 - 8 * 10 / 1000 + 32 MOD .", "2"}
    };

    for (const auto& i : correctExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        interpreter.stringInterpret(i.first, output);
        ASSERT_EQ(output, i.second);
    }

    std::vector<std::string> wrongExpressionTestDataset = {
            "+",
            "-",
            "*",
            "/",
            "MOD",
            "3 +",
            "3 -",
            "3 *",
            "3 /",
            "3 MOD"
    };

    for (const auto& i : wrongExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::out_of_range);
    }

    std::vector<std::string> forbiddenExpressionTestDataset = {
            "3 0 /",
            "3 0 MOD"
    };

    for (const auto& i : forbiddenExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::runtime_error);
    }

    std::vector<std::string> operationOverflowTestDataset = {
            "2147483647 1 +",
            "2147483647 -1 -",
            "-2147483648 -1 +",
            "-2147483648 1 -",
            "50000 50000 *",
            "50000 -50000 *",
            "-50000 50000 *",
            "-50000 -50000 *"
    };

    for (const auto& i : operationOverflowTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::overflow_error);
    }
}

TEST(Tests, logicOperations) {
    Reader _reader;
    Writer _writer;

    std::vector<std::pair<std::string, std::string>> correctExpressionTestDataset = {
            {"3", ""},
            {"3 0 < ", ""},
            {"3 0 < .", "0"},
            {"0 3 < .", "1"},
            {"3 5 < .", "1"},
            {"5 3 < .", "0"},
            {"3 0 > .", "1"},
            {"0 3 > .", "0"},
            {"3 5 > .", "0"},
            {"5 3 > .", "1"},
            {"3 0 = .", "0"},
            {"0 3 = .", "0"},
            {"3 3 = .", "1"},
            {"3 3 = .", "1"},
            {"9 10 + 4 * 9 4 * 10 4 * + = .", "1"},
            {"9 10 * 4 + 9 4 + 10 4 + * = .", "0"}
    };

    for (const auto& i : correctExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        interpreter.stringInterpret(i.first, output);
        ASSERT_EQ(output, i.second);
    }

    std::vector<std::string> wrongExpressionTestDataset = {
            "<",
            ">",
            "=",
            "3 <",
            "3 >",
            "3 ="
    };

    for (const auto& i : wrongExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::out_of_range);
    }
}

TEST(Tests, stackOperations) {
    Reader _reader;
    Writer _writer;

    std::vector<std::pair<std::string, std::string>> correctExpressionTestDataset = {
            {"3 DROP", ""},
            {"6 3 3 3 3 3 3 3 DROP DROP DROP DROP DROP DROP .", "3"},
            {"6 3 3 3 3 3 3 3 DROP DROP DROP DROP DROP DROP DROP .", "6"},
            {"3 DROP 3 DROP 3 DROP 3 DROP 3 DROP 3 DROP 3 .", "3"},
            {"3 DUP", ""},
            {"3 DUP .", "3"},
            {"3 DUP * .", "9"},
            {"3 DUP DROP DUP DROP DUP DROP DUP DROP DUP DROP .", "3"},
            {"3 4 OVER", ""},
            {"3 4 OVER .", "3"},
            {"3 4 OVER DROP .", "4"},
            {"3 4 OVER DROP DROP .", "3"},
            {"3 4 OVER DUP DROP .", "3"},
            {"3 4 OVER OVER OVER OVER OVER .", "3"},
            {"3 4 OVER OVER OVER OVER OVER OVER .", "4"},
            {"3 4 5 ROT ", ""},
            {"3 4 5 ROT .", "3"},
            {"3 4 5 ROT ROT .", "4"},
            {"3 4 5 ROT ROT ROT .", "5"},
            {"3 4 5 ROT DROP .", "5"},
            {"3 4 5 ROT DROP DROP .", "4"},
            {"3 3 4 ROT 3 = .", "1"},
            {"3 3 4 ROT OVER 3 = .", "0"},
            {"3 4 SWAP", ""},
            {"3 4 SWAP .", "3"},
            {"3 4 SWAP DROP .", "4"},
            {"3 4 SWAP", ""},
            {"3 6 / .", "0"},
            {"3 6 SWAP / .", "2"},
            {"3 4 5 DROP SWAP OVER .", "4"},
            {"3 DUP SWAP OVER ROT DROP .", "3"},
            {"3 4 SWAP SWAP SWAP SWAP SWAP SWAP . ", "4"},
            {"3 4 SWAP SWAP SWAP SWAP SWAP SWAP SWAP . ", "3"},
    };

    for (const auto& i : correctExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        interpreter.stringInterpret(i.first, output);
        ASSERT_EQ(output, i.second);
    }

    std::vector<std::string> wrongExpressionTestDataset {
            "DUP",
            "DROP",
            "ROT",
            "SWAP",
            "OVER",
            "3 DROP .",
            "3 3 * . DUP",
            "3 SWAP",
            "3 OVER",
            "3 ROT",
            "3 4 ROT",
            "3 DUP SWAP OVER ROT DROP DROP <"
    };

    for (const auto& i : wrongExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::out_of_range);
    }
}

TEST(Tests, outputOperations) {
    Reader _reader;
    Writer _writer;

    std::vector<std::pair<std::string, std::string>> correctExpressionTestDataset = {
            {"CR 3", "\n"},
            {"CR", "\n"},
            {"3", ""},
            {"3 .", "3"},
            {"3 3 3 3 3 .", "3"},
            {"3 3 3 3 4 .", "4"},
            {"3 3 3 3 3 + + + + .", "15"},
            {"65 EMIT", "A"},
            {"11 11 11 11 11 11 + + + + + EMIT", "B"},
            {"3 DUP 45 SWAP 8 90 * OVER 18 MOD ROT 64 + EMIT", "C"},
            {".\" this_is_a_string\"", "this_is_a_string"},
            {".\" this is a string with spaces\"", "this is a string with spaces"},
            {".\" this is a string with      many                spaces\"", "this is a string with      many                spaces"}
    };

    for (const auto& i : correctExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        interpreter.stringInterpret(i.first, output);
        ASSERT_EQ(output, i.second);
    }

    std::vector<std::string> wrongExpressionTestDataset {
            ".",
            "EMIT",
            "3 4 . +",
            "9 EMIT . =",
            ".\"abc\"",
            ".\" abc ",
            "\". abc \""
    };

    for (const auto& i : wrongExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::out_of_range);
    }
}

TEST(Tests, branchingOperations) {
    Reader _reader;
    Writer _writer;

    std::vector<std::pair<std::string, std::string>> correctExpressionTestDataset = {
            {"1 IF THEN ;",""},
            {"1 IF .\" true\" THEN ;","true"},
            {"0 IF .\" true\" THEN ;",""},
            {"1 IF 3 4 * 12 = 12 * . THEN ;","12"},
            {"90 2 MOD IF .\" odd\" THEN ;",""},
            {R"(1 IF ." true" ELSE ." false" THEN ;)","true"},
            {R"(0 IF ." true" ELSE ." false" THEN ;)","false"},
            {R"(1 IF 3 DUP * 9 / 9 * . ELSE 94 65 - . THEN ;)","9"},
            {R"(0 IF 3 DUP * 9 / 9 * . ELSE 94 65 - . THEN ;)","29"},
            {R"(50 DUP < IF 3 DUP * 9 / 9 * . ELSE 94 65 - . THEN ;)","29"},
            {"1 IF 1 IF 3 . THEN ; THEN ;","3"},
            {"1 IF 0 IF 3 . THEN ; THEN ;",""},
            {"0 IF 1 IF 3 . THEN ; THEN ;",""},
            {R"(1 IF 1 IF ." true" ELSE ." false" THEN ; THEN ;)","true"},
            {R"(1 IF 0 IF ." true" ELSE ." false" THEN ; THEN ;)","false"},
            {R"(0 IF 1 IF ." true" ELSE ." false" THEN ; THEN ;)",""},
            {R"(0 IF 0 IF ." true" ELSE ." false" THEN ; THEN ;)",""},
            {R"(0 IF 1 IF 3 9 < 81 * . ELSE 90 86 - DUP * . THEN ; THEN ;)",""},
            {R"(0 IF 1 IF 3 9 < 81 * . ELSE 90 86 - DUP * . THEN ; THEN ;)",""},
            {R"(1 IF 1 IF ." true" ELSE ." false1" THEN ; ELSE ." false2" THEN ;)","true"},
            {R"(1 IF 0 IF ." true" ELSE ." false1" THEN ; ELSE ." false2" THEN ;)","false1"},
            {R"(0 IF 1 IF ." true" ELSE ." false1" THEN ; ELSE ." false2" THEN ;)","false2"},
            {R"(0 IF 0 IF ." true" ELSE ." false1" THEN ; ELSE ." false2" THEN ;)","false2"},
            {"0 IF 1 IF 1 IF 1 IF 1 IF .\" true\" THEN ; THEN ; THEN ; THEN ; THEN ;",""},
            {"10 0 DO LOOP ;", ""},
            {"0 101 0 DO I + LOOP ; .", "5050"},
            {"3 2 1 101 0 DO ROT LOOP ; .", "2"},
            {"0 10 0 DO I 2 MOD DUP IF + ELSE DROP THEN ; LOOP ; .", "5"},
            {"0 10 0 DO I 1 + 0 DO I + LOOP ; LOOP ; .", "165"},
            {"0 10 0 DO I 1 + 0 DO I + LOOP ; I 2 * + LOOP ; .", "255"},
            {"10 0 DO I DUP 9 = IF .\" i = 9\" THEN ; LOOP ;", "i = 9"},
    };

    for (const auto& i : correctExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        interpreter.stringInterpret(i.first, output);
        ASSERT_EQ(output, i.second);
    }

    std::vector<std::string> wrongExpressionTestDataset {
            "IF",
            "THEN",
            "ELSE",
            ";",
            "IF 1 3 . THEN ;",
            "IF 3 . THEN ;",
            "1 IF 3 . THEN",
            "1 IF 3 . ;",
            "0 IF 3 . ELSE 4 . ;",
            "1 IF 1 IF 3 . THEN THEN ;",
            "1 IF 1 IF 3 . THEN ;",
            "1 IF 1 IF 3 . THEN ; ELSE 4 . ;",
            "1 IF ; 1 IF 3 . THEN ; ELSE 4 . THEN ;",
            "1 IF 1 IF 3 . THEN ELSE 4 . THEN ;",
            R"(0 IF 0 IF ." true" ELSE ." false1" THEN ; ELSE ." false2" THEN )",
            "DO",
            "LOOP",
            ";",
            "DO LOOP ;",
            "10 DO LOOP ;",
            "10 0 FOR LOOP ;",
            "10 0 DO ; LOOP ;",
            "10 0 DO ;",
            "10 0 DO LOOP",
            "10 0 LOOP ;",
            "0 10 0 DO I 1 + 0 DO I + LOOP LOOP ; .",
    };

    for (const auto& i : wrongExpressionTestDataset) {
        Interpreter interpreter(std::move(_reader), std::move(_writer));
        std::string output;
        ASSERT_THROW(interpreter.stringInterpret(i, output),
                     std::out_of_range);
    }
}