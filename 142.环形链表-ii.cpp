struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// @lc code=start

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (1)
        {
            if (fast != NULL && fast->next != NULL && fast->next->next != NULL){
                fast = fast->next->next;
                slow = slow->next;
                if(fast == slow){
                    break;
                }
            } else {
                return NULL;
            }

        }

        slow = head;

        while (1)
        {
            if(fast == slow) {
                return fast;
            }
            fast = fast->next;
            slow = slow->next;
        }

        return NULL;        
    }
};
// @lc code=end