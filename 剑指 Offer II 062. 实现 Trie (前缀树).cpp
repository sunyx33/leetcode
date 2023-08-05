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
