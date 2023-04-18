class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> B(a.size());
        int product = 1;
        for(int i = 0; i < a.size(); product *= a[i++]) {
            B[i] = product;
        }
        product = 1;
        for(int i = a.size() - 1; i >= 0; product *= a[i--]) {
            B[i] *= product;
        }
        return B;
    }
};