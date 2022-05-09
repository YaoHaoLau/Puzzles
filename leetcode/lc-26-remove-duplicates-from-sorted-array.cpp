#include <gtest/gtest.h>

#include <string>
#include <stack>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int removeDuplicates(vector<int>& nums) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int removeDuplicates(vector<int>& nums) {
        return distance(nums.begin(), unique(nums.begin(), nums.end()));
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return len;
        }
        int cnt = 0;
        for (int inx = 1; inx < len; ++ inx) {
            if (nums[cnt] != nums[inx]) {
                nums[++ cnt] = nums[inx];
            }
        }
        return cnt + 1;
    }
};
}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
        , new SolutionCppB()
};

static bool checkOrder(vector<int> nums, int len) {
    if (len == 0) {
        return true;
    }
    int num = nums[0];
    for (int i = 1; i < len; ++ i) {
        if (num >= nums[i]) {
            return false;
        }
        num = nums[i];
    }
    return true;
}

TEST(LeetCode_26_remove_duplicates_from_sorted_array, Cpp_Example1) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        vector<int> nums({1,1,2});
        int len = psolver->removeDuplicates(nums);
        EXPECT_EQ(2, len) << " by solution " << typeid(*psolver).name();
        EXPECT_TRUE(checkOrder(nums, len));
    }
}

TEST(LeetCode_26_remove_duplicates_from_sorted_array, Cpp_Example2) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        vector<int> nums({0,0,1,1,1,2,2,3,3,4});
        int len = psolver->removeDuplicates(nums);
        EXPECT_EQ(5, len) << " by solution " << typeid(*psolver).name();
        EXPECT_TRUE(checkOrder(nums, len));
    }
}