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
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        while(1) {
            if(fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast) break;
            } else return nullptr;
        }
        slow = head;
        while(slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};