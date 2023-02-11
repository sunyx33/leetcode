#include <stdio.h>
#include <algorithm>

using namespace std;
/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 

// @lc code=start

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0;
        int lenB = 0;
        ListNode *curA = headA;
        ListNode *curB = headB;

        // 求A长度
        while(curA != NULL){
            lenA ++;
            curA = curA->next;
        }

        // 求B长度
        while(curB != NULL){
            lenB ++;
            curB = curB->next;
        }

        // 返回头节点
        curA = headA;
        curB = headB;

        // 保持curA是长链表的节点
        if (lenB > lenA) {
            swap(curA, curB);
            swap(lenA, lenB);
        }

        int gap = lenA - lenB;

        // curA走到curB的起点
        while(gap--){
            curA = curA->next;
        }

        while(curA != NULL){
            if(curA == curB){
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }

        return NULL;

    }
};
// @lc code=end

