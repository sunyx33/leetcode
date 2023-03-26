#include <stdio.h>
#include <iostream>
using namespace std;

void bubbleSort(int nums[], int len) {
    bool flag;
    int tmp = 0;
    for (int i = len - 1; i > 0; i--) {
        flag = false;
        for (int j = 0; j < i; j++) { 
            if(nums[j] > nums[j + 1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
                flag = true;
            }
        }
        if (flag == false) break;
    }
}

int main() {
    int nums[5] = {0, 5, 1, 4, 3};
    int len = sizeof(nums) / sizeof(nums[0]);
    bubbleSort(nums, len);
    return 0;
}
