#include <gtest/gtest.h>

#include <string>
#include <stack>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual bool isValid(string s) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    bool isValid(string s) {
        stack<char> par_stack;
        for (auto c : s) {
            switch (c) {
                case '{':
                    par_stack.push('}');
                    break;
                case '[':
                    par_stack.push(']');
                    break;
                case '(':
                    par_stack.push(')');
                    break;
                case '}':
                case ']':
                case ')':
                    if (!par_stack.empty() && par_stack.top() != c) {
                        return false;
                    }
                    par_stack.pop();
                    break;
            }
        }
        return true;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_20_valid_parentheses, Cpp_Example1) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(true, psolver->isValid("()"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_20_valid_parentheses, Cpp_Example2) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(true, psolver->isValid("()[]{}"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_20_valid_parentheses, Cpp_Example3) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(false, psolver->isValid("(]"))
                            << " by solution " << typeid(*psolver).name();
    }
}
