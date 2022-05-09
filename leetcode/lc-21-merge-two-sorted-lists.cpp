#include <gtest/gtest.h>

#include "list_node.h"

using namespace std;

namespace {
class SolutionCpp {
public:
    virtual ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) = 0;
};

class SolutionCppA : public SolutionCpp {
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }
        if (!list2) {
            return list1;
        }
        ListNode head_node(0);
        ListNode *p1 = list1, *p2 = list2, *q = &head_node;
        while (p1 && p2) {
            if (p1->val >= p2->val) {
                q->next = p2;
                p2 = p2->next;
            } else {
                q->next = p1;
                p1 = p1->next;
            }
            q = q->next;
        }
        if (p1) {
            q->next = p1;
        }
        if (p2) {
            q->next = p2;
        }
        return head_node.next;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_21_merge_two_sorted_lists, Cpp_Example1) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        ListNode *plist1 = createList(std::vector<int>({1, 2, 4}));
        ListNode *plist2 = createList(std::vector<int>({1, 3, 4}));
        ListNode *pexpect = createList(std::vector<int>({1, 1, 2, 3, 4, 4}));
        ListNode *pactual = psolver->mergeTwoLists(plist1, plist2);
        EXPECT_EQ(true, compareLists(pexpect, pactual))
                            << " by solution " << typeid(*psolver).name();
        deleteList(pexpect);
        deleteList(pactual);
    }
}

TEST(LeetCode_21_merge_two_sorted_lists, Cpp_Example2) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        ListNode *plist1 = createList(std::vector<int>({}));
        ListNode *plist2 = createList(std::vector<int>({}));
        ListNode *pexpect = createList(std::vector<int>({}));
        ListNode *pactual = psolver->mergeTwoLists(plist1, plist2);
        EXPECT_EQ(true, compareLists(pexpect, pactual))
                            << " by solution " << typeid(*psolver).name();
        deleteList(pexpect);
        deleteList(pactual);
    }
}

TEST(LeetCode_21_merge_two_sorted_lists, Cpp_Example3) {
    for (SolutionCpp *psolver : pcpp_solvers) {
        ListNode *plist1 = createList(std::vector<int>({}));
        ListNode *plist2 = createList(std::vector<int>({0}));
        ListNode *pexpect = createList(std::vector<int>({0}));
        ListNode *pactual = psolver->mergeTwoLists(plist1, plist2);
        EXPECT_EQ(true, compareLists(pexpect, pactual))
                            << " by solution " << typeid(*psolver).name();
        deleteList(pexpect);
        deleteList(pactual);
    }
}
