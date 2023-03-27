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
    vector<int> reversePrint(ListNode* head) {
        ListNode* cur = head;
        vector<int> result;
        while(cur != nullptr) {
            result.push_back(cur->val);
            cur = cur->next;
        }
        for (int i = 0; i < result.size() / 2; i++) {
            int tmp = result[i];
            result[i] = result[result.size() - 1 - i];
            result[result.size() - 1 - i] = tmp;
        }
        return result;
    }
};