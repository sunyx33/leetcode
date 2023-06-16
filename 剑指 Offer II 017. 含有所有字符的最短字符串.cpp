class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(58, 0);
        int count = 0;
        for(char c : t) {
            need[c - 'A'] ++;
            count ++;
        }
        int left = 0;
        int right = 0;
        int start = 0;
        int minSize = INT_MAX;
        for(; right < s.size(); right ++) {
            if(need[s[right] - 'A'] > 0) count --;
            need[s[right] - 'A'] --;
            if(count == 0) { // 已经包含所有字母
                while(need[s[left] - 'A'] < 0) need[s[left++] - 'A']++;
                if(right - left + 1 < minSize) {
                    minSize = right - left + 1;
                    start = left;
                }
                need[s[left++] - 'A'] ++;
                count ++;
            }
        }
        return minSize == INT_MAX ? "" : s.substr(start, minSize);
    }
};
