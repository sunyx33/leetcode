/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return root;
        inorder(root);
        pre->right = head;
        head->left = pre;
        return head;
    }

private:
    Node* pre;
    Node* head; // 记录链表的头结点，即中序遍历的第一个结点（此时pre为空）
    void inorder(Node* cur) {
        if(cur == nullptr) return;
        inorder(cur->left);
        if(pre == nullptr) {
            head = cur;
            pre = cur;
        } else {
            cur->left = pre;
            pre->right = cur;
            pre = cur;
        }
        inorder(cur->right);
    }
};