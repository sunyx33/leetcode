#include <iostream>

using namespace std;
/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// @lc code=start
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp;
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            temp = cur->next;
            cur->next = pre;
            
            pre = cur;
            cur = temp;            
        }
        return pre;       
    }
};
// @lc code=end


