#include "list_node.h"

bool compareLists(const ListNode* list1, const ListNode *list2) {
    while (list1 && list2) {
        if (list1->val != list2->val) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    if (list1 || list2) {
        return false;
    }
    return true;
}

void displayList(const ListNode *list) {
    while (list) {
        std::cout << list->val;
        if (list->next) {
            std::cout << " -> ";
        }
        list = list->next;
    }
}

ListNode *createList(const std::vector<int> nums) {
    ListNode list_head(0);
    ListNode *ptail = &list_head;
    for (int num : nums) {
        ListNode *pnode = new ListNode(num);
        ptail->next = pnode;
        ptail = pnode;
    }
    return list_head.next;
}

void deleteList(ListNode *list) {
    ListNode *pnxt;
    while (list) {
        pnxt = list->next;
        delete list;
        list = pnxt;
    }
}