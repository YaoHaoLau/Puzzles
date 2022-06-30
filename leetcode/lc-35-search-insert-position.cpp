#include <gtest/gtest.h>

#include <string>
#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int searchInsert(vector<int>& nums, int target) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int searchInsert(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] >= target) {
                return i;
            }
        }
        return nums.size();
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (target > nums.back()) {
            return nums.size();
        }
        int linx = 0, rinx = nums.size() - 1;
        while (linx < rinx) {
            int minx = (linx + rinx) >> 1;
            if (target > nums[minx]) {
                linx = minx + 1;
            } else if (target < nums[minx]) {
                rinx = minx;
            } else {
                return minx;
            }
        }
        return rinx;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_35_search_insert_position, Cpp_Example1) {
    vector<int> nums = {1,3,5,6};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(2, psolver->searchInsert(nums, 5))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_35_search_insert_position, Cpp_Example2) {
    vector<int> nums = {1,3,5,6};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(1, psolver->searchInsert(nums, 2))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_35_search_insert_position, Cpp_Example3) {
    vector<int> nums = {1,3,5,6};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(4, psolver->searchInsert(nums, 7))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_35_search_insert_position, Cpp_Example4) {
    vector<int> nums = {1,3,5,6};
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(0, psolver->searchInsert(nums, 0))
                            << " by solution " << typeid(*psolver).name();
    }
}
