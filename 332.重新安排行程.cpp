/*
 * @lc app=leetcode.cn id=332 lang=cpp
 *
 * [332] 重新安排行程
 */
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
private:
    //<出发机场, map<到达机场, 航班次数>> target
    unordered_map<string, map<string, int>> targets;
    bool backtracking(int ticketNum, vector<string>& result) {
        if(result.size() == ticketNum + 1) {
            return true;
        }
        // result[result.size() - 1]指上一次到达的机场（起始机场为JFK）
        for (pair<const string, int>& target : targets[result[result.size() - 1]]) {
            if (target.second > 0) {
                result.push_back(target.first);
                target.second --;
                if (backtracking(ticketNum, result)) return true;
                result.pop_back();
                target.second ++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> result;
        for (const vector<string>& vec : tickets) {
            targets[vec[0]][vec[1]]++;
        }
        result.push_back("JFK");
        backtracking(tickets.size(), result);
        return result;
    }
};
// @lc code=end

int main() {
    vector<vector<string>> tickets;
    vector<string> str1;
    str1.push_back("JFK");
    str1.push_back("SFO");
    tickets.push_back(str1);

    vector<string> str2;
    str2.push_back("JFK");
    str2.push_back("ATL");
    tickets.push_back(str2);

    vector<string> str3;
    str3.push_back("SFO");
    str3.push_back("ATL");
    tickets.push_back(str3);

    vector<string> str4;
    str4.push_back("ATL");
    str4.push_back("JFK");
    tickets.push_back(str4);

    vector<string> str5;
    str5.push_back("ATL");
    str5.push_back("SFO");
    tickets.push_back(str5);

    Solution sol;
    sol.findItinerary(tickets);

    
    
    
    return 0;
}

