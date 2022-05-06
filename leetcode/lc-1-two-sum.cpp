#include "utils.h"

#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>
using namespace std;

namespace {

typedef int expect_t;
typedef int index_t;

class SolutionCpp {
public:
    virtual vector<int> twoSum(vector<int>& nums, int target) = 0;
};

/**
 * @brief Create a map to map numbers with index
 *  if expect number not found in the map,
 *    add current number with index into map
 *  otherwise
 *    return current index with expect number's index
 */
class SolutionCppA : public SolutionCpp {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> inx_pair(2);
        unordered_map<expect_t, index_t> exp2inx;
        const int num_len = nums.size();
        for (int inx = 0; inx < num_len; ++ inx) {
            expect_t num_exp = target - nums[inx];
            if (exp2inx.count(num_exp)) {
                inx_pair[0] = exp2inx[num_exp];
                inx_pair[1] = inx;
                break;
            } else {
                exp2inx.insert(pair<expect_t, index_t>(nums[inx], inx));
            }
        }
        return inx_pair;
    }
};

/**
 * @brief Sort input vector, this can speedup two number searching
 *        then find corresponding two number's index with binary search
 */
class SolutionCppB : public SolutionCpp {
    int binary_search(const vector<int> &nums, int beg, int end, int exp) {
        while (beg <= end) {
            int mid = (beg + end) >> 1;
            if (nums[mid] < exp) {
                beg = mid + 1;
            } else if (nums[mid] > exp) {
                end = mid - 1;
            } else {
                return mid;
            }
        }
        return 0;
    }
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> inx_pair(2);
        vector<int> nums_sorted = nums;
        std::sort(nums_sorted.begin(), nums_sorted.end());

        const int num_len = nums_sorted.size();

        int linx, rinx;
        for (linx = 0; linx < num_len - 1; ++linx) {
            rinx = binary_search(nums_sorted, linx + 1, num_len - 1, target - nums_sorted[linx]);
            if (rinx != 0) {
                linx = nums_sorted[linx];
                rinx = nums_sorted[rinx];
                break;
            }
        }

        for (int i = 0; i < num_len; ++i) {
            if (linx == nums[i]) {
                inx_pair[0] = i;
                break;
            }
        }
        for (int i = 0; i < num_len; ++i) {
            if (rinx == nums[i] && inx_pair[0] != i) {
                inx_pair[1] = i;
                break;
            }
        }

        return inx_pair;
    }
};

class SolutionCppC : public SolutionCpp {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> inx_pair(2);
        vector<int> nums_sorted = nums;
        std::sort(nums_sorted.begin(), nums_sorted.end());

        const int num_len = nums_sorted.size();

        int linx = 0, rinx = num_len - 1;
        while (linx < rinx) {
            int cur_sum = nums_sorted[linx] + nums_sorted[rinx];
            if (cur_sum > target) {
                rinx --;
            } else if (cur_sum < target) {
                linx ++;
            } else {
                linx = nums_sorted[linx];
                rinx = nums_sorted[rinx];
                break;
            }
        }

        for (int i = 0; i < num_len; ++i) {
            if (linx == nums[i]) {
                inx_pair[0] = i;
                break;
            }
        }
        for (int i = 0; i < num_len; ++i) {
            if (rinx == nums[i] && inx_pair[0] != i) {
                inx_pair[1] = i;
                break;
            }
        }

        return inx_pair;
    }
};

} // namespace

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA(),
        new SolutionCppB(),
        new SolutionCppC()
};

TEST(LeetCode_1_two_sum, Cpp_Example1) {
    const int src[] = {2, 2, 15, 7};
    const int dst[] = {0, 3};
    int target = 9;

    vector<int> nums = convert_arr2vec(src, int);
    vector<int> expect = convert_arr2vec(dst, int);
    vector<int> acutal;

    for (SolutionCpp *psolver : pcpp_solvers) {
        acutal = psolver->twoSum(nums, target);
        EXPECT_EQ(expect, acutal) << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_1_two_sum, Cpp_Example2) {
    const int src[] = {3, 2, 4};
    const int dst[] = {1, 2};
    int target = 6;

    vector<int> nums = convert_arr2vec(src, int);
    vector<int> expect = convert_arr2vec(dst, int);
    vector<int> acutal;

    for (SolutionCpp *psolver : pcpp_solvers) {
        acutal = psolver->twoSum(nums, target);
        EXPECT_EQ(expect, acutal) << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_1_two_sum, Cpp_Example3) {
    const int src[] = {3, 3};
    const int dst[] = {0, 1};
    int target = 6;

    vector<int> nums = convert_arr2vec(src, int);
    vector<int> expect = convert_arr2vec(dst, int);
    vector<int> acutal;

    for (SolutionCpp *psolver : pcpp_solvers) {
        acutal = psolver->twoSum(nums, target);
        EXPECT_EQ(expect, acutal) << " by solution " << typeid(*psolver).name();
    }
}

