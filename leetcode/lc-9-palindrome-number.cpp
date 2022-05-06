#include <gtest/gtest.h>

#include <string>
using namespace std;

namespace {

class SolutionCpp {
public:
    virtual bool isPalindrome(int x) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        }
        string x_str = to_string(x);
        int linx = 0, rinx = x_str.length() - 1;
        while (linx < rinx) {
            if (x_str[linx] != x_str[rinx]) {
                return false;
            }
            linx ++;
            rinx --;
        }
        return true;
    }
};

class SolutionCppB : public SolutionCpp {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        }
        string x_str = to_string(x);
        string x_rev(x_str.rbegin(), x_str.rend());
        return x_str == x_rev;
    }
};


class SolutionCppC : public SolutionCpp {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        }

        long long rev_x = 0;
        int ori_x = x;
        while (x) {
            rev_x = rev_x * 10 + (x % 10);
            x /= 10;
        }
        return ori_x == rev_x;
    }
};

class SolutionCppD : public SolutionCpp {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        } else if (0 == x % 10) {
            return false;
        }

        int div = 1;
        while (x / div >= 10) {
            div *= 10;
        }
        while (x) {
            int m = x / div;
            int n = x % 10;
            if (m != n) {
                return false;
            }
            x = (x % div) / 10;
            div /= 100;
        }
        return true;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
        , new SolutionCppB()
        , new SolutionCppC()
        , new SolutionCppD()
};

TEST(LeetCode_9_palindrome_number, Cpp_Example1) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(true, psolver->isPalindrome(121))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_9_palindrome_number, Cpp_Example2) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(false, psolver->isPalindrome(-121))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_9_palindrome_number, Cpp_Example3) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(false, psolver->isPalindrome(10))
                            << " by solution " << typeid(*psolver).name();
    }
}
