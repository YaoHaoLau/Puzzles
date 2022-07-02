#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int climbStairs(int n) = 0;
};

/**
 * f(n) = f(n-1) + f(n-2)
 * f(2) = 2
 * f(1) = 1
 */
class SolutionCppA : public SolutionCpp {
public:
    int climbStairs(int n) {
        if (n < 4) {
            return n;
        }
        int x1, x2 = 2, x = 3;
        for (int i = 3; i < n; ++ i) {
            x1 = x2;
            x2 = x;
            x = x1 + x2;
        }
        return x;
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int climbStairs(int n) {
        static int lut[] = {
            1,         2,          3,         5,         8,         13,        21,
            34,        55,         89,        144,       233,       377,       610,
            987,       1597,       2584,      4181,      6765,      10946,     17711,
            28657,     46368,      75025,     121393,    196418,    317811,    514229,
            832040,    1346269,    2178309,   3524578,   5702887,   9227465,   14930352,
            24157817,  39088169,   63245986,  102334155, 165580141, 267914296, 433494437,
            701408733, 1134903170, 1836311903
        };
        return lut[n - 1];
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_70_climbing_stairs, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(2, psolver->climbStairs(2))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_70_climbing_stairs, Cpp_All_Cases) {
    int lut[] = {
        1,         2,          3,         5,         8,         13,        21,
        34,        55,         89,        144,       233,       377,       610,
        987,       1597,       2584,      4181,      6765,      10946,     17711,
        28657,     46368,      75025,     121393,    196418,    317811,    514229,
        832040,    1346269,    2178309,   3524578,   5702887,   9227465,   14930352,
        24157817,  39088169,   63245986,  102334155, 165580141, 267914296, 433494437,
        701408733, 1134903170, 1836311903
    };
    for (int i = 1; i <= 45; ++i) {
        for (SolutionCpp *psolver: pcpp_solvers) {
            EXPECT_EQ(lut[i - 1], psolver->climbStairs(i))
                                << " by solution " << typeid(*psolver).name();
        }
    }
}
