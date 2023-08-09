class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> arr2Map;
        for(int i = 0; i < arr2.size(); i++) arr2Map[arr2[i]] = i;
        sort(arr1.begin(), arr1.end(), [&](int x, int y){
            if(arr2Map.count(x)) return arr2Map.count(y) ? arr2Map[x] < arr2Map[y] : true;
            else return arr2Map.count(y) ? false : x < y;
        });
        return arr1;
    }
};