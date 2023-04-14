class Solution {
public:
    string minNumber(vector<int>& nums) {
        vector<string> s;
        for(int num : nums) {
            s.emplace_back(to_string(num));
        }

        sort(s.begin(), s.end(), cmp);
        
        string res = "";
        for(string si : s) {
            res += si;
        }
        return res;
    }

private:
    static bool cmp(string a, string b) {
        return a + b < b + a;
    }
};