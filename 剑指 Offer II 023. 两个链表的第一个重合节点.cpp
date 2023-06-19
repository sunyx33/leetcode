/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        int cntA = 0;
        ListNode* curB = headB;
        int cntB = 0;
        while(curA || curB) {
            if(curA) {
                cntA ++;
                curA = curA->next;
            }
            if(curB) {
                cntB ++;
                curB = curB->next;
            }
        }
        curA = headA;
        curB = headB;
        if(cntA < cntB) {
            swap(curA, curB);
            swap(cntA, cntB);
        }

        int gap = cntA - cntB;
        while(gap --) {
            curA = curA->next;
        }
        while(curA && curB) {
            if(curA == curB) return curA;
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }

};