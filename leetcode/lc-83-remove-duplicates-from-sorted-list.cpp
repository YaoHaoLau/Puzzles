#include <gtest/gtest.h>
#include "list_node.h"

#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace {

class SolutionCpp {
public:
    virtual ListNode* deleteDuplicates(ListNode* head) = 0;
};

class SolutionCppA : public SolutionCpp {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode *curr = head;
        while (curr && curr->next) {
            if (curr->val == curr->next->val) {
                ListNode *temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
};

}

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA()
};

TEST(LeetCode_83_remove_duplicates_from_sorted_list, Cpp_Example1) {
    vector<int> vec_src = {1,1,2};
    vector<int> vec_res = {1,2};
    ListNode *plist_src = createList(vec_src);
    ListNode *plist_res = createList(vec_res);
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_TRUE(compareLists(plist_res, psolver->deleteDuplicates(plist_src)))
                            << " by solution " << typeid(*psolver).name();
    }
    deleteList(plist_src);
    deleteList(plist_res);
}

TEST(LeetCode_83_remove_duplicates_from_sorted_list, Cpp_Example2) {
    vector<int> vec_src = {1,1,2,3,3};
    vector<int> vec_res = {1,2,3};
    ListNode *plist_src = createList(vec_src);
    ListNode *plist_res = createList(vec_res);
    for (SolutionCpp *psolver: pcpp_solvers) {
        EXPECT_TRUE(compareLists(plist_res, psolver->deleteDuplicates(plist_src)))
                            << " by solution " << typeid(*psolver).name();
    }
    deleteList(plist_src);
    deleteList(plist_res);
}
