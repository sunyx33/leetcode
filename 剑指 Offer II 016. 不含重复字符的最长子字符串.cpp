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
                umap.emplace(s[i], i);
                count ++;
                if(count > result) result = count;
            } else if (umap[s[i]] < start) { // 有重复，但重复的字符在左边界之前
                umap[s[i]] = i; // 更新重复字符的索引，继续右移右边界
                count ++;
                if(count > result) result = count;
            } else { // 有重复，重复的字符在左边界之后
                start = umap[s[i]] + 1; // 左边界移到重复的下一个
                count = i - start + 1; 
                umap[s[i]] = i;
            }
        }
        return result;
    }
};