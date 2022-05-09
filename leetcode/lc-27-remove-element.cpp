#include <gtest/gtest.h>
#include <string>
#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int removeElement(vector<int>& nums, int val) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int removeElement(vector<int>& nums, int val) {
        nums.erase(remove(nums.begin(), nums.end(), val), nums.end());
        return nums.size();
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int cnt = 0;
        for (int inx = 0; inx < len; ++ inx) {
            if (val != nums[inx]) {
                nums[cnt ++] = nums[inx];
            }
        }
        return cnt;
    }
};

class SolutionCppC : public SolutionCpp {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int inx = 0;
        while (inx < len) {
            if (val == nums[inx]) {
                nums[inx] = nums[len - 1];
                -- len;
            } else {
                ++ inx;
            }
        }
        return len;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
        , new SolutionCppB()
        , new SolutionCppC()
};

TEST(LeetCode_27_remove_element, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        vector<int> nums({3, 2, 2, 3});
        vector<int> expn({2, 2});
        int len = psolver->removeElement(nums, 3);
        EXPECT_EQ(2, len) << " by solution " << typeid(*psolver).name();
        EXPECT_EQ(expn, vector<int>(nums.begin(), nums.begin() + len));
    }
}

TEST(LeetCode_27_remove_element, Cpp_Example2) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        vector<int> nums({0,1,2,2,3,0,4,2});
        vector<int> expn({0,1,4,0,3});
        int len = psolver->removeElement(nums, 2);
        EXPECT_EQ(5, len) << " by solution " << typeid(*psolver).name();
        sort(nums.begin(), nums.begin() + len);
        sort(expn.begin(), expn.end());
        EXPECT_EQ(expn, vector<int>(nums.begin(), nums.begin() + len));
    }
}
