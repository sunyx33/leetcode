/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */
// @lc code=start
struct MyListNode {
    int key;
    int val;
    MyListNode* next;
    MyListNode* prev;
    MyListNode() : key(0), val(0), next(nullptr), prev(nullptr) {}
    MyListNode(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
    MyListNode(int key, int val, MyListNode* next, MyListNode* prev) : key(key), val(val), next(next), prev(prev) {}
};

class LRUCache {
public:
    LRUCache(int capacity) {
        m_capacity = capacity;
        m_size = 0;
    }
    
    int get(int key) {
        if(m_map.find(key) == m_map.end()) return -1;
        MyListNode* node = m_map[key];
        moveToTail(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if(m_map.find(key) != m_map.end()) {
            MyListNode* node = m_map[key];
            node->val = value;
            moveToTail(node);
        } else {
            if(m_map.size() == m_capacity) {
                MyListNode* removed = removeHead();
                m_map.erase(removed->key);
                delete removed;
            }
            MyListNode* node = new MyListNode(key, value);
            m_map[key] = node;
            addToTail(node);
        }
    }

    void addToTail(MyListNode* node) {
        node->next = dummyTail;
        node->prev = dummyTail->prev;
        dummyTail->prev->next = node;
        dummyTail->prev = node;
    }

    void removeNode(MyListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;  
    }

    void moveToTail(MyListNode* node) {
        removeNode(node);
        addToTail(node);
    }

    MyListNode* removeHead() {
        MyListNode* node = dummyHead->next;
        removeNode(node);
        return node;
    }
private:
    int m_capacity;
    int m_size;
    unordered_map<int, MyListNode*> m_map; // key - <value, idx>
    MyListNode* dummyHead = new MyListNode(0, 0, dummyTail, nullptr);
    MyListNode* dummyTail = new MyListNode(0, 0, nullptr, dummyHead);
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

