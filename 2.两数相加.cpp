/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 */

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
    int getSum(ListNode* cur1, ListNode* cur2, bool& carry) {
        int sum = 0;
        if(cur1 && cur2) sum = cur1->val + cur2->val;
        else if (cur1 || cur2) sum = cur1 ? cur1->val : cur2-> val;
        if(carry) sum ++;
        carry = false;
        return sum; 
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        bool carry = false;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* dummyHead = new ListNode();
        ListNode* cur3 = dummyHead;
        int digitSum = 0;
        while((cur1 || cur2) || carry) {
            digitSum = getSum(cur1, cur2, carry);
            if(digitSum >= 10) {
                digitSum -= 10;
                carry = true;
            }
            cur3->next = new ListNode(digitSum);
            if(cur1) cur1 = cur1->next;
            if(cur2) cur2 = cur2->next;
            cur3 = cur3->next;
        }
        return dummyHead->next;
    }
};
// @lc code=end

