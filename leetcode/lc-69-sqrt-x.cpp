#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int mySqrt(int x) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int mySqrt(int x) {
        return sqrt(x);
    }
};

/**
 * f(x) = m - x^2 = 0
 * f'(x) = -2x
 * x_np1 = x_n - f(x_n) / f'(x_n)
 *       = x_n - (m - x_n^2) / (-2x_n)
 *       = (m + x_n^2) / (2x_n)
 *       = 0.5 * (m / x_n + x_n)
 * x_n = x_np1
 */
class SolutionCppB : public SolutionCpp {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }
        double x_np1 = x / 2.f, x_n;
        do {
            x_n = x_np1;
            x_np1 = 0.5f * ((double)x / x_n + x_n);
        } while (std::abs(x_np1 - x_n) > 1e-2);
        return static_cast<int>(x_np1);
    }
};

class SolutionCppC : public SolutionCpp {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }

        int low = 1, high = 1 + (x >> 1);
        while (low <= high) {
            int64_t mid = low + ((high - low) >> 1);
            int64_t res = mid * mid;
            if (res == x) {
                return mid;
            } else if (res < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return high;
    }
};

/**
 * From Doom fast-sqrt
 */
class SolutionCppD : public SolutionCpp {
public:
    int mySqrt(int x) {
        double y = x;
        int64_t i = 0x5fe6eb50c7b537a9;
        y = *(double*)&(i = i-(*(int64_t*)&y)/2);
        y = y * (3 - x * y * y) * 0.5;
        y = y * (3 - x * y * y) * 0.5;
        i = x * y + 1;
        return i - (i * i > x);
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppD(),
        new SolutionCppC(),
        new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_69_sqrt_x, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(2, psolver->mySqrt(4))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_69_sqrt_x, Cpp_Example2) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(2, psolver->mySqrt(8))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_69_sqrt_x, Cpp_Example3) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(255, psolver->mySqrt(65535))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_69_sqrt_x, Cpp_Example4) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(0, psolver->mySqrt(0))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_69_sqrt_x, Cpp_Example5) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(46339, psolver->mySqrt(2147395599))
                            << " by solution " << typeid(*psolver).name();
    }
}
