#include <gtest/gtest.h>
#include "list_node.h"

#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace {

class SolutionCpp {
public:
    virtual void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n < 1) {
            return;
        }
        --m, --n;
        int inx = m + n + 1;
        while (m > -1 && n > -1) {
            nums1[inx] = nums1[m] > nums2[n] ? nums1[m --] : nums2[n --];
            -- inx;
        }
        while (n > -1) {
            nums1[inx] = nums2[n --];
            -- inx;
        }
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_88_merge_sorted_array, Cpp_Example1) {
    vector<int> vec_nums1 = {1,2,3,0,0,0};
    vector<int> vec_nums2 = {2,5,6};
    vector<int> vec_res = {1,2,2,3,5,6};
    for (SolutionCpp *psolver: pcpp_solvers) {
        psolver->merge(vec_nums1, 3, vec_nums2, 3);
        EXPECT_EQ(vec_res, vec_nums1)
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_88_merge_sorted_array, Cpp_Example2) {
    vector<int> vec_nums1 = {1};
    vector<int> vec_nums2 = {};
    vector<int> vec_res = {1};
    for (SolutionCpp *psolver: pcpp_solvers) {
        psolver->merge(vec_nums1, 1, vec_nums2, 0);
        EXPECT_EQ(vec_res, vec_nums1)
                            << " by solution " << typeid(*psolver).name();
    }
}
