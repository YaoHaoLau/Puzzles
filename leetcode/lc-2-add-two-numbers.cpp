#include <gtest/gtest.h>
#include "list_node.h"

#include <vector>
using namespace std;

namespace {
class SolutionCpp {
public:
    virtual ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return NULL;
    }
};

class SolutionCppA : public SolutionCpp {
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) override {
        int carry = 0;
        ListNode *phead = l1, *pcarry = l2, *prev;
        while (l1 && l2) {
            int sval = (l1->val + l2->val + carry);
            l1->val = sval % 10;
            carry = sval >= 10;

            if (!l1->next) {
                prev = l1;
            }
            l1 = l1->next;
            l2 = l2->next;
        }

        if (l2) {
            l1 = l2;
            prev->next = l2;
        }

        while (l1) {
            int sval = l1->val + carry;
            l1->val = sval % 10;
            carry = sval >= 10;

            if (!l1->next) {
                prev = l1;
            }
            l1 = l1->next;
        }

        if (carry) {
            prev->next = pcarry;
            pcarry->val = 1;
            pcarry->next = NULL;
        }

        return phead;
    }
};

class SolutionCppB : public SolutionCpp {
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) override {
        int carry = 0;
        ListNode *phead = l1, *pcarry = l2, *prev;
        while (l1 && l2) {
            int sval = (l1->val + l2->val + carry);
            l1->val = sval % 10;
            carry = sval >= 10;

            prev = l1;
            l1 = l1->next;
            l2 = l2->next;
        }

        if (l2) {
            l1 = l2;
            prev->next = l2;
        }

        while (l1) {
            int sval = l1->val + carry;
            l1->val = sval % 10;
            carry = sval >= 10;

            prev = l1;
            l1 = l1->next;
        }

        if (carry) {
            prev->next = pcarry;
            pcarry->val = 1;
            pcarry->next = NULL;
        }

        return phead;
    }
};


}

class SolutionCppC : public SolutionCpp {
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) override {
        int carry = 0;
        ListNode res(-1);

        ListNode *prev = &res;
        while (l1 && l2) {
            int sum = l1->val + l2->val + carry;
            l1 = l1->next;
            l2 = l2->next;

            carry = sum > 9;
            sum %= 10;
            prev->next = new ListNode(sum);
            prev = prev->next;
        }

        if (l2) {
            l1 = l2;
            prev->next = l2;
        }

        while (l1) {
            int sum = l1->val + carry;
            l1 = l1->next;
            carry = sum > 9;
            sum %= 10;
            prev->next = new ListNode(sum);
            prev = prev->next;
        }

        if (carry) {
            prev->next = new ListNode(1);
        }

        return res.next;
    }
};

static SolutionCpp *pcpp_solvers[] = {
        new SolutionCppA(),
        new SolutionCppB(),
        new SolutionCppC(),
};

TEST(LeetCode_2, Cpp_Example1) {
    ListNode *lres = createList({7, 0, 4, 0, 1});
    set<ListNode *> item_list;
    ListNode *ptemp;

    for (SolutionCpp *psolver: pcpp_solvers) {
        ListNode *l1 = createList({2, 4, 9});
        ListNode *l2 = createList({5, 6, 4, 9});

        ptemp = l1;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }
        ptemp = l2;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }

        ListNode *lact = psolver->addTwoNumbers(l1, l2);
        EXPECT_TRUE(compareLists(lres, lact))
                            << " by solution " << typeid(*psolver).name();

        ptemp = lact;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }

        for (ListNode *pitem : item_list) {
            delete pitem;
        }
        item_list.clear();
    }
    deleteList(lres);
}

TEST(LeetCode_2, Cpp_Example2) {
    ListNode *lres = createList({7, 0, 4, 0, 1});
    set<ListNode *> item_list;
    ListNode *ptemp;

    for (SolutionCpp *psolver: pcpp_solvers) {
        ListNode *l1 = createList({5, 6, 4, 9});
        ListNode *l2 = createList({2, 4, 9});

        ptemp = l1;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }
        ptemp = l2;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }

        ListNode *lact = psolver->addTwoNumbers(l1, l2);
        EXPECT_TRUE(compareLists(lres, lact))
                            << " by solution " << typeid(*psolver).name();

        ptemp = lact;
        while (ptemp) {
            item_list.insert(ptemp);
            ptemp = ptemp->next;
        }

        for (ListNode *pitem: item_list) {
            delete pitem;
        }
        item_list.clear();
    }
    deleteList(lres);
}