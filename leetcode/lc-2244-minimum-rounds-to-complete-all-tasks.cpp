#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

namespace {
class Solution {
public:
    virtual int minimumRounds(vector<int>& tasks) = 0;
};

class SolutionCppA : public Solution {
    int calcStepNums(int lvl_ntasks) {
        int need = 0;
        while (lvl_ntasks > 6) {
            lvl_ntasks -= 3;
            ++ need;
        }

        if (lvl_ntasks > 3) {
            need += 2;
        } else if (lvl_ntasks > 1) {
            ++ need;
        } else if (lvl_ntasks == 1) {
            need = -1;
        }

        return need;
    }
public:
    int minimumRounds(vector<int>& tasks) {
        if (tasks.size() < 2) {
            return -1;
        }

        std::sort(tasks.begin(), tasks.end());
        
        int steps = 0;
        auto iter = tasks.begin();
        int curr = *iter, count = 0;
        while (iter != tasks.end()) {
            int val = *iter;
            if (val == curr) {
                ++ count;
            } else {
                int need = calcStepNums(count);
                if (need != -1) {
                    steps += need;
                } else {
                    steps = -1;
                    break;
                }
                count = 1;
                curr = *iter;
            }

            ++ iter;
        }

        int need = calcStepNums(count);
        if (need != -1) {
            steps += need;
        } else {
            steps = -1;
        }

        return steps;
    }
};

class SolutionCppB : public Solution {
    int calcStepNums(int lvl_ntasks) {
        if (lvl_ntasks != 1) {
            return (lvl_ntasks + 2) / 3;
        } else {
            return -1;
        }
    }
public:
    int minimumRounds(vector<int>& tasks) {
        if (tasks.size() < 2) {
            return -1;
        }

        std::sort(tasks.begin(), tasks.end());

        int steps = 0;
        auto iter = tasks.begin();
        int curr = *iter, count = 0;
        while (iter != tasks.end()) {
            int val = *iter;
            if (val == curr) {
                ++ count;
            } else {
                int need = calcStepNums(count);
                if (need != -1) {
                    steps += need;
                } else {
                    steps = -1;
                    break;
                }
                count = 1;
                curr = *iter;
            }

            ++ iter;
        }

        int need = calcStepNums(count);
        if (need != -1) {
            steps += need;
        } else {
            steps = -1;
        }

        return steps;
    }
};

class SolutionCppC : public Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        if (tasks.size() < 2) {
            return -1;
        }

        std::sort(tasks.begin(), tasks.end());

        int steps = 0;
        auto iter = tasks.begin();
        int curr = *iter, count = 0;
        while (iter != tasks.end()) {
            int val = *iter;
            if (val == curr) {
                ++ count;
            } else {
                if (count != 1) {
                    steps += (count + 2) / 3;
                } else {
                    return -1;
                }
                count = 1;
                curr = *iter;
            }

            ++ iter;
        }

        if (count != 1) {
            return steps + (count + 2) / 3;
        } else {
            return -1;
        }
    }
};

class SolutionCppD : public Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        if (tasks.size() < 2) {
            return -1;
        }

        unordered_map<int, int> lvl_cntr;
        for (auto iter = tasks.begin(); iter != tasks.end(); ++ iter) {
            lvl_cntr[*iter] ++;
        }

        int steps = 0;
        for (auto cntr : lvl_cntr) {
            if (cntr.second != 1) {
                steps += (cntr.second + 2) / 3;
            } else {
                steps = -1;
                break;
            }
        }
        return steps;
    }
};

}

static Solution *psolvers[] = {
    new SolutionCppA(),
    new SolutionCppB(),
    new SolutionCppC(),
};

TEST(LeetCode_2244, Cpp_Example1) {
    for (Solution *psolver : psolvers) {
        vector<int> tasks = {2,2,3,3,2,4,4,4,4,4};
        EXPECT_EQ(4, psolver->minimumRounds(tasks))
            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_2244, Cpp_Example2) {
    for (Solution *psolver : psolvers) {
        vector<int> tasks = {2,3,3};
        EXPECT_EQ(-1, psolver->minimumRounds(tasks))
                            << " by solution " << typeid(*psolver).name();
    }
}
