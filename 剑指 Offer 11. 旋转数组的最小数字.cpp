class Solution {
public:
    int minArray(vector<int>& numbers) {
        int i = 0;
        int j = numbers.size() - 1;
        // 要寻找的是第二个排序数组的首元素
        while (i < j) {
            int m = (i + j) / 2;
            if (numbers[m] < numbers[j]) { // m在第二个排序数组中
                j = m;
            } else if (numbers[m] > numbers[j]) { // m在第一个排序数组中
                i = m + 1;
            } else { // 无法确定m在哪个排序数组中，但能确定的是，把nums[j]拿掉不影响我们找最小值
                j --;
            }
        }
        return numbers[i];
    }
};