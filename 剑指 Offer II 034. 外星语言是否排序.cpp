class Solution {
public:
    // 比较s1与s2的字典序，如果s1 < s2（按照题意字典序大的在后），返回true
    bool cmpWord(string& s1, string& s2) {
        for(int i = 0; i < min(s1.size(), s2.size()); i++) {
            if(dict[s1[i]] < dict[s2[i]]) return true;
            else if(dict[s1[i]] > dict[s2[i]]) return false;
            else continue;
        }
        if(s1.size() <= s2.size()) return true;
        else return false;
    }
    bool isAlienSorted(vector<string>& words, string order) {
        for(int i = 0; i < order.size(); i++) {
            dict[order[i]] = i;
        }
        for(int i = 0; i < words.size() - 1; i++) {
            if(cmpWord(words[i], words[i + 1])) continue;
            else return false;
        }
        return true;
    }
private:
    unordered_map<char, int> dict;
};