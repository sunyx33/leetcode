class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* node = new Node(insertVal);
        if(head == nullptr) {
            node->next = node;
            return node;
        }
        Node* maxNode = head;
        Node* curNode = head;
        do {
            if(insertVal >= curNode->val && insertVal <= curNode->next->val) { // 其实包含了只有一个节点的情况
                node->next = curNode->next;
                curNode->next = node;
                return head;
            }
            if(curNode->val >= maxNode->val) maxNode = curNode;
            curNode = curNode->next;
        } while(curNode != head);

        // 如果上面循环每找到位置，就说明它比最大节点还大，插到最大节点后面即可
        node->next = maxNode->next;
        maxNode->next = node;
        return head;
    }
};