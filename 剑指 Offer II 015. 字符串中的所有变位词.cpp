class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if(p.size() > s.size()) return result;
        vector<int> hashmap_s(26, 0);
        vector<int> hashmap_p(26, 0);
        for(int i = 0; i < p.size(); i++) {
            hashmap_p[p[i] - 'a'] ++;
            hashmap_s[s[i] - 'a'] ++;
        } 
        for(int i = p.size(); i < s.size(); i++) {
            if(hashmap_p == hashmap_s) result.push_back(i - p.size());
            hashmap_s[s[i] - 'a'] ++;
            hashmap_s[s[i - p.size()] - 'a'] --;
        }
        if(hashmap_p == hashmap_s) result.push_back(s.size() - p.size());
        return result;
    }
};