class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        vector<ListNode*> vec;
        ListNode* cur = head;

        while (cur) {
            vec.push_back(cur);
            cur = cur->next;
        }

        int left = 0;
        int right = vec.size() - 1;
        while (left < right) {
            vec[left]->next = vec[right];
            vec[right--]->next = vec[++left];
        }
        vec[left]->next = nullptr;
    }
};