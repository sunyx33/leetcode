#include <stdio.h>
#include <iostream>
using namespace std;

void chooseSort(int nums[], int len) {
    int tmp = 0;
    int minNum = INT_MAX;
    int minNumIdx;
    for (int i = 0; i < len - 1; i++) {
        minNum = INT_MAX;
        for (int j = i; j < len ; j++) { 
            if (nums[j] < minNum) {
                minNumIdx = j;
                minNum = nums[j];
            }
        }
        tmp = nums[i];
        nums[i] = nums[minNumIdx];
        nums[minNumIdx] = tmp;
    }
}

int main() {
    int nums[5] = {0, 5, 1, 4, 3};
    int len = sizeof(nums) / sizeof(nums[0]);
    chooseSort(nums, len);
    return 0;
}
