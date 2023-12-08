#ifndef LAB2_UTILITIES_H
#define LAB2_UTILITIES_H

#include <stack>
#include <string>

class Utilities {
public:
    static bool checkTheValue(std::stack<int> &stack);
    static bool checkTwoOperands(std::stack<int> &stack);
    static bool checkThreeOperands(std::stack<int> &stack);

    static bool checkOverflowAdd(int a, int b);
    static bool checkUnderflowAdd(int a, int b);
    static bool checkOverflowSub(int a, int b);
    static bool checkUnderflowSub(int a, int b);
    static bool checkOverflowMul(int a, int b);
    static bool checkUnderflowMul(int a, int b);
    static bool checkZeroDivision(int b);

    static bool isNumber(const std::string& str);
    static void restoreStack(std::stack<int> &stack);
};

#endif //LAB2_UTILITIES_H
