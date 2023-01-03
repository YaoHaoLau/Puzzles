#include <gtest/gtest.h>

#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual int minDeletionSize(const vector<string>& strs) {
        return 0;
    };
};

class SolutionCppA : public SolutionCpp {
    int minDeletionSize(const vector<string>& strs) override {
        int ncols = strs[0].length();
        int nrows = strs.size() - 1;
        int res = 0;
        for (int cinx = 0; cinx < ncols; ++ cinx) {
            for (int rinx = 0; rinx < nrows; ++ rinx) {
                if (strs[rinx][cinx] > strs[rinx + 1][cinx]) {
                    ++ res;
                    break;
                }
            }
        }
        return res;
    };
};

}
static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_944, Cpp_Example1) {
    vector<string> vec = {
            "abc",
            "bce",
            "cae"
    };
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(1, psolver->minDeletionSize(vec))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_944, Cpp_Example2) {
    vector<string> vec = {
            "a","b"
    };
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(0, psolver->minDeletionSize(vec))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_944, Cpp_Example3) {
    vector<string> vec = {
            "zyx",
            "wvu",
            "tsr"
    };
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_EQ(3, psolver->minDeletionSize(vec))
                            << " by solution " << typeid(*psolver).name();
    }
}
