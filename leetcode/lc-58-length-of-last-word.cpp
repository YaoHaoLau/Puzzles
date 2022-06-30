#include <gtest/gtest.h>

#include <string>
#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int lengthOfLastWord(string s) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int lengthOfLastWord(string str) {
        int rinx = str.length() - 1;
        while (rinx > -1 && str[rinx] == ' ') {
            -- rinx;
        }
        int len = 0;
        while (rinx > -1 && str[rinx] != ' ') {
            -- rinx;
            ++ len;
        }
        return len;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        // new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_58_length_of_last_word, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(5, psolver->lengthOfLastWord("Hello World"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_58_length_of_last_word, Cpp_Example2) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(4, psolver->lengthOfLastWord("   fly me   to   the moon  "))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_58_length_of_last_word, Cpp_Example3) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(6, psolver->lengthOfLastWord("luffy is still joyboy"))
                            << " by solution " << typeid(*psolver).name();
    }
}
