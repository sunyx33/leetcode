#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void shellSort(vector<int>& nums) {
    for(int gap = nums.size() / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < nums.size(); i++) {
            for(int j = i - gap; j >= 0; j -= gap) {
                if(nums[j] > nums[j + gap]) {
                    swap(nums[j], nums[j + gap]);
                }
            }
        }
    }
}

int main() {
    cout << "shellSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    shellSort(nums);
    for(int n : nums) {
        cout << n << " ";
    }
    return 0;
}


