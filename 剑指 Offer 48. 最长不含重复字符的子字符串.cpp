class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0) return 0;
        unordered_map<char, int> umap;
        int result = 1;
        int count = 1;
        int start = 0;
        umap.emplace(s[0], 0);
        for(int i = 1; i < s.size(); i++) {
            if (umap.find(s[i]) == umap.end()) {
                cout << s[i] << endl;
                umap.emplace(s[i], i);
                count ++;
                if(count > result) result = count;
            } else if (umap[s[i]] < start) {
                umap[s[i]] = i;
                count ++;
                if(count > result) result = count;
            } else {
                start = umap[s[i]] + 1;
                count = i - start + 1;
                umap[s[i]] = i;
            }
        }
        return result;
    }
};