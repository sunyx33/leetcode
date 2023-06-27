/*
 * @lc app=leetcode.cn id=735 lang=cpp
 *
 * [735] 行星碰撞
 */

// @lc code=start
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for (auto aster : asteroids) {
            bool alive = true;
            while (alive && aster < 0 && !st.empty() && st.back() > 0) {
                alive = st.back() < -aster; // aster 是否存在
                if (st.back() <= -aster) {  // 栈顶小行星爆炸
                    st.pop_back();
                }
            }
            if (alive) {
                st.push_back(aster);
            }
        }
        return st;
    }
};
// @lc code=end

