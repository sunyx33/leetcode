/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head, Node* next) {
        Node* cur = head;
        while(cur) {
            if(cur->child) {
                Node* next = cur->next;
                Node* child = flatten(cur->child, next);
                cur->next = child;
                child->prev = cur;
                cur->child = nullptr;
            }
            if(!cur->next) {
                cur->next = next;
                if(next) next->prev = cur;
                break;
            }
            cur = cur->next;
        }
        return head;
    }

    Node* flatten(Node* head) {
        Node* cur = head;
        while(cur) {
            if(cur->child) {
                Node* next = cur->next;
                Node* child = flatten(cur->child, next);
                cur->next = child;
                child->prev = cur;
                cur->child = nullptr;
            }
            cur = cur->next;
        }
        return head;
    }
};