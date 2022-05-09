#ifndef PUZZLES_LEETCODE_LIST_NODE_H
#define PUZZLES_LEETCODE_LIST_NODE_H

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool compareLists(const ListNode* list1, const ListNode *list2);

void displayList(const ListNode *list);

ListNode *createList(const std::vector<int> nums);

void deleteList(ListNode *list);

#endif // PUZZLES_LEETCODE_LIST_NODE_H
