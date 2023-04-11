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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* start = head;
        ListNode* end = head;
        while(k - 1) {
            end = end->next;
            k--;
        }
        while(end->next) {
            start = start->next;
            end = end->next;
        }
        return start;
    }
};