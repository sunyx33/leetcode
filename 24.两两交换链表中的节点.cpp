/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */

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
    ListNode* swapPairs(ListNode* head) {
        // 设置假头并初始化三个指针，若小于两个结点就直接结束（返回head）
        ListNode* _dummyHead = new ListNode(0, head);
        ListNode* leftNode = _dummyHead;
        ListNode* middelNode = head;
        ListNode* rightNode;
        if (middelNode != nullptr && middelNode->next != nullptr) {
            rightNode = _dummyHead->next->next;
        } else {
            return head;
        }

        while (1) {
            middelNode->next = rightNode->next;
            leftNode->next = rightNode;
            rightNode->next = middelNode;
            if(middelNode->next != nullptr && middelNode->next->next != nullptr){
                leftNode = leftNode->next->next;
                middelNode = middelNode->next;
                rightNode = rightNode->next->next->next;
            } else {
                break;
            }
        }

        return _dummyHead->next;
    }
};
// @lc code=end

