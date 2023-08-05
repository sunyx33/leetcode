#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int>& nums) {
    for(int i = 1; i < nums.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(nums[j] < nums[j - 1]) swap(nums[j], nums[j - 1]);
            else break;
        }
    }
}

int main() {
    cout << "insertSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    insertSort(nums);
    for(int n : nums) {
        cout << n << " ";
    }
    return 0;
}