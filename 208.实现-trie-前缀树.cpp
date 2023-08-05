/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Trie {
public:
    struct Node {
        bool isWord;
        vector<Node*> children;
        Node() : isWord(false), children(26, nullptr) {};
        ~Node() {
            for(auto& child : children) {
                delete child;
            }
        }
    };
    
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* node = root;
        for(char c : word) {
            if(!node->children[c - 'a']) node->children[c - 'a'] = new Node();
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }
    
    bool search(string word) {
        Node* node = root;
        for(char c : word) {
            if(!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return node->isWord;
    }
    
    bool startsWith(string prefix) {
        Node* node = root;
        for(char c : prefix) {
            if(!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return true;
    }

private:
    Node* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

