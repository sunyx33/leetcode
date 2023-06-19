class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t) return false;
        vector<int> vec(26, 0);
        for(char c : s) vec[c - 'a'] ++;
        for(char c : t) vec[c - 'a'] --;
        for(int n : vec) if(n) return false;
        return true;
    }
};