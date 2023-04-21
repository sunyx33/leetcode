class Solution {
private:
    // 整数的格式可以用[+|-]B表示, 其中B为无符号整数
    bool isInteger(const string s, int& index) {
        if(s[index] == '+' || s[index] == '-') index ++;
        return isUnsignedInteger(s, index);
    }

    bool isUnsignedInteger(const string s, int& index) {
        int befor = index;
        while(index != s.size() && s[index] >= '0' && s[index] <= '9') {
            index ++;
        }
        return index > befor;
    }
    
public:
    bool isNumber(string s) {
        if(s.size() == 0) return false;
        int index = 0;

        while(s[index] == ' ') index ++;
        
        bool numeric = isInteger(s, index);

        if(s[index] == '.') {
            index ++;
            numeric = isUnsignedInteger(s, index) || numeric;
        }

        if(s[index] == 'e' || s[index] == 'E') {
            index ++;
            numeric = numeric && isInteger(s, index);
        }

        while(s[index] == ' ') index ++;

        return numeric && index == s.size();
    }
};