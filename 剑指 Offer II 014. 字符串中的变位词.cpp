class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.size() > s2.size()) return false;
        vector<int> hashmap1(26, 0);
        vector<int> hashmap2(26, 0);
        for(int i = 0; i < s1.size(); i++) {
            hashmap1[s1[i] - 'a'] ++;
            hashmap2[s2[i] - 'a'] ++;
        }

        for(int i = s1.size(); i < s2.size(); i++) {
            if(hashmap1 == hashmap2) return true;
            hashmap2[s2[i] - 'a'] ++;
            hashmap2[s2[i - s1.size()] - 'a'] --;
        }
        return hashmap1 == hashmap2;
    }
};