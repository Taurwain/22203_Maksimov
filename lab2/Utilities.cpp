#include <climits>
#include "Utilities.h"

bool Utilities::checkTheValue(std::stack<int> &stack) {
    return (!stack.empty());
}

bool Utilities::checkTwoOperands(std::stack<int> &stack) {
    return (stack.size() >= 2);
}

bool Utilities::checkThreeOperands(std::stack<int> &stack) {
    return (stack.size() >= 3);
}

bool Utilities::checkOverflowAdd(int a, int b) {
    if (b > 0) {
        return (a > INT_MAX - b);
    }
    return false;
}

bool Utilities::checkUnderflowAdd(int a, int b) {
    if (b < 0) {
        return (a < INT_MIN - b);
    }
    return false;
}

bool Utilities::checkOverflowSub(int a, int b) {
    if (b < 0) {
        return (a > INT_MAX + b);
    }
    return false;
}

bool Utilities::checkUnderflowSub(int a, int b) {
    if (b > 0) {
        return (a < INT_MIN + b);
    }
    return false;
}

bool Utilities::checkOverflowMul(int a, int b) {
    return (abs(a) > INT_MAX / abs(b));
}

bool Utilities::checkUnderflowMul(int a, int b) {
    return (abs(a) * (-1) < INT_MIN / abs(b));
}

bool Utilities::checkZeroDivision(int b) {
    return (b == 0);
}

bool Utilities::isNumber(const std::string& str) {
    try {
        std::stoi(str);
        return true;
    } catch (const std::exception &) {
        return false;
    }
}

void Utilities::restoreStack(std::stack<int> &stack) {
    stack = std::stack<int>();
}