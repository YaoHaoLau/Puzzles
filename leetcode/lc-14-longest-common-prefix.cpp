#include <gtest/gtest.h>

#include <string>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual string longestCommonPrefix(vector<string>& strs) = 0;
};

/**
 * @brief Find shortest string first, use it as prefix, then compare one-by-one,
 *   decrease the prefix's length
 */
class SolutionCppA : public SolutionCpp {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int num_strs = strs.size();
        if (0 == num_strs) {
            return "";
        }

        int min_len = numeric_limits<int>::max(), min_inx = 0;
        for (int inx = 0; inx < num_strs; ++ inx) {
            if (strs[inx].length() < min_len) {
                min_len = strs[inx].length();
                min_inx = inx;
            }
        }

        string prefix = strs[min_inx];

        for (string str : strs) {
            if (0 == min_len) {
                break;
            }
            if (str.compare(0, min_len, prefix)) {
                int sub_len = 0;
                for (int inx = 0; inx < min_len - 1; ++ inx) {
                    if (str[inx] != prefix[inx]) {
                        sub_len = inx;
                        break;
                    }
                }
                min_len = sub_len;
            }
        }

        return prefix.substr(0, min_len);
    }
};

class SolutionCppB : public SolutionCpp {
    string compareTwoStrs(string str1, string str2) {
        int min_len = min(str1.length(), str2.length());
        if (!str1.compare(0, min_len, str2)) {
            return str1.substr(0, min_len);
        } else {
            for (int i = 0; i < min_len; ++ i) {
                if (str1[i] != str2[i]) {
                    return str1.substr(0, i);
                }
            }
            return "";
        }
    }

    string compareRangeStrs(vector<string>& strs, int beg, int end) {
        if (beg == end) {
            return strs[beg];
        } else if (beg + 1 == end) {
            return compareTwoStrs(strs[beg], strs[end]);
        } else {
            int mid = (beg + end) >> 1;
            if (mid > beg &&  mid < end) {
                return compareTwoStrs(compareRangeStrs(strs, beg, mid),
                                      compareRangeStrs(strs, mid + 1, end));
            } else if (mid >= beg) {
                return compareRangeStrs(strs, beg, mid);
            } else {
                return compareRangeStrs(strs, mid, end);
            }
        }
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }

        return compareRangeStrs(strs, 0, strs.size() - 1);
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
    new SolutionCppA()
    , new SolutionCppB()
};

TEST(LeetCode_14_longest_common_prefix, Cpp_Example1) {
    vector<string> strs = {
            "flower", "flow", "flight"
    };
    string prefix = "fl";
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(prefix, psolver->longestCommonPrefix(strs))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_14_longest_common_prefix, Cpp_Example2) {
    vector<string> strs = {
            "dog", "racecar", "car"
    };
    string prefix = "";
    for (SolutionCpp *psolver : pcpp_solvers) {
        EXPECT_EQ(prefix, psolver->longestCommonPrefix(strs))
                            << " by solution " << typeid(*psolver).name();
    }
}
