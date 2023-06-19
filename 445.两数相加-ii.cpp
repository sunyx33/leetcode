/*
 * @lc app=leetcode.cn id=445 lang=cpp
 *
 * [445] 两数相加 II */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

 

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(head) {
            ListNode* next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverse(l1);
        l2 = reverse(l2);
        int carry = 0;
        ListNode* next = nullptr;
        while(l1 || l2 || carry) {
            int sum = carry;
            if(l1) sum += l1->val;
            if(l2) sum += l2->val;
            ListNode* node = new ListNode(sum % 10, next);
            carry = sum / 10;
            next = node;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        return next;
    }
};
// @lc code=end

