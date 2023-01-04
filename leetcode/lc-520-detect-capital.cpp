#include <gtest/gtest.h>

#include <vector>
using namespace std;

namespace {
class Solution {
public:
    virtual bool detectCapitalUse(string word) = 0;
};

class SolutionCppA : public Solution {
    bool detectCapitalUse(string word) {
        int len = word.length();
        if (len < 2) {
            return true;
        }
        int sec_info = isupper(word[1]);
        if (islower(word[0]) && sec_info) {
            return false;
        }
        for (int inx = 2; inx < len; ++ inx) {
            if (isupper(word[inx]) ^ sec_info) {
                return false;
            }
        }
        return true;
    }
};

}

static Solution *psolvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_520, Cpp_Example1) {
    for (Solution *psolver: psolvers) {
        EXPECT_EQ(true, psolver->detectCapitalUse("USA"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_520, Cpp_Example2) {
    for (Solution *psolver: psolvers) {
        EXPECT_EQ(false, psolver->detectCapitalUse("FlaG"))
                            << " by solution " << typeid(*psolver).name();
    }
}