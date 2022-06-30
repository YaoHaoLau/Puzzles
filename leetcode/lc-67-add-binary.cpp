#include <gtest/gtest.h>

#include <string>
#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual string addBinary(string a, string b) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    string addBinary(string a, string b) {
        int len_a = a.length() - 1, len_b = b.length() - 1, carry = 0;
        string res;
        while (len_a > -1 && len_b > -1) {
            int sum = carry;
            if (a[len_a] != '0') {
                ++ sum;
            }
            if (b[len_b] != '0') {
                ++ sum;
            }
            carry = sum / 2;
            res.insert(res.begin(), (sum % 2) + '0');
            -- len_a;
            -- len_b;
        }

        while (len_a > -1) {
            int sum = carry;
            if (a[len_a] != '0') {
                ++ sum;
            }
            carry = sum / 2;
            res.insert(res.begin(), (sum % 2) + '0');
            -- len_a;
        }

        while (len_b > -1) {
            int sum = carry;
            if (b[len_b] != '0') {
                ++ sum;
            }
            carry = sum / 2;
            res.insert(res.begin(), (sum % 2) + '0');
            -- len_b;
        }

        if (carry) {
            res.insert(res.begin(), '1');
        }

        return res;
    }
};

class SolutionCppB : public SolutionCpp {
public:
    string addBinary(string a, string b) {
        int len_a = a.length() - 1, len_b = b.length() - 1, carry = 0;
        string res;
        while (len_a > -1 || len_b > -1) {
            int sum = carry;
            if (len_a > -1 && a[len_a] != '0') {
                ++ sum;
            }
            if (len_b > -1 && b[len_b] != '0') {
                ++ sum;
            }
            carry = sum / 2;
            res.insert(res.begin(), (sum % 2) + '0');
            -- len_a;
            -- len_b;
        }

        if (carry) {
            res.insert(res.begin(), '1');
        }

        return res;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_67_add_binary, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ("100", psolver->addBinary("11", "1"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_67_add_binary, Cpp_Example2) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ("10101", psolver->addBinary("1010", "1011"))
                            << " by solution " << typeid(*psolver).name();
    }
}
