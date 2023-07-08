/*
 * @lc app=leetcode.cn id=729 lang=cpp
 *
 * [729] 我的日程安排表 I
 */

// @lc code=start
class MyNode{
public:
    int start;
    int end;
    MyNode* left;
    MyNode* right;
    MyNode(int start, int end) : start(start), end(end), left(nullptr), right(nullptr){}
    bool operator>(const MyNode& node) {
        return this->start >= node.end;
    }
    bool operator<(const MyNode& node) {
        return node.start >= this->end;
    }
};


class MyCalendar {
public:
    MyCalendar() {
        root = nullptr;
    }
    
    bool book(int start, int end) {
        MyNode* node = new MyNode(start, end);
        return insert(root, node);
    }

    bool insert(MyNode*& root, MyNode* node) {
        if(!root) {
            root = node;
            return true;
        } else if(*node > *root) return insert(root->right, node);
        else if(*node < *root) return insert(root->left, node);
        else return false;
    };

    MyNode* root;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
// @lc code=end

