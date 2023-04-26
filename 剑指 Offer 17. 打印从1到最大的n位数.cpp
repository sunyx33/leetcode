class Solution {
public:
    vector<int> res;
    vector<int> printNumbers(int n) {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= 9; j++)
                dfs(1, i, to_string(j)); //dfs从1开始，因为第0位已经确定了
        return res;
    }
    void dfs(int k, int n, string s) // 我需要一个n位数，现在处理完了第k位，这k位数字是s
    {
        if(k==n)
        {
            res.emplace_back(stoi(s));
            return;
        }
        for(int i = 0; i < 10; i++)
            dfs(k+1, n, s+to_string(i));
    }
};