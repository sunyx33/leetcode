#include <iostream>
#include<string>

using namespace std;



class Solution {
public:
    string replaceSpace(string s) {
        int count = 0;
        int oldsize = s.size();
        for(char c : s){
            if (c == ' '){
                count ++;
            }
        }

        s.resize(s.size() + count * 2);
        int newsize = s.size();
        for(int i = oldsize - 1, j = newsize - 1; i < j; i--, j--){
            if(s[i] == ' '){
                s[j] == '0';
                s[j-1] == '2';
                s[j-2] == '%';
                j = j - 2;
                
            } else {
                s[j] = s[i];
            }
        }

        return s;
    }
};

int main(){
    string test = "we are happy.";
    Solution sol;
    test = sol.replaceSpace(test);
    cout << test << endl;
    return 0;
}