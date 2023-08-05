#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& nums) {
    bool flag;
    for(int i = nums.size() - 1; i > 0; i--) {
        flag = false;
        for(int j = 0; j < i; j++) {
            if(nums[j] > nums[j + 1]){
                swap(nums[j], nums[j + 1]);
                flag = true;
            } 
        }
        if(!flag) break;
    }
}

int main() {
    cout << "bubbleSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    bubbleSort(nums);
    for(int n : nums) {
        cout << n << " ";
    }
    return 0;
}
