#include <gtest/gtest.h>

#include <string>
#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual vector<int> plusOne(vector<int>& digits) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (auto iter = digits.rbegin(); iter != digits.rend(); ++iter) {
            int num = *iter + carry;
            *iter = num % 10;
            carry = num / 10;
            if (0 == carry) {
                break;
            }
        }
        if (carry) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        // new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_66_plus_one, Cpp_Example1) {
    vector<int> nums = {1,2,3};
    vector<int> exp_res = {1,2,4};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(exp_res, psolver->plusOne(nums))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_66_plus_one, Cpp_Example2) {
    vector<int> nums = {4,3,2,1};
    vector<int> exp_res = {4,3,2,2};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(exp_res, psolver->plusOne(nums))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_66_plus_one, Cpp_Example3) {
    vector<int> nums = {9};
    vector<int> exp_res = {1,0};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(exp_res, psolver->plusOne(nums))
                            << " by solution " << typeid(*psolver).name();
    }
}
