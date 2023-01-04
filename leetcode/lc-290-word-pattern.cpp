#include <gtest/gtest.h>

#include <unordered_map>
using namespace std;

namespace {
class Solution {
public:
    virtual bool wordPattern(string pattern, string s) = 0;
};

class SolutionCppA : public Solution {
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> ch2wd;
        unordered_map<string, char> wd2ch;

        str += ' ';

        int pos = -1;
        for (char ch : pattern) {
            int last = pos + 1;
            pos = str.find(' ', last);
            if (string::npos == pos) {
                return false;
            }

            string word = str.substr(last, pos - last);
            if (word.empty()) {
                return false;
            }

            if (ch2wd.find(ch) != ch2wd.end()) {
                if (ch2wd.at(ch).compare(word) != 0) {
                    return false;
                }
            } else {
                ch2wd.insert(std::pair<char, string>(ch, word));
            }

            if (wd2ch.find(word) != wd2ch.end()) {
                if (wd2ch.at(word) != ch) {
                    return false;
                }
            } else {
                wd2ch.insert(std::pair<string, char>(word, ch));
            }
        }

        if (pos != string::npos) {
            if (string::npos != str.find(' ', pos + 1)) {
                return false;
            }
        }
        return true;
    }
};

class SolutionCppB : public Solution {
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> ch2wd;
        unordered_map<string, char> wd2ch;

        str += ' ';

        int pos = -1;
        for (char ch : pattern) {
            int last = pos + 1;
            pos = str.find(' ', last);
            if (string::npos == pos) {
                return false;
            }

            string word = str.substr(last, pos - last);
            if (word.empty()) {
                return false;
            }

            auto fwd = ch2wd.find(ch);
            auto fch = wd2ch.find(word);

            if (fwd == ch2wd.end() && fch == wd2ch.end()) {
                ch2wd[ch] = word;
                wd2ch[word] = ch;
            } else {
                if (fwd == ch2wd.end() || fwd->second != word
                    || fch == wd2ch.end() || fch->second != ch) {
                    return false;
                }
            }
        }

        if (pos != string::npos) {
            if (string::npos != str.find(' ', pos + 1)) {
                return false;
            }
        }
        return true;
    }
};

}

static Solution *psolvers[] = {
        new SolutionCppA(),
        new SolutionCppB(),
};

TEST(LeetCode_290, Cpp_Example1) {
    for (Solution *psolver: psolvers) {
        EXPECT_TRUE(psolver->wordPattern("abba", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example2) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("aba", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example3) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("abbba", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example4) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("acba", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example5) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("acba", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example6) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("aba", "dog cat dog cat"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example7) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("abba", "dog cat cat fish"))
                            << " by solution " << typeid(*psolver).name();
    }
}

TEST(LeetCode_290, Cpp_Example8) {
    for (Solution *psolver: psolvers) {
        EXPECT_FALSE(psolver->wordPattern("aaaa", "dog cat cat dog"))
                            << " by solution " << typeid(*psolver).name();
    }
}

