#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;



int partition(vector<int>& nums, int left, int right) {
    int pivot = right;
    int location = left;
    for(int i = left; i < right; i++) {
        if(nums[i] < nums[pivot]) swap(nums[i], nums[location++]);
    }
    swap(nums[location], nums[pivot]);
    return location;
}

void quickSort(vector<int>& nums, int left, int right) {
    if(right <= left) return ;
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

int main() {
    cout << "quickSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    quickSort(nums, 0, nums.size() - 1);
    for(int n : nums) {
        cout << n << " ";
    }
    return 0;
}