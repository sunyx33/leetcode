class Solution {
public:
    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverse(s, 0, s.size() - 1);
        for (int i = 0; i < s.size(); i++) {
            int start = i;
            while (i < s.size() && s[i] != ' ') {
                i++;
            } 
            reverse(s, start, i - 1);
        }
        return s;
    }

    void reverse(string& s, int start, int end) {
        while (start < end) {
            swap(s[start++], s[end--]);
        }
    }

    void removeExtraSpaces(string& s) {
        int slow = 0;
        for(int fast = 0; fast < s.size(); fast ++) {
            if (s[fast] != ' ') {
                if (slow != 0) {
                    s[slow] = ' ';
                    slow ++;
                }
                while(fast < s.size() && s[fast] != ' ') {
                    s[slow] = s[fast];
                    slow ++;
                    fast ++;
                }
            }
        }
        s.resize(slow);
    }
};