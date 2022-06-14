#include <gtest/gtest.h>

#include <string>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int strStr(string haystack, string needle) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    int strStr(string haystack, string needle) {
        auto ret = haystack.find(needle);
        if (haystack.npos == ret) {
            return -1;
        }
        return ret;
    }
};

class SolutionCppB : public SolutionCpp {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }

        int m = static_cast<int>(haystack.length());
        int n = static_cast<int>(needle.length());
        if (m < n) {
            return -1;
        }

        for (int i = 0; i <= m - n; ++i) {
            if (haystack[i] != needle[0]) {
                continue;
            }
            int j = 0;
            while (j < n) {
                if (haystack[i + j] != needle[j]) {
                    break;
                }
                ++j;
            }
            if (j == n) {
                return i;
            }
        }
        return -1;
    }
};

class SolutionCppC : public SolutionCpp {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }

        int m = static_cast<int>(haystack.length());
        int n = static_cast<int>(needle.length());
        if (m < n) {
            return -1;
        }

        int i = 0;
        while (i <= m - n) {
            while (haystack[i] != needle[0]) {
                ++ i;
            }
            int j = 0, matched = 0;
            while (i < m && j < n && haystack[i] == needle[j]) {
                ++ i;
                ++ j;
                ++ matched;
            }
            if (matched == n) {
                return i - n;
            }
            i = i - matched + 1;
        }
        return -1;
    }
};

class SolutionCppD : public SolutionCpp {
    // partial match table
    vector<int> calcNext(const string &str) const {
        int len = static_cast<int>(str.size());
        vector<int> next(len, -1);
        for (int i = 1; i < len; ++ i) {
            int j = next[i - 1];
            while (j > -1 && str[i] != str[j + 1]) {
                j = next[j];
            }

            if (str[i] == str[j + 1]) {
                next[i] = j + 1;
            }
        }
        return next;
    }
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }

        int m = static_cast<int>(haystack.length());
        int n = static_cast<int>(needle.length());
        if (m < n) {
            return -1;
        }

        // KMP
        vector<int> next = calcNext(needle);
        int i = 0, j = 0;
        while (i < m) {
            if (haystack[i] == needle[j]) {
                ++ i, ++ j;
                if (j == n) {
                    return i - n;
                }
            } else {
                if (0 == j) {
                    ++ i;
                } else {
                    j = next[j - 1] + 1;
                }
            }
        }


        return -1;
    }
};


}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppD(),
        new SolutionCppC(),
        new SolutionCppB(),
        new SolutionCppA()
};

TEST(LeetCode_28_implement_strstr, Cpp_Example1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(2, psolver->strStr("hello", "ll"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_28_implement_strstr, Cpp_Example2) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(-1, psolver->strStr("aaaaa", "bba"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_28_implement_strstr, Cpp_ExampleX1) {
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(15, psolver->strStr("BBC ABCDAB ABCDABCDABDE", "ABCDABD"))
                            << " by solution " << typeid(*psolver).name();
    }
}