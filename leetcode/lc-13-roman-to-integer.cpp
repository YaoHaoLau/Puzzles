#include <gtest/gtest.h>

#include <string>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int romanToInt(string s) = 0;
};

static inline int cvtRom2Int(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
    return 0;
}

class SolutionCppA : public SolutionCpp {
public:
    int romanToInt(string s) {
        int num = 0;
        if (s.empty()) {
            return num;
        }

        int s_len = s.length();
        int cur_val = cvtRom2Int(s[0]);
        for (int inx = 1; inx < s_len; ++ inx) {
            int nxt_val = cvtRom2Int(s[inx]);
            if (nxt_val > cur_val) {
                num -= cur_val;
            } else {
                num += cur_val;
            }
            cur_val = nxt_val;
        }

        num += cur_val;
        return num;
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int romanToInt(string s) {
        int num = 0;
        if (s.empty()) {
            return num;
        }
        int pre_val = 0;
        for (int i = s.length() - 1; i >= 0; -- i) {
            int cur_val = cvtRom2Int(s[i]);
            if (cur_val < pre_val) {
                num -= cur_val;
            } else {
                num += cur_val;
            }
            pre_val = cur_val;
        }

        return num;
    }
};

class SolutionCppC : public SolutionCpp {
public:
    int romanToInt(string s) {
        int num = 0;
        if (s.empty()) {
            return num;
        }
        int pre_val = 0;
        for (auto iter = s.rbegin(); iter != s.rend(); iter ++) {
            int cur_val = cvtRom2Int(*iter);
            if (cur_val < pre_val) {
                num -= cur_val;
            } else {
                num += cur_val;
            }
            pre_val = cur_val;
        }

        return num;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
        , new SolutionCppB()
        , new SolutionCppC()
};

TEST(LeetCode_13_roman_to_integer, Cpp_Example1) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(3, psolver->romanToInt("III"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_13_roman_to_integer, Cpp_Example2) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(58, psolver->romanToInt("LVIII"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_13_roman_to_integer, Cpp_Example3) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(1994, psolver->romanToInt("MCMXCIV"))
                            << " by solution " << typeid(*psolver).name();
    }
}
