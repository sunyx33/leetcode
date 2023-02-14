class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int size = s.size();
        s.resize(size + n);
        for(int i = 0; i < n ; i++) {
            s[size + i] = s[i];
        }
        return s.substr(n);
    }
};