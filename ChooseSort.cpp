#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void chooseSort(vector<int>& nums) {
    int minNum = INT_MAX;
    int minIdx = 0;
    for(int i = 0; i < nums.size(); i++) {
        minNum = INT_MAX;
        for(int j = i; j < nums.size(); j++) {
            if(nums[j] < minNum) {
                minNum = nums[j];
                minIdx = j;
            }
        }
        swap(nums[i], nums[minIdx]);
    }
}

int main() {
    cout << "chooseSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    chooseSort(nums);
    for(int n : nums) {
        cout << n << " ";
    }
    return 0;
}
