#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<int> merge(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> result(nums1.size() + nums2.size());
    int idx = 0;
    int idx1 = 0;
    int idx2 = 0;
    while(idx1 < nums1.size() && idx2 < nums2.size()) {
        if(nums1[idx1] < nums2[idx2]) result[idx++] = nums1[idx1++];
        else result[idx++] = nums2[idx2++];
    }
    if(idx1 < nums1.size()) {
        for(int i = idx1; i < nums1.size(); i++) {
            result[idx++] = nums1[i];
        }
    } else if(idx2 < nums2.size()) {
        for(int i = idx2; i < nums2.size(); i++) {
            result[idx++] = nums2[i];
        }
    }
    return result;
}

vector<int> mergeSort(const vector<int>& nums, int left, int right) {
    if((right - left) <= 1) {
        vector<int> vec(nums.begin() + left, nums.begin() + right);
        return vec;
    }
    int mid = (left + right) / 2;
    return merge(mergeSort(nums, left, mid), mergeSort(nums, mid, right));
}


int main() {
    cout << "mergeSort" << endl;
    vector<int> nums = {1,7,4,8,2,3,9,5,6};
    vector<int> sortedNums = mergeSort(nums, 0, nums.size() - 1);
    for(int n : sortedNums) {
        cout << n << " ";
    }
    return 0;
}