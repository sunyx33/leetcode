---
title: leetcode刷题日记
description: <h4 align="center"> 玩一玩 </h4>
date: 2022-09-02 14:54:54
categories:
- 算法
tags:
- leetcode
---

# 数组

## 704. 二分查找 [easy]

[704. 二分查找 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-search/)

**思路：**

二分查找看似简单，但边界问题需要注意，写不好很容易有bug。

我们定义middel指针在一个左闭右闭的区间中：[start, end]，左右边界都能取到，那么end = 真实下标（size - 1），且while (end >= start)，可以出现左右边界重合的情况。

另外，在更新start或end的时候，考虑到middel已经不是target了，则 start = middel + 1 或 end = middel - 1，不然会陷入死循环。

这种基础算法还是直接背过为好。

**代码：**

```c++
/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 */

// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (end >= start) {
            int middle = start + (end - start) / 2;
            if (target > nums[middle]) {
                start = middle + 1;
            } else if (target < nums[middle]) {
                end = middle - 1;
            } else {
                return middle;
            }
        }

        return -1;
    }
};
// @lc code=end
```



## 27. 移除元素 [easy]

[27. 移除元素 - 力扣（LeetCode）](https://leetcode.cn/problems/remove-element/)

**思路：**

暴力解法，两层循环，第一遍找到待删除的元素，第二遍将后面的元素集体后移一位，时间复杂度O(n^2)

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/27.移除元素-暴力解法.gif)

那么如何将两层循环优化为一层呢？用两个指针，都从头开始往后找，并在每次循环用快指针覆写慢指针，若快指针指到待删元素，就跳过覆写操作，自己往后移一个，继续下次循环。这样一来，一旦出现快慢差，就会将待删除指针覆写掉了（遇到几个待删除元素，快慢差就差几）。这样一层for搞定，O(n)

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/27.移除元素-双指针法.gif)

**代码：**

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if (val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
};
```



## 977. 有序数组的平方 [easy]

[977. 有序数组的平方 - 力扣（LeetCode）](https://leetcode.cn/problems/squares-of-a-sorted-array/)

**思路：**

数组其实是有序的， 只不过负数平方之后可能成为最大数了。那么数组平方的最大值就在数组的两端，不是最左边就是最右边，不可能是中间。

给两个指针，两边往中间靠，每次从两个指针指的数选择一个绝对值大的倒序填入新数组。

**代码：**

```c++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int k = nums.size() - 1;
        vector<int> result(nums.size(), 0);
        for (int i = 0, j = nums.size() - 1; i <= j;) { // 注意这里要i <= j，因为最后要处理两个元素
            if (nums[i] * nums[i] < nums[j] * nums[j])  {
                result[k--] = nums[j] * nums[j];
                j--;
            }
            else {
                result[k--] = nums[i] * nums[i];
                i++;
            }
        }
        return result;
    }
};
```



## 209. 长度最小的子数组 [medium]

[209. 长度最小的子数组 - 力扣（LeetCode）](https://leetcode.cn/problems/minimum-size-subarray-sum/)

**思路：**

滑动窗口思想——**不断的调节子序列的起始位置和终止位置，从而得出我们要想的结果**。

暴力解法中两个for循环其实就表示了窗口的首尾，但其中有很多冗余的操作。那么用一个for循环，循环量是窗口尾部，每次满足条件，头部再+1，找新的尾部就好。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/209.长度最小的子数组.gif)

**代码：**

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = __INT32_MAX__;
        int start = 0;
        int sum = 0;
        int sublenth = 0;
        for (int end = 0; end < nums.size(); end++) {
            sum += nums[end];
            while(sum >= target) {
                sublenth =  end - start + 1;
                result = result < sublenth ? result : sublenth;
                sum -= nums[start++];
            }
        }
        return result == __INT32_MAX__ ? 0 : result;
    }
};
```



## 59. 螺旋矩阵 [medium]

[59. 螺旋矩阵 II - 力扣（LeetCode）](https://leetcode.cn/problems/spiral-matrix-ii/)

**思路：**

按条件往下写，注意边界问题。

在写复杂循环时，一定要注意做到：所有的循环条件都按照一个标准（如都是左闭右开区间），即**循环不变量原则**。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20220922102236.png)

**代码：**

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0)); // 使用vector定义一个二维数组
        int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
        int loop = n / 2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
        int mid = n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
        int count = 1; // 用来给矩阵中每一个空格赋值
        int offset = 1; // 需要控制每一条边遍历的长度，每次循环右边界收缩一位
        int i,j;
        while (loop --) {
            i = startx;
            j = starty;

            // 下面开始的四个for就是模拟转了一圈
            // 模拟填充上行从左到右(左闭右开)
            for (j = starty; j < n - offset; j++) {
                res[startx][j] = count++;
            }
            // 模拟填充右列从上到下(左闭右开)
            for (i = startx; i < n - offset; i++) {
                res[i][j] = count++;
            }
            // 模拟填充下行从右到左(左闭右开)
            for (; j > starty; j--) {
                res[i][j] = count++;
            }
            // 模拟填充左列从下到上(左闭右开)
            for (; i > startx; i--) {
                res[i][j] = count++;
            }

            // 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
            startx++;
            starty++;

            // offset 控制每一圈里每一条边遍历的长度
            offset += 1;
        }

        // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
        if (n % 2) {
            res[mid][mid] = count;
        }
        return res;
    }
};
```





# 链表

## 203. 移除链表元素 [easy]

[203. 移除链表元素 - 力扣（LeetCode）](https://leetcode.cn/problems/remove-linked-list-elements/)

**思路：**

链表删除节点的基础操作，没啥好说的。注意两点：

* 头节点的删除，要么来一个虚拟头节点指向头节点，删除逻辑与其他一样；要么就写一段单独的逻辑：头节点向后移一步，释放头节点。
* c++在删除时，注意用delete释放堆区内存（new过的）。

**代码：**

```c++
/*
 * @lc app=leetcode.cn id=203 lang=cpp
 *
 * [203] 移除链表元素
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* cur = dummyHead;
        while (cur->next) {
            if (cur->next->val == val){
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
};
// @lc code=end
```



## 707. 设计链表 [medium]

[707. 设计链表 - 力扣（LeetCode）](https://leetcode.cn/problems/design-linked-list/)

**思路：**

本题为实现链表的一些基本操作，不难，这里主要规范一下链表的数据结构：

```c++
class MyLinkedList {
public:
    struct Node{
        int val;
        Node* next;
        Node(int val):val(val), next(nullptr){}
    };

    // 初始化链表
    MyLinkedList() {
        _dummyHead = new Node(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        _size = 0;
    }
    
    //各种方法...
        
private:
    Node* _dummyHead;
    int _size;
}
```



**代码：**

```c++
/*
 * @lc app=leetcode.cn id=707 lang=cpp
 *
 * [707] 设计链表
 */

// @lc code=start
class MyLinkedList {
public:
    struct Node{
        int val;
        Node* next;
        Node(int val):val(val), next(nullptr){}
    };
    
    // 初始化链表
    MyLinkedList() {
        _dummyHead = new Node(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        _size = 0;
    }

    
    int get(int index) {
        if (index > (_size - 1) || index < 0) {
           return -1; 
        }
        Node* cur = _dummyHead->next;

        while (index --) {
            cur = cur->next;
        }

        return cur->val;
    }
    
    void addAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size ++;
    }
    
    void addAtTail(int val) {
        Node* newNode = new Node(val);
        Node* cur = _dummyHead;
        while(cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
        _size ++;

    }
    
    void addAtIndex(int index, int val) {
        if(index > _size){
            return;
        } else if (index <= 0) {
            addAtHead(val);
        } else {
            Node* newNode = new Node(val);
            Node* cur = _dummyHead;
            while (index --) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            cur->next = newNode;
            _size ++;
        }
        

    }
    
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        } 
        Node* cur = _dummyHead;
        while(index --){
            cur = cur->next;
        }
        Node* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        _size --;
    }

private:
    Node* _dummyHead;
    int _size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
// @lc code=end
```



## 206. 翻转链表 [easy]

[206. 反转链表 - 力扣（LeetCode）](https://leetcode.cn/problems/reverse-linked-list/)

**思路：**

从头节点的前一个结点开始，记录前中后三个节点，中指向前，前等于中，中等于后，后等于后+1.

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/206.翻转链表.gif)

**代码：**

```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// @lc code=start
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp;
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            temp = cur->next;
            cur->next = pre;
        
            pre = cur;
            cur = temp;        
        }
        return pre;   
    }
};
// @lc code=end
```



## 24. 两两交换链表中的节点 [medium]

[24. 两两交换链表中的节点 - 力扣（LeetCode）](https://leetcode.cn/problems/swap-nodes-in-pairs/)

**思路：**

首先是要设置虚拟头节点，目的是让真头节点一般化

交换位置，从小到大，从左向右依次交换。先画图模拟，交换过程中没有指针指向的节点就要用tmp先存起来。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/24.两两交换链表中的节点1.png)

比如步骤一，1失去指向它的指针；步骤二，3失去指向它的指针。

另外，注意判空指针，很重要。

**代码：**

```c++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next; // 记录临时节点
            ListNode* tmp1 = cur->next->next->next; // 记录临时节点

            cur->next = cur->next->next;    // 步骤一
            cur->next->next = tmp;          // 步骤二
            cur->next->next->next = tmp1;   // 步骤三

            cur = cur->next->next; // cur移动两位，准备下一轮交换
        }
        return dummyHead->next;
    }
};
```



## 19. 删除链表的倒数第N个节点 [medium]

**思路：**

双指针的经典应用，如果要删除倒数第n个节点，让fast移动n步，然后让fast和slow同时移动，直到fast指向链表末尾。删掉slow所指向的节点就可以了。

**代码：**

```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// @lc code=start
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while(n-- && fast != NULL) {
            fast = fast->next;
        }
        if (fast != NULL){
            fast = fast->next;
        }
     
        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;   
        
        return dummyHead->next;
    }
};
// @lc code=end
```

## 160. 相交链表 [easy]

[160. 相交链表 - 力扣（LeetCode）](https://leetcode.cn/problems/intersection-of-two-linked-lists/)

**思路：**

- 计算两个链表的长度差gap
- 相交点在后面，所以从前面的同一起点开始（长链表先向前走gap步），一起往后逐个比较。

**代码：**

```c++
#include <stdio.h>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
 
// @lc code=start
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0;
        int lenB = 0;
        ListNode *curA = headA;
        ListNode *curB = headB;

        // 求A长度
        while(curA != NULL){
            lenA ++;
            curA = curA->next;
        }

        // 求B长度
        while(curB != NULL){
            lenB ++;
            curB = curB->next;
        }

        // 返回头节点
        curA = headA;
        curB = headB;

        // 保持curA是长链表的节点
        if (lenB > lenA) {
            swap(curA, curB);
            swap(lenA, lenB);
        }

        int gap = lenA - lenB;

        // curA走到curB的起点
        while(gap--){
            curA = curA->next;
        }

        while(curA != NULL){
            if(curA == curB){
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }

        return NULL;

    }
};
// @lc code=end
```

## 142. 环形链表Ⅱ [medium]

[142. 环形链表 II - 力扣（LeetCode）](https://leetcode.cn/problems/linked-list-cycle-ii/)

**思路：**

[牛逼，建议全文背诵](https://www.programmercarl.com/0142.环形链表II.html#_142-环形链表ii)

首先，怎么确定一个链表是否有环？

定义快慢两个指针，快指针一次走两步，慢指针一次走一步，快指针先走，那么如果两指针相遇，则一定有环。很简单，跑的快的人比跑的慢的人先跑，如果后面两人相遇了，那就是套圈了呗。

其次，如何确定环的入口？

假设从头结点到环形入口节点 的节点数为x。 环形入口节点到 fast指针与slow指针相遇节点 节点数为y。 从相遇节点 再到环形入口节点节点数为 z。 如图所示：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20220925103433.png)

观察相遇时刻，慢指针走了 x + y 个节点，快指针走了 x + n ( y + z ) + y个节点，两者相遇，所用时间相等，则快指针走的节点数是慢指针的两倍。故有：

$$
2(x+y) = x + y+n(y+z)
$$

化简得：

$$
x -z= (n - 1) (y + z)
$$

由此可得，x与z的节点数差就是整数倍的圈长。（注意，此处 n ≥ 1）

那么我们让另外两个同速指针从**头节点**与**相遇节点**同时出发，每次走一步，那么两指针相遇处就一定是环形入口了。

> 为啥人家就那么聪明呢？

**代码：**

```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// @lc code=start

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (1)
        {
            if (fast != NULL && fast->next != NULL && fast->next->next != NULL){
                fast = fast->next->next;
                slow = slow->next;
                if(fast == slow){
                    break;
                }
            } else {
                return NULL;
            }

        }

        slow = head;

        while (1)
        {
            if(fast == slow) {
                return fast;
            }
            fast = fast->next;
            slow = slow->next;
        }

        return NULL;    
    }
};
// @lc code=end
```





# 哈希表

## 基础理论

当我们想使用哈希法来解决问题的时候，我们一般会选择如下三种数据结构。

- 数组
- set （集合）
- map（映射）

这里数组就没啥可说的了，我们来看一下set。

在C++中，set 和 map 分别提供以下三种数据结构，其底层实现以及优劣如下表所示：

| 集合               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::set           | 红黑树   | 有序     | 否               | 否           | O(log n) | O(log n) |
| std::multiset      | 红黑树   | 有序     | 是               | 否           | O(logn)  | O(logn)  |
| std::unordered_set | 哈希表   | 无序     | 否               | 否           | O(1)     | O(1)     |

std::unordered_set底层实现为哈希表，std::set 和std::multiset 的底层实现是红黑树，红黑树是一种平衡二叉搜索树，所以key值是有序的，但key不可以修改，改动key值会导致整棵树的错乱，所以只能删除和增加。

关于set的基础知识：

[C++ STL set容器完全攻略（超级详细） (biancheng.net)](http://c.biancheng.net/view/7192.html)

[C++ STL unordered_set容器完全攻略 (biancheng.net)](http://c.biancheng.net/view/7250.html)

| 映射               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::map           | 红黑树   | key有序  | key不可重复      | key不可修改  | O(logn)  | O(logn)  |
| std::multimap      | 红黑树   | key有序  | key可重复        | key不可修改  | O(log n) | O(log n) |
| std::unordered_map | 哈希表   | key无序  | key不可重复      | key不可修改  | O(1)     | O(1)     |

std::unordered_map 底层实现为哈希表，std::map 和std::multimap 的底层实现是红黑树。同理，std::map 和std::multimap 的key也是有序的（这个问题也经常作为面试题，考察对语言容器底层的理解）。

当我们要使用集合来解决哈希问题的时候，优先使用unordered_set，因为它的查询和增删效率是最优的，如果需要集合是有序的，那么就用set，如果要求不仅有序还要有重复数据的话，那么就用multiset。

那么再来看一下map ，在map 是一个key value 的数据结构，map中，对key是有限制，对value没有限制的，因为key的存储方式使用红黑树实现的。

其他语言例如：java里的HashMap ，TreeMap 都是一样的原理。可以灵活贯通。

虽然std::set、std::multiset 的底层实现是红黑树，不是哈希表，std::set、std::multiset 使用红黑树来索引和存储，不过给我们的使用方式，还是哈希法的使用方式，即key和value。所以使用这些数据结构来解决映射问题的方法，我们依然称之为哈希法。 map也是一样的道理。

这里在说一下，一些C++的经典书籍上 例如STL源码剖析，说到了hash_set hash_map，这个与unordered_set，unordered_map又有什么关系呢？

实际上功能都是一样一样的， 但是unordered_set在C++11的时候被引入标准库了，而hash_set并没有，所以建议还是使用unordered_set比较好，这就好比一个是官方认证的，hash_set，hash_map 是C++11标准之前民间高手自发造的轮子。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210104235134572.png)

总结一下，**当我们遇到了要快速判断一个元素是否出现集合里的时候，就要考虑哈希法**。

但是哈希法也是**牺牲了空间换取了时间**，因为我们要使用额外的数组，set或者是map来存放数据，才能实现快速的查找。

如果在做面试题目的时候遇到需要判断一个元素是否出现过的场景也应该第一时间想到哈希法！

## 242. 有效的字母异位词 [easy]

[242. 有效的字母异位词 - 力扣（LeetCode）](https://leetcode.cn/problems/valid-anagram/)

**思路：**

遍历两个字符串，统计每个字母出现的顺序，用一个数组记录。（数组的索引为该字母的ASCII值，这也就是哈希方法的体现）

**代码思路：**

1. 建立一个长度为26的数组 `count`，用于记录每个字母的出现频次。（f  =>>  count['f'-'a']; ）
2. 遍历第一个字符串，++记录
3. 遍历第二个字符串，--记录
4. 检查 `count`数组是否全部为0（遍历），是返回true，否返回false。

**代码：**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        int count[26] = {0};
        for (int i = 0; i < s.size(); i++)
        {
            count[s[i]-'a'] ++;
        }
        for (int j = 0; j < t.size(); j++)
        {
            count[t[j]-'a']--;
        }
        for (int k = 0; k < 26; k++)
        {
            if (count[k] != 0)
            {
                return false;
            }
        }
        return true;
    }
};
```



## 349. 两个数组的交集 [easy]

[349. 两个数组的交集 - 力扣（LeetCode）](https://leetcode.cn/problems/intersection-of-two-arrays/)

**思路：**

将nums1转换为哈希表的形式（具体用set来实现），然后遍历查找nums2的数字是否存在于哈希表中，若存在则记录为最终结果。

**代码思路：**

1. 定义一个 `unordered_set` 作为存放结果的地方（顺带去重效果）
2. 将 `nums1`转为 `unordered_set`
3. 将 `nums2` 与上一步的结果进行比对，比对上的录入最终结果

**代码：**

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set; // 存放结果
        unordered_set<int> nums_set(nums1.begin(), nums1.end()); // 使用迭代器进行初始化，vec -> set
        for(int num : nums2){
            if(nums_set.find(num) != nums_set.end()){
                result_set.insert(num);
            }
        }

        return vector<int>(result_set.begin(), result_set.end());
    }
};
```



## 202. 快乐数 [easy]

[202. 快乐数 - 力扣（LeetCode）](https://leetcode.cn/problems/happy-number/)

**思路：**

本质上还是要老老实实递归往下算，重点在于如何判断是否陷入无限循环：即判断是否算出了先前出现的结果。这里本质是一个查找操作，自然想到哈希方法，用一个 `unordered_set` 来存储出现过的所有结果，以便进行比对。

**代码思路：**

1. 首先要写一个各位平方和的方法，通过除以10取余的方式来提取出各位。
2. 正常计算，算完后判断一下是否为1，是的话返回true
3. 若不为1，则将结果与存放结果的set进行比对，若比对上则返回false，表示已经开始循环；若没有比对上则录入结果，继续算。

**代码：**

```c++
class Solution {
public:
    int getSum(int n){
        int sum = 0;
        while (n) {
            sum += (n % 10 ) * (n % 10);
            n /= 10;
        }

        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> res;
        while (1) {
            n = getSum(n);
            if (n == 1) {
                return true;
            }

            if (res.find(n) != res.end()){
                return false;
            } else {
                res.insert(n);
            }
        }    
    }
};
```



## 1. 两数之和 [easy]

[1. 两数之和 - 力扣（LeetCode）](https://leetcode.cn/problems/two-sum/)

**思路：**

在给定数据中查找是否有target - nums[i]这个数字，如果有则返回i和这个数字的下标。查找一个集合中是否有某个元素，就应该想到哈希方法。这里我们可以用 `unordered_map` 这一结构，key为数字的值，value为数字的下标，这样知道要找的数字的值，就可以快速锁定其在原数组的下标。

**代码思路：**

1. 首先要把给定数据转成 `unordered_map` ，但不是一次性转完，+而是一边找一边转（如下）
2. 遍历数组，寻找当前map中是否有target-nums[i]这个数字，如果有，则返回i与map中该key所对应的value。
3. 若没有，则将 `key = nums[i],  value = i` 插入map中，继续下次循环。

**代码：**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> res;
        for(int i = 0; i < nums.size(); i++){
            auto iter = res.find(target - nums[i]);
            if(iter != res.end()){
                return {iter->second, i};
            }
            res.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};
```



## 454. 四数相加 [medium]

[454. 四数相加 II - 力扣（LeetCode）](https://leetcode.cn/problems/4sum-ii/)

**思路：**

与上题类似。记录AB数组所有和的情况（这里仅记录不同结果出现的次数）（map，key=和，value=次数），然后遍历CD数组所有和的情况，查看map中是否有0-C[i]-D[i]的key，有的话结果+1.

**代码思路：**

1. 首先定义 一个unordered_map，key放a和b两数之和，value 放a和b两数之和出现的次数。
2. 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中。
3. 定义int变量count，用来统计 a+b+c+d = 0 出现的次数。
4. 在遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就用count把map中key对应的value也就是出现次数统计出来。
5. 最后返回统计值 count 就可以了

**代码：**

```c++
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> umap; //key:a+b的数值，value:a+b数值出现的次数
        // 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中
        for (int a : A) {
            for (int b : B) {
                umap[a + b]++;
            }
        }
        int count = 0; // 统计a+b+c+d = 0 出现的次数
        // 在遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
        for (int c : C) {
            for (int d : D) {
                if (umap.find(0 - (c + d)) != umap.end()) {
                    count += umap[0 - (c + d)];
                }
            }
        }
        return count;
    }
};
```



## 383. 赎金信 [easy]

[383. 赎金信 - 力扣（LeetCode）](https://leetcode.cn/problems/ransom-note/)

**思路：**

与242题十分相似，用数组对每个字母计数，然后遍历赎金信减去数组相应字母的数量，看是否有负数。

**代码思路：**

1. 若ran.size() > mag.size()，直接返回false
2. 遍历mag计数
3. 遍历ran反向计数

**代码：**

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        if(ransomNote.size() > magazine.size()){
            return false;
        }

        for(int i = 0; i < magazine.size(); i++){
            record[magazine[i] - 'a'] ++;
        }

        for(int j = 0; j < ransomNote.size(); j++){
            record[ransomNote[j] - 'a'] --;
            if(record[ransomNote[j] - 'a'] < 0){
                return false;
            }
        }

        return true;
    }
};
```





# 字符串

[C++的string库用法总结](https://zhuanlan.zhihu.com/p/388823262)

## 344. 反转字符串 [easy]

[344. 反转字符串 - 力扣（LeetCode）](https://leetcode.cn/problems/reverse-string/)

**思路：**

为数不多我可以重拳出击的题，没啥好说的，头尾俩指针，swap，往中间走。

**代码：**

```c++
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while(right > left){
            swap(s[left], s[right]);
            left ++;
            right --;
        }
    }

    void swap(char& a, char& b){
        char temp = a;
        a = b;
        b = temp;
    }
};
```



## 541. 反转字符串II [easy]

[541. 反转字符串 II - 力扣（LeetCode）](https://leetcode.cn/problems/reverse-string-ii/)

**思路：**

这是一个找规律模拟题，每次需要反转的字串都可以写成关于k的函数：start = (i - 1) * k；end = i * k - 1；其中i = 1,3,5,7,...

 (i - 1) * k ~  i * k - 1这个窗口没有发生越界的话，就对这个子串反转，否则对从 i * k - 1到头的所有字符反转。

至于反转字符串就无需多言了。

**代码：**

```c++
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 1; (i - 1) * k < s.size(); i = i + 2 ) {
            if ((i * k - 1) < s.size()) {
                reverse(s, (i - 1) * k, i * k - 1);
            } else {
                reverse(s, (i - 1) * k, s.size() - 1);
            }
        }

        return s;
    }

    void reverse(string& s, int start, int end){
        while(start < end){
            swap(s[start], s[end]);
            start ++;
            end --;
        }
    }
};
```



## 剑指Offer | 05. 替换空格 [easy]

[剑指 Offer 05. 替换空格](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)

**思路：**

空格变成"%20"，字符串变长了，要扩容。

**很多数组填充类的问题，都可以先预先给数组扩容带填充后的大小，然后在从后向前进行操作。**从前向后填充就是O(n^2)的算法了，因为每次添加元素都要将添加元素之后的所有元素向后移动。

所以，先统计空格个数，计算扩容后长度，进行扩容。接着，从后往前，双指针，速差来源于空格，一个空格三个速差。

**代码：**

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int count = 0; // 统计空格的个数
        int sOldSize = s.size();
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                count++;
            }
        }
        // 扩充字符串s的大小，也就是每个空格替换成"%20"之后的大小
        s.resize(s.size() + count * 2);
        int sNewSize = s.size();
        // 从后先前将空格替换为"%20"
        for (int i = sNewSize - 1, j = sOldSize - 1; j < i; i--, j--) {
            if (s[j] != ' ') {
                s[i] = s[j];
            } else {
                s[i] = '0';
                s[i - 1] = '2';
                s[i - 2] = '%';
                i -= 2;
            }
        }
        return s;
    }
};
```



## 151. 翻转字符串里的单词 [medium]

[151. 反转字符串中的单词 - 力扣（LeetCode）](https://leetcode.cn/problems/reverse-words-in-a-string/)

**思路：**

- 移除多余空格
- 将整个字符串反转
- 将每个单词反转

移除前后多余空格比较难，自带的erase方法时间复杂度是O(n)，他在for循环里，就成了O(n^2)，所以不能用。

使用双指针法来去移除空格，最后resize（重新设置）一下字符串的大小，就可以做到O(n)的时间复杂度。思路同移除元素，但这里要保留单词间的空格。具体代码如下：

**代码：**

移除多余空格：

```c++
void removeExtraSpaces(string& s) {//去除所有空格并在相邻单词之间添加空格, 快慢指针。
    int slow = 0;   //整体思想参考https://programmercarl.com/0027.移除元素.html
    for (int i = 0; i < s.size(); ++i) { //
        if (s[i] != ' ') { //遇到非空格就处理，即删除所有空格。
            if (slow != 0) s[slow++] = ' '; //slow != 0说明不是第一个单词，需要在单词前添加空格。
            while (i < s.size() && s[i] != ' ') { //补上该单词，遇到空格说明单词结束。
                s[slow++] = s[i++];
            }
        }
    }
    s.resize(slow); //slow的大小即为去除多余空格后的大小。
}
```

整体：

```c++
class Solution {
public:
    string reverseWords(string s) {
        delEmpty(s);
        reverse(s, 0, s.size() - 1);
        for (int i = 0; i < s.size(); i++){
            int start = i;
            while(i < s.size() && s[i] != ' ') {
                i ++;
            }
            reverse(s, start, i - 1);
        }
        return s;
    }

    void reverse(string& s, int start, int end){
        while(start < end){
            swap(s[start], s[end]);
            start ++;
            end --;
        }
    }

    void swap(char& a, char& b){
        char temp = a;
        a = b;
        b = temp;
    }

    void delEmpty(string& s){
        int slow = 0;
        for (int fast = 0; fast < s.size(); fast++) {
            if (s[fast] != ' ') {
                if (slow != 0) s[slow++] = ' ';
                while (fast < s.size() && s[fast] != ' ') { 
                    s[slow++] = s[fast++];
                }
            }
        }
    
        s.resize(slow);
    }
};
```



## 剑指Offer | 58-II.左旋转字符串 [easy]

[剑指 Offer 58 - II. 左旋转字符串 - 力扣（LeetCode）](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

**思路：**

第一种，要用到额外空间，将字符延长至size + n，其中size + i的位置放第i个字符，i=0,1,...,n

第二种，不用额外空间：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/剑指Offer58-II.左旋转字符串.png)

两种差不多，第二种相较于第一种少了空间，多了时间。

**代码：**

第一种：

```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int size = s.size();
        s.resize(size + n);
        for(int i = 0; i < n ; i++) {
            s[size + i] = s[i];
        }
        return s.substr(n);
    }
};
```

第二种：

```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};
```



## 28. 找出字符串中第一个匹配项的下标 [medium]

[28. 找出字符串中第一个匹配项的下标 - 力扣（LeetCode）](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)

**思路：**

KMP算法。

KMP算法是字符串模式匹配的经典方法，它将暴力求解的时间复杂度O(nm)降为O(n^2)。

我尝试用文字说清楚：

模式串与原串进行匹配，模式串匹配到**第j位**，原串匹配到**第i位**，两者不一样了，那就去找**前j-1位最长的相同前后缀的长度next[j-1]**，进而下一次匹配从i位与next[j-1]位开始（长度等于索引+1，但要看的是前缀后面的那一个，所以这里next[j-1]刚好就不加了）。

中止条件：模式串j移到最后一位并且匹配上，则成功匹配；原串i移动最后一位但j没有到头，则不匹配。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/KMP精讲2.gif)

如何求next数组？

大多数教程里没有点明的是，在求next数组时，本身也用到了KMP算法，即前缀为模式串，当前i指针之前的字符串为原串。有点递归的思想在里面。

1. 初始化

   j = 0； next[0] = 0; for(i = 1; i < s.size(); i++)。

   始终记住，j指向前缀的最后一位（也就是模式串待匹配的第一位，也就是说任何时候j之前的字符都以匹配）；i指向原串待匹配的位置。

2. 若当前待匹配位（j， i）不同

   找j之前的最长相同前后缀长度，即next[j - 1]。退而比较s[i]与s[next[j-1]]，直至j退为0，则没希望了，nexti] = 0，i继续往下走吧。

   > 注意：始终有i≥j + 1，也就是说next[j - 1]始终是已经填好的，满足 j > 0 即可。

3. 若当前位匹配上了

   j++， 填写next[i] = j。

   > j始终指向最长前后缀的后一位，所以它也有计数（计长度）的功能。

**代码：**

```c++
class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size() ) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
```



## 459.重复的子字符串 \[easy]

[459. 重复的子字符串 - 力扣（LeetCode）](https://leetcode.cn/problems/repeated-substring-pattern/)

**思路：**

第一种方法：把字符串复制一份拼到原字符串后，则新字符串的中心一定会找到原字符串

第二种方法：KMP法

我们来看整个字符串的最长前后缀长度next[s.size() - 1]，如果字符串可以整除`s.size() - next[s.size() - 1]`，则true

本质是在看前后缀是否首尾相接，或可以拆成首尾相接的更小的重复项。（证明子串是重复的）

[代码随想录 (programmercarl.com)](https://www.programmercarl.com/0459.重复的子字符串.html#kmp)

**代码：**

第一种：

```c++
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string t = s + s;
        t.erase(t.begin()); t.erase(t.end() - 1); // 掐头去尾
        if (t.find(s) != std::string::npos) return true; // r
        return false;
    }
};
```

第二种：

```c++
class Solution {
public:
    void getNext(int next[], const string& s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1]; // 若当前两个不同，则找次长相同前后缀
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size() ) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
```







# 双指针法

## 15. 三数之和 [medium]

[15. 三数之和 - 力扣（LeetCode）](https://leetcode.cn/problems/3sum/)

**思路：**

两层for循环就可以确定 a 和b 的数值了，可以使用哈希法来确定 0-(a+b) 是否在 数组里出现过，其实这个思路是正确的，时间复杂度也更低（o(n^2)），但在结果去重时非常困难，故采用双指针法来做。

双指针法的大前提是，该数列是一个从小到大排序后的数列。我们选择一个起始位置i，另外有两个指针：left = i + 1， right = nums.size() - 1，每次找答案时，i固定，判断三个指针指向数字之和，若大于0，right左移；若小于0，left右移；等于0，记录结果。具体效果可以看下图：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/15.三数之和.gif)

再说去重思路。对于a的去重，判断当前位置与前一个是否相等，若相等，则cotinue（因为最小数为这个数的所有情况已然穷尽）。对于b、c的去重，则是当找到一组解后，若发现right的左边或left右边与当前数字相等，则继续左移或右移。

**代码：**

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < nums.size(); i++){
            // 从小到大排序，第一个都大于0则不可能和为0
            if(nums[i] > 0){
                return result;
            }

            int left = i + 1;
            int right = nums.size() - 1;

            // 对i进行去重
            if(i > 0 && nums[i] == nums[i-1]){
                continue;
            } 

            // 进行left与right的移动
            while (right > left) { 
                if(nums[i] + nums[left] + nums[right] > 0){
                    right --;
                } else if (nums[i] + nums[left] + nums[right] < 0)
                {
                    left ++;
                } else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            
            }
        
        }
        return result;
    }
};
```



## 18. 四数之和 [medium]

[18. 四数之和 - 力扣（LeetCode）](https://leetcode.cn/problems/4sum/)

**思路：**

同三数和一样，仅仅加了一个for循环（i， i+1 -> end, left & right -> mid）

**代码：**

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++) {
            // 剪枝处理
            if (nums[k] > target && nums[k] >= 0) {
            	break; // 这里使用break，统一通过最后的return返回
            }
            // 对nums[k]去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                // 2级剪枝处理
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }

                // 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if ((long) nums[k] + nums[i] + nums[left] + nums[right] > target) {
                        right--;
                    // nums[k] + nums[i] + nums[left] + nums[right] < target 会溢出
                    } else if ((long) nums[k] + nums[i] + nums[left] + nums[right]  < target) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        // 对nums[left]和nums[right]去重
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;

                        // 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }

            }
        }
        return result;
    }
};
```





之前做过的题：

数组：

[27.移除元素 [easy]](#27. 移除元素 [easy])

链表：

[206.翻转链表 [easy]](#206.翻转链表 [easy])

[19.删除链表的倒数第N个节点 [medium]](#19.删除链表的倒数第N个节点 [medium])

[160.相交链表 [easy]](#160.相交链表 [easy])

[142.环形链表Ⅱ [medium]](#142.环形链表Ⅱ [medium])

字符串：

[344.反转字符串 [easy]](#344.反转字符串 [easy])

[剑指Offer | 05. 替换空格 [easy]](#剑指Offer | 05. 替换空格 [easy])

[151. 翻转字符串里的单词 [medium]](#151. 翻转字符串里的单词 [medium])



## 总结

什么时候用双指针呢？

首先，用双指针的最底层思想就是用两个指针来避免嵌套的两层循环，一次循环中指两个位置。

可以首尾相向走，做反转等操作。也可以用快慢指针，用速差去做一些事情。如删除，慢指针指向待删除，快指针找到后面不删除的元素，进行覆写；或者用速差去找链表的环，环的入口。





# 栈与队列

## 基础知识

栈和队列是STL（C++标准库）里面的两个数据结构。

C++标准库是有多个版本的，要知道我们使用的STL是哪个版本，才能知道对应的栈和队列的实现原理。

那么来介绍一下，三个最为普遍的STL版本：

1. HP STL 其他版本的C++ STL，一般是以HP STL为蓝本实现出来的，HP STL是C++ STL的第一个实现版本，而且开放源代码。
2. P.J.Plauger STL 由P.J.Plauger参照HP STL实现出来的，被Visual C++编译器所采用，不是开源的。
3. SGI STL 由Silicon Graphics Computer Systems公司参照HP STL实现，被Linux的C++编译器GCC所采用，SGI STL是开源软件，源码可读性甚高。

接下来介绍的栈和队列也是SGI STL里面的数据结构， 知道了使用版本，才知道对应的底层实现。

来说一说栈，栈先进后出，如图所示：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210104235434905.png)

栈提供push 和 pop 等等接口，所有元素必须符合先进后出规则，所以栈不提供走访功能，也不提供迭代器(iterator)。 不像是set 或者map 提供迭代器iterator来遍历所有元素。

**栈是以底层容器完成其所有的工作，对外提供统一的接口，底层容器是可插拔的（也就是说我们可以控制使用哪种容器来实现栈的功能）。**

所以STL中栈往往不被归类为容器，而被归类为container adapter（容器适配器）。

那么问题来了，STL 中栈是用什么容器实现的？

从下图中可以看出，栈的内部结构，栈的底层实现可以是vector，deque，list 都是可以的， 主要就是数组和链表的底层实现。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210104235459376.png)

**我们常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。**

deque是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑了。

**SGI STL中 队列底层实现缺省情况下一样使用deque实现的。**

我们也可以指定vector为栈的底层实现，初始化语句如下：

```cpp
std::stack<int, std::vector<int> > third;  // 使用vector为底层容器的栈
```

刚刚讲过栈的特性，对应的队列的情况是一样的。

队列中先进先出的数据结构，同样不允许有遍历行为，不提供迭代器, **SGI STL中队列一样是以deque为缺省情况下的底部结构。**

也可以指定list 为起底层实现，初始化queue的语句如下：

```cpp
std::queue<int, std::list<int>> third; // 定义以list为底层容器的队列
```

所以STL 队列也不被归类为容器，而被归类为container adapter（ 容器适配器）。



## 232.用栈实现队列 [easy]

[232. 用栈实现队列 - 力扣（LeetCode）](https://leetcode.cn/problems/implement-queue-using-stacks/)

**思路：**

一个staIn用来写入，一个staOut用来读出。写入就正常写，读出的话需要将栈内元素反过来，那么就先将staIn中元素pop到staOut中（此时就反转了），再从staOut中pop。注意，当staOut为空时需要倒入staIn的东西，若不为空直接pop就好。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/232.用栈实现队列版本2.gif)

**代码：**

```c++
// @lc code=start
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    MyQueue() {
        
    }
    
    void push(int x) {
        stIn.push(x);
    }
    
    int pop() {
        if (stOut.empty()) {
            while(!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }
    
    int peek() {
        int res = this->pop(); // 直接使用已有的pop函数
        stOut.push(res); // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }
    
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end
```



## 225. 用队列实现栈 [easy]

[225. 用队列实现栈 - 力扣（LeetCode）](https://leetcode.cn/problems/implement-stack-using-queues/)

**思路：**

让队尾的人先买到票，怎么办呢？前面的人站一边去就好了。

所以，que1是正常队列，当要pop时，把que1除最后一个的其他元素都push到que2里，然后pop完最后一个人后，再将que2中的所有元素push回来。

请注意，队列间互相pop、push是不改变元素顺序的，大胆来。

**代码：**

```c++
class MyStack {
public:
    queue<int> que1; 
    queue<int> que2; // 用作que1的备份
    MyStack() {

    }
    
    void push(int x) {
        que1.push(x);
    }
    
    int pop() {
        int size = que1.size();
        size --;
        while (size --) {
            que2.push(que1.front());
            que1.pop();    
        }

        int result = que1.front();
        que1.pop();
        que1 = que2;
        while(!que2.empty()){
            que2.pop();
        }
        return result;
    }
    
    int top() {
        return que1.back();
    }
    
    bool empty() {
        return que1.empty() && que2.empty();
    }
};
```



## 20.有效的括号 [easy]

[20. 有效的括号 - 力扣（LeetCode）](https://leetcode.cn/problems/valid-parentheses/)

**思路：**

想清楚有不匹配时有几种情况：

1. 左括号多了
2. 右括号多了
3. 左右括号一样多，但是类型不对

有没有像消消乐的感觉？这也就是对称匹配问题，由于栈结构的特殊性，非常适合做对称匹配类的题目。

遍历字符串：当遇到左括号，就往栈里push进相应的右括号；当遇到右括号，就去消去栈顶相同的右括号。发现栈顶和当前遍历的括号类型不一？那就是情况3呗。此外，情况1的后果是字符串看完了，栈里还剩东西；情况2的后果是栈空了，字符串还没看完（又遇到新的右括号了）。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20.有效括号.gif)

**代码：**

```c++
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false; // 长度为奇数一定不符合要求
        stack<char> sta;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == '(') sta.push(')');
            else if(s[i] == '[') sta.push(']');
            else if(s[i] == '{') sta.push('}');
            else if (sta.empty() || sta.top() != s[i]) return false;
            else sta.pop();
        }
        return sta.empty();
    }
};
```



## 1047.删除字符串中的所有相邻重复项 [easy]

[1047. 删除字符串中的所有相邻重复项 - 力扣（LeetCode）](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/)

**思路：**

双消问题。比较栈顶与当前位置的字符是否相同，相同栈pop，不同栈push，遍历完后栈全部pop出来到新字符串，再来一个reverse。

改进一下，用一个双向队列，比较阶段在队尾操作，遍历完后队首pop，就省去了reverse操作了。

**注意，c++中空栈的top可不是null，而会报错。所以要做好判空，或是给栈底铺一层褥子（push一个不可能出现的元素）。**

**代码：**

```c++
class Solution {
public:
    string removeDuplicates(string s) {
        deque<char> que;
        for (int i = 0; i < s.size(); i++) {
            if (que.empty() || que.back() != s[i]) {
                que.push_back(s[i]);
            } else {
                que.pop_back();
            }
        }

        string result;
        while (!que.empty()) {
            result += que.front();
            que.pop_front();
        }

        return result;
    }
};
```



## 150. 逆波兰表达式求值 [medium]

[150. 逆波兰表达式求值 - 力扣（LeetCode）](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)

**思路：**

逆波兰表达式其实就是二叉树的后序遍历。可以通过以运算符作为中间节点，用后序遍历的规则画出二叉树。

但没必要真的用这个解，太麻烦了。思路还是用栈消消乐（就像上面那道题），由于题目给的例子都是严格按照算术式转换而来的逆波兰表达式，所有的算例都是正确的，所以不用判断各种意外情况。

具体来说，遍历tokens，遇到符号去取栈顶前两个数num1与num2，注意num2是被除数。

**代码：**

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> sta;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int num1 = sta.top();
                sta.pop();
                int num2 = sta.top();
                sta.pop();
                if (tokens[i] == "+") sta.push(num2 + num1);
                if (tokens[i] == "-") sta.push(num2 - num1);
                if (tokens[i] == "*") sta.push(num2 * num1);
                if (tokens[i] == "/") sta.push(num2 / num1);
            } else {
                sta.push(stoll(tokens[i]));
            }

        }
        return sta.top();
    }
};
```



## 239. 滑动窗口最大值 [hard]

[239. 滑动窗口最大值 - 力扣（LeetCode）](https://leetcode.cn/problems/sliding-window-maximum/)

> 第一个困难题，特此留念~

**思路：**

> 头好痒哦，感觉要长脑袋了 o.0

整破防了，看起来很简单但就是做不对。

这里用到的是单调队列。

**优先队列：**所有元素入队，按大小排序后的队列

**单调队列：**不一定所有元素都入队，push的时候要和把门的比较，比他大就把他换掉。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/239.滑动窗口最大值.gif)

以这个方式back_push，就能保证front始终为最大。那么如何解决滑出的元素呢？

窗口滑出，分为两种情况，第一种情况就是把最大值滑出去了，也就是滑出了que.front()，那就front_pop；若不是这个数，那大家就当无事发生。（小人物没人关注）

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/239.滑动窗口最大值-2.gif)

**代码：**

```c++
class Myque {
    public:
    deque<int> que;
    
    int front(){
        return que.front();
    }

    void pop(int value){
        if(!que.empty() && value == que.front()){
            que.pop_front();
        }
    }

    void push(int value){
        while(!que.empty() && value > que.back()){
            que.pop_back();
        }
        que.push_back(value);
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myque que;
        vector<int> res;
        for (int i = 0; i < k; i++){    
            que.push(nums[i]);
        }
        res.push_back(que.front());
        for (int i = k; i < nums.size(); i++)
        {
            que.pop(nums[i-k]);
            que.push(nums[i]);
            res.push_back(que.front());
        }
        
        return res;              
    }
};
```



## 347. 前-k-个高频元素 [medium]

[347. 前 K 个高频元素 - 力扣（LeetCode）](https://leetcode.cn/problems/top-k-frequent-elements/)

**思路：**

首先，遍历数组，用哈希表记录下每个数字的出现次数：map<nums[i], 次数>

接着，用大小为k的小顶堆过一遍这个map，则最终小顶堆剩下的元素就是排名前三的元素。

用优先级队列实现小顶堆，即定义一个比较函数，使得次数越小的数字优先级越高，在过map时就先被pop掉。

代码有些细节，注意看注释：

**代码：**

```c++
class Solution {
    // 小顶堆的排序方法
    class mycomparison {
        public:
            // 运算符重载
            // 参数1是比较者，参数2是被比较者，返回true说明参数1优先级高，也就是说，频率越大优先级越高
            // 乍一看这个逻辑反了，其实原因是优先级队列从队尾（优先级最小的）pop，所以和堆这个刚好反着来
            bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
                return lhs.second > rhs.second;
            }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计元素出现的频率，计入unordered_map:
        unordered_map<int, int> map;  // map<nums[i], 出现的次数>
        for (int i = 0; i < nums.size(); i++) {
            //使用 [] 运算符访问一个未出现在 std::unordered_map<int, int> 中的键会导致该键被插入到 std::unordered_map<int, int> 中，并将对应的值初始化为默认值，对于 int 类型的值，默认值为0。
            map[nums[i]]++;
        }

        // 对频率排序, 定义一个大小为k的小顶堆
        // 参数 1：pair<int, int>，表明该小顶堆的元素类型
        // 参数 2：vector<pair<int, int>>，底层容器的类型，这里使用 vector 作为底层容器
        // 参数 3：mycomparison， 比较函数的类型
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫遍所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if(pri_que.size() > k) {
                pri_que.pop();
            }
        }

        vector<int> result(k);
        for(int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }

        return result;
    }
};
```





# 二叉树

> 噔噔咚！

## 基础理论

[二叉树](https://www.sunnyx.cn/2022/06/15/数据结构与算法/#二叉树)

[二叉排序数](https://www.sunnyx.cn/2022/06/15/数据结构与算法/#二叉排序树)

[平衡二叉树](https://www.sunnyx.cn/2022/06/15/数据结构与算法/#平衡二叉树)

规范一下定义：

```c++
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

来了都是客，先写个遍历吧~



## 144. 二叉树的前序遍历 [easy]

[144. 二叉树的前序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-preorder-traversal/)

**思路：**

递归法就不谈了，说说迭代法

用栈，先入头节点，while(!stack.empty())就pop一个，然后若它的右孩子非空，push右；左孩子非空，push左。

**代码：**

递归：

```c++
class Solution {
public:
    void preorder(TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) {
            return;
        }
        res.push_back(cur -> val);
        preorder(cur -> left, res);
        preorder(cur -> right, res);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
};
```

迭代：

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> sta;
        if (root == nullptr) return res;
        sta.push(root);
        while (!sta.empty()) {
            TreeNode* node = sta.top();
            sta.pop();
            res.push_back(node->val);
            if(node->right) sta.push(node->right);
            if(node->left) sta.push(node->left);
        }
        return res;
    }
};
```



## 94. 二叉树的中序遍历 [easy]

**思路：**

递归法换个位置就行，迭代法上面的套路不行了。中序遍历是左中右，先访问的是二叉树顶部的节点，然后一层一层向下访问，直到到达树左面的最底部，再开始处理节点（也就是在把节点的数值放进result数组中），这就造成了**处理顺序和访问顺序是不一致的。**

那么**在使用迭代法写中序遍历，就需要借用指针的遍历来帮助访问节点，栈则用来处理节点上的元素。**

**代码：**

递归法

```c++
class Solution {
public:
    void inorder(TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) {
            return;
        }
        inorder(cur -> left, res);
        res.push_back(cur -> val);
        inorder(cur -> right, res);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
```

迭代法：

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != NULL || !st.empty()) {
            if (cur != NULL) { // 指针来访问节点，访问到最底层
                st.push(cur); // 将访问的节点放进栈
                cur = cur->left;                // 左
            } else {
                cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                st.pop();
                result.push_back(cur->val);     // 中
                cur = cur->right;               // 右
            }
        }
        return result;
    }
};
```



## 145. 二叉树的后续遍历 [easy]

[145. 二叉树的后序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-postorder-traversal/)

**思路：**

迭代法，先序遍历是中左右，后续遍历是左右中，那么我们只需要调整一下先序遍历的代码顺序，就变成中右左的遍历顺序，然后在反转result数组，输出的结果顺序就是左右中了

**代码：**

递归法：

```c++
class Solution {
public:
    void postorder(TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) {
            return;
        }
        postorder(cur -> left, res);
        postorder(cur -> right, res);
        res.push_back(cur -> val);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        postorder(root, res);
        return res;
    }
};
```

迭代法：

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == NULL) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->left) st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            if (node->right) st.push(node->right); // 空节点不入栈
        }
        reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
        return result;
    }
};
```



## 102. 二叉树的层序遍历 [medium]

[102. 二叉树的层序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-level-order-traversal/)

**思路：**

需要借用一个辅助数据结构即队列来实现，**队列先进先出，符合一层一层遍历的逻辑，而用栈先进后出适合模拟深度优先遍历也就是递归的逻辑。**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/102二叉树的层序遍历.gif)

**代码：**

队列：

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }
};
```

递归：

```c++
class Solution {
public:
    void order(TreeNode* cur, vector<vector<int>>& result, int depth)
    {
        if (cur == nullptr) return;
        if (result.size() == depth) result.push_back(vector<int>());
        result[depth].push_back(cur->val);
        order(cur->left, result, depth + 1);
        order(cur->right, result, depth + 1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        return result;
    }
};
```



## 266. 翻转二叉树 [easy]

[226. 翻转二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/invert-binary-tree/)

**思路：**

> 纯手写一次过，可喜可贺~

没啥难度，层序遍历，遍历到每一个节点，把它的左右子节点交换一下，入队继续。

也可用递归

**代码：**

队列：

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> que;
        if(root != nullptr){
            que.push(root);
        }
        
        while(!que.empty()) {
            TreeNode* cur = que.front();
            TreeNode* temp = cur->left;
            cur->left = cur->right;
            cur->right = temp;
            que.pop();
            if (cur->left != nullptr) {
                que.push(cur->left);
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
            }
        }
        return root;
    }
};
```

递归：

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr) return root;
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }
};
```



## 101. 对称二叉树 [easy]

[101. 对称二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/symmetric-tree/)

**思路：**

比较根节点左子树、右子树两个树的内侧与外侧元素是否相等：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210203144624414.png)

**正是因为要遍历两棵树而且要比较内侧和外侧节点，所以准确的来说是一个树的遍历顺序是左右中，一个树的遍历顺序是右左中。**

1. 确定递归的参数与返回值

   比较两颗子树，参数自然是子树的根，返回bool

2. 终止条件

   - 左节点为空，右节点不为空，不对称，return false
   - 左不为空，右为空，不对称 return false
   - 左右都为空，对称，返回true
   - 左右都不为空，比较节点数值，不相同就return false

   只有左右节点都有且都和另一边对称，才继续递归下去。

   ```c++
   if (left == NULL && right != NULL) return false;
   else if (left != NULL && right == NULL) return false;
   else if (left == NULL && right == NULL) return true;
   else if (left->val != right->val) return false; // 注意这里我没有使用else
   ```

3. 确定单层递归的逻辑

   - 比较二叉树外侧是否对称：传入的是左节点的左孩子，右节点的右孩子。
   - 比较内测是否对称，传入左节点的右孩子，右节点的左孩子。
   - 如果左右都对称就返回true ，有一侧不对称就返回false 。

   ```c++
   bool outside = compare(left->left, right->right);   // 左子树：左、 右子树：右
   bool inside = compare(left->right, right->left);    // 左子树：右、 右子树：左
   bool isSame = outside && inside;                    // 左子树：中、 右子树：中（逻辑处理）
   return isSame;
   ```

**代码：**

```c++
class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) {
        if (left == NULL && right != NULL) return false;
        else if (left != NULL && right == NULL) return false;
        else if (left == NULL && right == NULL) return true;
        else if (left->val != right->val) return false;

        bool outside = compare(left->left, right->right);
        bool inside = compare(left->right, right->left);
        bool isSame = outside && inside;
        return isSame;
    }

    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        return compare(root->left, root->right);
    }
};
```



## 104. 二叉树的最大深度 [easy]

**思路：**

解决二叉树，首先就想该按什么顺序遍历。这里我的第一想法其实是层序遍历，因为求深度，数有多少层就好了。事实证明——也确实可以。。。

还有一种想法时后序遍历，左右中，把左右看完，选一个最深的再+1，回溯到父节点，以此来计数。

**代码：**

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return 1 + max(leftDepth, rightDepth);
    }
};
```



## 111. 二叉树的最小深度 [easy]

[111. 二叉树的最小深度 - 力扣（LeetCode）](https://leetcode.cn/problems/minimum-depth-of-binary-tree/)

**思路：**

看似与最大深度一样，但差别还挺大的，比如下面这种情况：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210203155800503.png)

深度是根节点与叶子节点的距离，**叶子节点是没有左右子节点的节点！**

所以，如果左子树为空，右子树不为空，说明最小深度是 1 + 右子树的深度。

反之，右子树为空，左子树不为空，最小深度是 1 + 左子树的深度。 最后如果左右子树都不为空，返回左右子树深度最小值 + 1 。

左右子树都空，叶子节点，为递归的中止条件，return 0

**代码：**

```c++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right != NULL) {
            return 1 + minDepth(root->right);
        }
        if (root->left != NULL && root->right == NULL) {
            return 1 + minDepth(root->left);
        }
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};
```



## 222. 完全二叉树的节点个数 [medium]

[222. 完全二叉树的节点个数 - 力扣（LeetCode）](https://leetcode.cn/problems/count-complete-tree-nodes/)

**思路：**

完全二叉树是一种特殊的满二叉树，一个完全二叉树只有两种情况：就是满二叉树或最后一层叶子节点没满

满二叉树，直接2^树的深度-1来算

若当前节点不是满二叉树，则递归判断其左孩子与右孩子是否为满二叉树，**递归到某一深度一定会有左孩子或右孩子是满二叉树（单独的一个叶子节点就是满二叉树！）**，那么就可以按照情况一来算。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201124092543662.png)

**代码：**

```c++
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        int leftDepth = 0, rightDepth = 0;
        
        while (left) {
            left = left->left;
            leftDepth ++;
        } 

        while (right) {
            right = right->right;
            rightDepth++;
        }

        if (leftDepth == rightDepth) {
            return (2 << leftDepth) - 1;
        }

        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
```



## 110. 平衡二叉树 [easy]

**思路：**

后序遍历求高度（递归），因为后序从下往上遍历，所以能先遍历到那个不平衡的根节点，一旦发现某个根节点不平衡，直接返回-1表示已经结束咧！那么嵌套在这外面的递归也不求高度了，直接返回-1摆烂就好。如果没有发现当前节点不平衡，就老老实实求高度，往出走。

递归参数：当前节点

返回值：以当前节点为根节点的最大高度或-1

终止条件：当前节点为null，返回0；当前节点左右高度差大于1，返回-1；否则返回1+左右最大高度。

**代码：**

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftDepth = maxDepth(root->left);
        if(leftDepth == -1) return -1;
        int rightDepth = maxDepth(root->right);
        if(rightDepth == -1) return -1;
        if (abs(leftDepth - rightDepth) > 1) {
            return -1;
        } else {
            return 1 + max(leftDepth, rightDepth);
        }
        
    }

    bool isBalanced(TreeNode* root) {       
        return maxDepth(root) == -1 ? false : true;
    }
};
```



## 257. 二叉树的所有路径 [easy]

[257. 二叉树的所有路径 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-paths/)

**思路：**

前序遍历，到叶子节点，将已经遍历过（记录在数组中的）节点转换为字符串，出遍历，数组删除最后一个（这个节点被用完了），继续遍历。

> 所谓遍历的顺序，其实就是指业务代码在哪，如本道题业务代码为记录当前节点到数组，在遍历左右孩子之前，所以就是前序

**代码：**

```c++
class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
        // 记录当前节点
        path.push_back(cur->val);

        // 如果当前节点是叶子节点，就将path中的数据转换为string
        if (cur->left == nullptr && cur->right == nullptr) {
            string sPath;
            for(int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }

        // 当前节点有孩子，进孩子，直至到头，返回并删除孩子在path中的值（也就做到了回溯）
        if (cur->left) {
            traversal(cur->left, path, result);
            path.pop_back();
        }

        if (cur->right) {
            traversal(cur->right, path, result);
            path.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        if (root == nullptr) {
            return result;
        }
        traversal(root, path, result);
        return result;
    }
};
```



## 404. 左叶子之和 [easy]

[404. 左叶子之和 - 力扣（LeetCode）](https://leetcode.cn/problems/sum-of-left-leaves/)

**思路：**

递归到左叶子，累加。选择前序遍历，这样才能知道该节点是父节点的左孩子还是右孩子。参数给一个标志位表明cur与父节点的关系。

**代码：**

```c++
class Solution {
public:
    void preOrder(TreeNode* cur, bool isLeft, int& record) {
        if (cur == nullptr) { 
            return;
        }
        if (isLeft == true && cur->left == nullptr && cur->right == nullptr) {
            record += cur->val;
        }
        
        preOrder(cur->left, true, record); 
        preOrder(cur->right, false, record);
    }

    int sumOfLeftLeaves(TreeNode* root) {
        int record = 0;
        preOrder(root, false, record);
        return record;
    }
};
```



## 112. 路径总和 [easy]

[112. 路径总和 - 力扣（LeetCode）](https://leetcode.cn/problems/path-sum/)

**思路：**

与[257. 二叉树的所有路径 [easy]](#257. 二叉树的所有路径 [easy])这道题十分相似。257是找所有的路径，这道题是求路径的数值和。

所以整体遍历也参照257，前序遍历，不同的是，当找到一个解后，后面的遍历都不用做了，所以可以在传参中设计一个标志位isFind开绿灯。

**代码：**

```c++
class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
        // 记录当前节点
        path.push_back(cur->val);

        // 如果当前节点是叶子节点，就将path中的数据转换为string
        if (cur->left == nullptr && cur->right == nullptr) {
            string sPath;
            for(int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }

        // 当前节点有孩子，进孩子，直至到头，返回并删除孩子在path中的值（也就做到了回溯）
        if (cur->left) {
            traversal(cur->left, path, result);
            path.pop_back();
        }

        if (cur->right) {
            traversal(cur->right, path, result);
            path.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        if (root == nullptr) {
            return result;
        }
        traversal(root, path, result);
        return result;
    }
};
```



## 513. 找树左下角的值 [medium]

[513. 找树左下角的值 - 力扣（LeetCode）](https://leetcode.cn/problems/find-bottom-left-tree-value/)

**思路：**

层序遍历，在遍历每一层时记录该层的第一个元素，那么最后一定就是最有一层的第一个元素，也就是左下角的值。

**代码：**

```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> que;
        int result = 0;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode* node = que.front();
                que.pop();
                if (i == 0) result = node->val; // 记录每一层的第一个元素，最终就是最后一层的第一个元素
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return result;
    }
};
```



## 106. 从中序与后序遍历序列构造二叉树 [medium]

[106. 从中序与后序遍历序列构造二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)

**思路：**

首先从原理上如何实现这一需求——找根分左右，递归：

后续数组，其**最后的节点一定是前面所有节点的根节点**。那么**以后序数组的最后一个元素为切割点**（找根）去将中序分为左右两个数组（分左右），左中就是根节点左边的元素，右中即根节点右边的元素。

接着，后序数组也删除最后的元素，则并也分左右，如何分？**后序数组右子树一定在左子树的后面**，那么只需按照前面分好的左中与右中的长度去分就好。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210203154249860.png)

什么时候中止？该节点为叶子节点（也就是后序数组只有一个元素）时停止，返回该节点，作为外层递归所取节点的左/右孩子。

**代码：**

```c++
class Solution {
public:
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
        // 第一步：
        if (postorder.size() == 0) return nullptr;

        // 第二步：后序数组最后一个元素当作中序数组分割点
        int rootValue = postorder[postorder.size() - 1];
        TreeNode* root = new TreeNode(rootValue);

        // 叶子节点（终止条件）
        if (postorder.size() == 1) return root;

        // 第三步：找切割点
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex ++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        // 第四步：切割中序数组，得到中序左数组与中序右数组，左闭右开
        // [0, delimiterIndex)
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        // [delimiterIndex, end)
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        
        // 第五步：切割后序数组，得到后序左数组与后序右数组，左闭右开
        // 去掉最后一个元素，按照左右中序数组的大小来切割
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

        // 第六步：进入递归
        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);

        return root;

    }

    TreeNode* buildTree (vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 || postorder.size() == 0) return nullptr;
        return (traversal(inorder, postorder));
    }
};
```



## 105. 从前序与中序遍历序列构造二叉树 [easy]

[105. 从前序与中序遍历序列构造二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

**思路：**

和105一样，只不过分割点从后序的最后一个变成了前序的第一个。

> **前序和后序不能唯一构成一棵二叉树！！**

**代码：**

```c++
class Solution {
public:
    TreeNode* traversal(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;

        int rootValue = preorder[0];
        TreeNode* root = new TreeNode(rootValue);

        if (preorder.size() == 1) return root;

        // 找切割点
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex ++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        // 切割中序数组，得到中序左数组与中序右数组，左闭右开
        // [0, delimiterIndex)
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        // [delimiterIndex, end)
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());
        
        // 切割后序数组，得到后序左数组与后序右数组，左闭右开
        // 去掉第一个元素，按照左右中序数组的大小来切割
        vector<int> newarr(preorder.begin() + 1, preorder.end());
        vector<int> leftPreorder(newarr.begin(), newarr.begin() + leftInorder.size());
        vector<int> rightPreorder(newarr.begin() + leftInorder.size(), newarr.end());

        // 进入递归
        root->left = traversal(leftPreorder, leftInorder);
        root->right = traversal(rightPreorder, rightInorder);

        return root;

    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(inorder.size() == 0 || preorder.size() == 0) return nullptr;
        return (traversal(preorder, inorder));
    }
};
```



## 654. 最大二叉树 [medium]

[654. 最大二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/maximum-binary-tree/)

**思路：**

和上两题很像，前序遍历构造，从数组中找出最大的，左边的进递归构造左子树，右边同理。

**代码：**

```c++
class Solution {
public:
    // 找出数组中最大元素的下标
    int findMaxIdx (vector<int> nums) {
        auto max_it = max_element(nums.begin(), nums.end());
        return distance(nums.begin(), max_it);
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) return nullptr;

        TreeNode* node;
        int maxIdx;
        // 找到当前数组最大值，建立节点
        if (nums.size() > 1) {
            maxIdx = findMaxIdx(nums);
            node = new TreeNode(nums[maxIdx]);
        } else {
            node = new TreeNode(nums[0]);
            return node;
        } 


        // 左：[begin, maxIdx)
        vector<int> leftNums(nums.begin(), nums.begin() + maxIdx);
        // 右：[maxIdx + 1, end)
        vector<int> rightNums(nums.begin() + maxIdx + 1, nums.end());

        // 在左数组上构建左子树
        node->left = constructMaximumBinaryTree(leftNums);
        // 在右数组上构建右子树
        node->right = constructMaximumBinaryTree(rightNums);

        return node;
    }
};
```



## 617. 合并二叉树 [easy]

[617. 合并二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/merge-two-binary-trees/)

**思路：**

同时遍历两个二叉树，其中root1为主树，改变在其身上进行。遍历过程中可能会遇到以下几种情况：

- 两个cur同时时nullptr，说明到头啦，return nullptr;
- cur1有cur2无，cur2给一个新的空节点（防止空指针），cur1值不变
- cur1无cur2有，cur1给一个新的节点，值为cur2
- 两个都有，直接加到cur1

**代码：**

```c++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) {
            return nullptr;
        }
        
        if (root1 == nullptr) {
            root1 = new TreeNode(0 + root2->val);
        } else if (root2 != nullptr) {
            root1->val += root2->val;
        } else {
            root2 = new TreeNode();
        }
        
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;     

    }
};
```



## 700. 二叉搜索树中的搜索 [easy]

[700. 二叉搜索树中的搜索 - 力扣（LeetCode）](https://leetcode.cn/problems/search-in-a-binary-search-tree/)

**思路：**

没啥讲的，记着二叉搜索树左<中<右就行

**代码：**

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr || root->val == val) return root;
        if (root->val > val) return searchBST(root->left, val);
        if (root->val < val) return searchBST(root->right, val);
        return nullptr;
    }
};
```



## 98. 验证二叉搜索树 [medium]

[98. 验证二叉搜索树 - 力扣（LeetCode）](https://leetcode.cn/problems/validate-binary-search-tree/)

**思路：**

> 这为啥也能medium？

**二叉排序树**或是空树，或是满足如下性质的二叉树：

1. 若其**左子树**非空，则左子树上所有结点的值均**小于根结点**的值；
2. 若其**右子树**非空，则右子树上所有结点的值均**大于等于根结点**的值；
3. 其左右子树本身又是一颗二叉排序树

4. **二叉排序树的中序遍历数组一定是递增数列！**

不能单纯比较根节点与左右孩子的大小关系，应该用递归的方法去判断左右子树是否为二叉搜索树，直至走到空节点（空节点也是二叉搜索树，遂反true）。

由于这里我们一旦找到一个节点不符合条件，就直接跳过接下来所有循环，故需要有返回值记录深层循环的状态。

由于题目中节点可能会达到int最小值，所以我们用longlong maxVal最小值作为比较值的初始化：当前节点值大于maxVal，更新maxVal，继续遍历；否则直接返回true跳过接下来的遍历。

**代码：**

```c++
class Solution {
public:
    long long maxVal = LONG_MIN;
    
    bool isValidBST(TreeNode* root) {    
        if (root == nullptr) return true;

        bool left = isValidBST(root->left);
        if (root->val > maxVal) maxVal = root->val;
        else return false;
        bool right = isValidBST(root->right);
        return left && right;
    }
};
```



## 530. 二叉搜索树的最小绝对差 [easy]

[530. 二叉搜索树的最小绝对差 - 力扣（LeetCode）](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/)

**思路：**

排序二叉树，与当前节点差值最小的，只能是中序遍历的上一个节点（中序遍历是递增数组~）

在递归中，我们需要一个全局变量去记录该节点的上一个节点pre。注意，不是从总根节点开始记，而是从中序的开始，也就是左下角节点开始记。所以pre的更新也要放在中序处理。

**代码：**

```c++
class Solution {
public:
    int result = __INT_MAX__;
    TreeNode* pre = nullptr;
    void traversal (TreeNode* cur) {
        if (cur == nullptr) return;

        traversal(cur->left);
        if (pre != nullptr) result = min(result, cur->val - pre->val);
        pre = cur;
        traversal(cur->right);
    }
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;        
    }
};
```



## 501.二叉搜索树中的众数 [easy]

[501. 二叉搜索树中的众数 - 力扣（LeetCode）](https://leetcode.cn/problems/find-mode-in-binary-search-tree/)

**思路：**

若是一般树，思路是：遍历一遍，用map记录数值与出现的次数，再转换成vector\<pair>进行排序，选择最pair.second最大的那些项的pair.first。

排序二叉树，由于中序遍历是递增数列，所以只需与中序的前面一个节点比较是否一致即可。

若一致，count ++，若count与当前maxCount相等，将当前val录入数组；若count比maxCount大，则清空数组，重新录入当前val并更新maxCount。

**代码：**

```c++
class Solution {
public:
    TreeNode* pre = nullptr;
    int maxCount = 0;
    int count = 0;
    void traversal (TreeNode* cur, vector<int>& res) {
        if (cur == nullptr) return;

        traversal(cur->left, res);

        if(pre == nullptr) {
            count = 1;
            res.push_back(cur->val);
            maxCount = 1;
        } else {
            if (cur->val == pre->val) count ++;
            else count = 1;

            if (count > maxCount) {
                    res.clear();
                    res.push_back(cur->val);
                    maxCount = count;
                }
            else if (count == maxCount) {
                res.push_back(cur->val);
            }

        }
        pre = cur;

        traversal(cur->right, res);

        return;
    }

    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
```



## 236. 二叉树的最近公共祖先 [medium]

[236. 二叉树的最近公共祖先 - 力扣（LeetCode）](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)

**思路：**

找公共祖先，首先想到从下往上找爹，也就是回溯思想。后序遍历就是天然的回溯过程。

所以，我们仅需通过后序遍历去查找该节点的子树（包括自身）有无两个目标？若两个都有，则返回root；若仅有一个，则返回子树中的目标节点（反正不是空），但另一个子树还是空，所以继续向上走。

题目保证一定是有两个目标点的，那么就可以说，第一个左右出来不是null的父节点就是最近公共祖先咯。

> cpu有点烧，看下面的图自己推一推吧

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/202102041512582.png)

**代码：**

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == q || root== p || root == nullptr) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        // 在左子树与右子树分别找到了目标
        if (left != NULL && right != NULL) return root;
        
        // 仅在右子树找到目标
        if (left == NULL && right != NULL) return right;

        // 仅在左子树找到目标
        else if (left != NULL && right == NULL) return left;

        // 没有目标
        else return nullptr;
        
    }
};
```



## 235. 二叉搜索树的最近公共祖先 [medium]

[235. 二叉搜索树的最近公共祖先 - 力扣（LeetCode）](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/)

**思路：**

由于二叉搜索树具有有序性，就不用后序遍历了，而是从上到下，遇到的第一个落在[p, q]区间内的结点就一定是p、q的最近公共祖先。

一定是嘛？仔细想想，落到的第一个在[p, q]区间内的结点，**可以保证p、q分别在其左右子树上**，而不是在同一边（因为是排序树！），所以如果再往下找，就一定是向左或向右，就会错过一个结点。

**代码：**

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else return root;
    }
};
```



## 701. 二叉搜索树中的插入操作 [medium]

> 不该medium的

[701. 二叉搜索树中的插入操作 - 力扣（LeetCode）](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)

**思路：**

很基础的搜索二叉树插入操作，原先在手写搜索二叉树时已经实现过。

首先明确，插入结点一定是空结点，也就是遍历到某个叶子节点的子结点了，发现空再插入。遍历方向由插入值与当前节点值大小决定：当前结点值比插入值大，就遍历左子树，反之遍历右子树，直至空节点。

注意，在给空节点赋值时，我一开始直接

```c++
if (root == nullptr) root = new TreeNode(val);
```

结果发现new的变量（在堆区）在函数执行完后会被释放掉，无法有效赋值。

所以正确的赋值方法应该是return到上一层赋值，如下：

**代码：**

```c++
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) return new TreeNode(val);
        else if (root->val > val) root->left = insertIntoBST(root->left, val);
        else root->right = insertIntoBST(root->right, val);
        return root;
    }
};
```



## 450.删除二叉搜索树中的节点 [medium]

[450. 删除二叉搜索树中的节点 - 力扣（LeetCode）](https://leetcode.cn/problems/delete-node-in-a-bst/)

**思路：**

五种情况：

1. 树中根本无待删除结点：表现为遍历到nullptr还没找到，那就直接返回nullptr
2. 待删除结点是叶子结点：直接删除(delete)
3. 待删除结点是只有左子树：左子树上位替代它
4. 待删除结点是只有右子树：右子树上位替代它
5. **待删除结点有左右子树：将左子树接到右子树最左结点的左孩子处，新右子树替代它**

知道情况5这个定理，就不难实现。要注意的还是和上题一样，要改变一个结点，不能给它的指针new一个新值（会释放掉），而是要返回新结点，由外层递归完成对孩子的赋值操作。

**代码：**

```c++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // 情况一：没有要删除的结点
        if (root == nullptr) return root;
        if (root->val == key) {
            // 情况二：删除的结点为叶子结点：直接删除
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }

            // 情况三：删除的结点仅有右孩子：删除，右孩子补位
            else if (root->left == nullptr && root->right != nullptr) {
                TreeNode* retNode = root->right;
                delete root;
                return retNode;
            }

            // 情况四：删除的结点仅有左孩子：删除，左孩子补位
            else if (root->left != nullptr && root->right == nullptr) {
                TreeNode* retNode = root->left;
                delete root;
                return retNode;
            }

            // 情况五：删除的结点有左右孩子：则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            // 并返回删除节点右孩子为新的根节点。
            else
            {
                // 找右子树的最左结点
                TreeNode* cur = root->right;
                while (cur->left)
                {
                    cur = cur->left;
                }
                cur->left = root->left;  // 给最左结点赋左孩子
                TreeNode* temp = root;  // 暂存一下原root，以便删除
                root = root->right; // 替换原root
                delete temp;
                return root;
            }
            
        }

        if (root->val > key) root->left = deleteNode(root->left, key);
        if (root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};
```



## 669. 修剪二叉搜索树 [medium]

[669. 修剪二叉搜索树 - 力扣（LeetCode）](https://leetcode.cn/problems/trim-a-binary-search-tree/)

**思路：**

前序遍历，遇到不符合的结点，用他的第一个符合的左、右子树根节点替代之

**代码：**

```c++
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr) return nullptr;
        // 如果root（当前节点）的元素小于low的数值，那么应该递归右子树，并返回右子树符合条件的头结点。
        if (root->val < low) {
            TreeNode* right = trimBST(root->right, low, high); 
            return right;
        }   
        // 如果root(当前节点)的元素大于high的，那么应该递归左子树，并返回左子树符合条件的头结点。
        if (root->val > high) {
            TreeNode* left = trimBST(root->left, low, high); // 寻找符合区间[low, high]的节点
            return left;
        }

        root->left = trimBST(root->left, low, high); // root->left接入符合条件的左孩子
        root->right = trimBST(root->right, low, high); // root->right接入符合条件的右孩子
        return root;

    }
};
```



## 108.将有序数组转换为二叉搜索树 [easy]

[108. 将有序数组转换为二叉搜索树 - 力扣（LeetCode）](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/)

**思路：**

有序数组构造搜索树，以中间结点作为根结点，并分割左右数组构建左右子树，这样一来，构建的二叉树自然就是平衡的，不用再来那些繁琐的操作（左旋右旋）。

如果数组长度为偶数，中结点为两个，那么选哪个都行，因为构造的二叉树答案不唯一。

**代码：**

```c++
class Solution {
public:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + ((right - left) / 2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1);
        return root;
    }
};
```



## 538. 把二叉搜索树转换为累加树 [medium]

[538. 把二叉搜索树转换为累加树 - 力扣（LeetCode）](https://leetcode.cn/problems/convert-bst-to-greater-tree/)

**思路：**

搜索二叉树可以写成一个有序数组，有序数组累加就很简单了：从后往前走，前一个就等于本身+后面一个。

有序数组是中序遍历的结果，那么从后往前走自然就是二叉树的反中序遍历：右中左。

使用一个变量pre去记录下一层遍历的值，然后cur->val + pre就好。

**代码：**

```c++
class Solution {
public:
    int pre = 0;
    void traversal(TreeNode* cur) {
        if (cur == nullptr) return;
        traversal(cur->right);
        cur->val += pre;
        pre = cur->val;
        traversal(cur->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        pre = 0;
        traversal(root);
        return root;
    }
};
```



# 回溯算法 

## 基础理论

回溯法也可以叫做回溯搜索法，它是一种搜索的方式。其实在前面二叉树的学习中已经大量用到了回溯的思想，回溯是递归的副产品，有递归就会有回溯。

回溯算法的时间复杂度并不低，本质还是遍历，一般适用于如下几种问题：

- 组合问题：N个数里面按一定规则找出k个数的集合
- 切割问题：一个字符串按一定规则有几种切割方式
- 子集问题：一个N个数的集合里有多少符合条件的子集
- 排列问题：N个数按一定规则全排列，有几种排列方式（排列有序）
- 棋盘问题：N皇后，解数独等等

从本质来讲，**回溯法解决的问题都可以抽象为树形结构**，因为回溯法解决的都是在集合中递归查找子集，**集合的大小就构成了树的宽度，递归的深度，都构成的树的深度**。

以下给出回溯问题的模板（与递归三部曲相似）：

1. 回溯函数模板返回值以及参数

   回溯算法中函数返回值一般为void。

   再来看一下参数，因为回溯算法需要的参数可不像二叉树递归的时候那么容易一次性确定下来，所以一般是先写逻辑，然后需要什么参数，就填什么参数。

   ```c++
   void backtracking(参数)
   ```

2. 终止条件

   同递归一样，回溯也需要一个终止条件，这个比较灵活：

   ```c++
   if (终止条件) {
       存放结果;
       return;
   }
   ```

3. 回溯搜索遍历的过程

   在上面我们提到了，回溯法一般是在集合中递归搜索，集合的大小构成了树的宽度，递归的深度构成的树的深度。

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210130173631174.png)

   ```c++
   for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
       处理节点;
       backtracking(路径，选择列表); // 递归
       回溯，撤销处理结果
   }
   ```

   for循环就是遍历集合区间，可以理解一个节点有多少个孩子，这个for循环就执行多少次。

   backtracking这里自己调用自己，实现递归。

   大家可以从图中看出**for循环可以理解是横向遍历，backtracking（递归）就是纵向遍历**，这样就把这棵树全遍历完了，一般来说，搜索叶子节点就是找的其中一个结果了。

结合以上三步，给出回溯算法的一般模板：

```c++
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
```



## 77. 组合 [medium]

[77. 组合 - 力扣（LeetCode）](https://leetcode.cn/problems/combinations/)

**思路：**

经典题目，暴力遍历无法实现，因为要用k个循环，但k是变量。

用回溯思路，首先把题目抽象成树结构：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201123195223940.png)

每次从集合中选取元素，可选择的范围随着选择的进行而收缩，调整可选择的范围。图中可以发现n相当于树的宽度，k相当于树的深度。树的广度遍历用for循环，深度遍历就用递归。图中每次搜索到了叶子节点，我们就找到了一个结果。

**代码：**

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking (int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i <= n; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1); // 不满足k个，下层会进入for循环继续往后面pop；满足k个，下层进入终止条件录入result并返回。
            path.pop_back();
        } 
    }

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};
```



## 216. 组合总和III [medium]

[216. 组合总和 III - 力扣（LeetCode）](https://leetcode.cn/problems/combination-sum-iii/)

**思路：**

整体思路与上题类似，在1-9中选k个元素使其和为n。

前k-1个元素就按照上题的思路遍历，并记录当前路径前k-1个元素和sum。当path中有k-1个元素时进入终止条件，此时：如果在[startIndex, 10)区间内，存在n-sum这个元素，那么path最后一块拼图就找到了，世界加入path再将完整的path加入result即可。若没有这个元素，则说明这条路走不通，直接return试试别的路吧

**代码：**

```c++
class Solution {
private:
vector<vector<int>> result;
vector<int> path;

void backtracking (int n, int k, int startIndex) {
    if (path.size() == k - 1) {
        if (10 > n && n >= startIndex ) {
            path.push_back(n);
            result.push_back(path);
            path.pop_back();
            return;
        } else return;
    }

    // 注意这里的边界条件：由于内层递归一定比外层大，所以进行剪枝
    // 也就说，如果当前位置之后的元素个数（包括当前）少于所需元素个数，就不该继续搜索了
    // 例如：取三个元素，则第一层:[1, 7], 第二层[2, 8]，第三层[3, 9]
    for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {
        path.push_back(i);
        // n - i 实际记录了一路走下来的sum，换言之，在最后一层n-i这个元素就是最后一块拼图
        backtracking(n - i, k, i + 1);
        path.pop_back();
    }    
}

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(n, k, 1);
        return result;
    }
};
```



##  17.电话号码的字母组合 [medium]

[17. 电话号码的字母组合 - 力扣（LeetCode）](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/)

**思路：**

数字和字母如何映射？可以建立vector用数字-2代表下标进行映射，也可建立map

回溯思想：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201123200304469.png)

**代码：**

```c++
class Solution {
public:
    string path;
    vector<string> result;
    const vector<string> alph = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void backtracking(string digits, int curIndex) {
        if (path.length() == digits.length()) {
            result.push_back(path);
            return;
        }
        string curAlph = alph[(int)digits[curIndex] - 50];
        for (int i = 0; i < curAlph.length(); i ++) {
            path.push_back(curAlph[i]);
            backtracking(digits, curIndex + 1); // idx + 1不会超出边界，因为当path与digits一样长时就结束递归了
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.length() > 0) {
            backtracking (digits, 0);
        }
        return result;

```



## 39. 组合总和 [medium]



**思路：**

本题与[216. 组合总和III [medium]](#216. 组合总和III [medium])的区别在于：本题数字可以重复，且无长度限制。

所以本题的树形思路抽象如下：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201223170730367.png)

注意图中叶子节点的返回条件，因为本题没有组合数量要求，仅仅是总和的限制，所以递归没有层数的限制。这里只要当前层前面的sum加上当前层的元素大于target，就跳出for循环。

关于剪枝操作，在前文也以提及，不再赘述。

**代码：**

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0);
        return result;        
    }
};
```



## 40. 组合总和Ⅱ [medium]

[40. 组合总和 II - 力扣（LeetCode）](https://leetcode.cn/problems/combination-sum-ii/)

**思路：**

与39题的区别在于：

1. 本题candidates 中的每个数字在每个组合中只能使用一次。
2. 本题数组candidates的元素是有重复的，而是39题无重复元素的数组candidates

数组中有重复，解集中就会出现重复项，要去重。去重的原则是：同一层不取一样的，不同层可取一样的：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201123202817973.png)

这里选用一个bool类型的vector记录数组中相应位置元素是否已经被使用：false表示可以在同一层被使用，该跳过当前的for循环continue；true表示在上一层被使用，可继续使用。

**代码：**

```c++
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex, vector<bool>& used) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            // used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
            // used[i - 1] == false，说明同一树层candidates[i - 1]使用过
            // 要对同一树层使用过的元素进行跳过
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
                continue;
            }
            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target, sum, i + 1, used); // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size(), false);
        path.clear();
        result.clear();
        // 首先把给candidates排序，让其相同的元素都挨在一起。
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, used);
        return result;
    }
};
```



## 131. 分割回文串 [medium]

[131. 分割回文串 - 力扣（LeetCode）](https://leetcode.cn/problems/palindrome-partitioning/)

**思路：**

其实难点在于如何把这个问题抽象成树结构？

其实切割问题类似于组合问题，例如对于abcdef：

- 组合问题：选取一个a之后，在bcdef中再去选取第二个，选取b之后在cdef中再选取第三个.....
- 切割问题：切割一个a之后，在bcdef中再去切割第二段，切割b之后在cdef中再切割第三段.....

**切割问题是切割点的组合！**

那么，就可以抽象成如下树结构：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/131.分割回文串.jpg)

至于如何判断切下来的字符串是回文？双指针两头比较即可。

**代码：**

```c++
class Solution {
private:
    vector<vector<string>> result;
    vector<string> path; // 放已经回文的子串
    void backtracking (const string& s, int startIndex) {
        // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome(s, startIndex, i)) {   // 是回文子串
                // 获取[startIndex,i]在s中的子串
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            } else {                                // 不是回文，跳过
                continue;
            }
            backtracking(s, i + 1); // 寻找i+1为起始位置的子串
            path.pop_back(); // 回溯过程，弹出本次已经填在的子串
        }
    }
    bool isPalindrome(const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        backtracking(s, 0);
        return result;
    }
};
```



## 93. 复原IP地址 [medium]

[93. 复原 IP 地址 - 力扣（LeetCode）](https://leetcode.cn/problems/restore-ip-addresses/)

**思路：**

与上题类似，对于分割点的组合。但这里只允许有三个分割点，要记录分割点的数量pointNum， =3时就验证最后一部分，若符合要求就找到了一组分割点。

另外，在for循环中，随着i的增长，分割出的子串一旦不符合要求，就直接break，后面的不用看了。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201123203735933.png)

最后，如何判断是否为有效子串有些技巧，详见代码。

**代码：**

```c++
class Solution {
private:
    vector<string> result;
    // 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

    void backtracking (string& s, int startIndex, int pointNum) {
        if (pointNum == 3) {
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
            } else return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1 , '.');
                pointNum ++;
                backtracking(s, i + 2, pointNum);
                pointNum --;
                s.erase(s.begin() + i + 1);
            } else break;
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12) return result; // 算是剪枝了
        backtracking(s, 0, 0);
        return result;
    }
};
```



## 78. 子集 [medium]

[78. 子集 - 力扣（LeetCode）](https://leetcode.cn/problems/subsets/)

**思路：**

很正常的思路

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/202011232041348.png)

**代码：**

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        if (startIndex == nums.size()) return;
        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
```



## 90.子集II [medium] 

[90. 子集 II - 力扣（LeetCode）](https://leetcode.cn/problems/subsets-ii/)

**思路：**

在上一题的基础上增加了去重操作，思路与[40. 组合总和Ⅱ [medium]](#40. 组合总和Ⅱ [medium])完全一样，在for循环中以vector\<bool> used去标志每个元素有无被使用过。

**代码：**

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking(vector<int>& nums, int startIndex, vector<bool> used) {
        result.push_back(path);
        if (startIndex == nums.size()) return;
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backtracking(nums, 0, used);
        return result;
    }
};
```



## 491.递增子序列 [medium]

[491. 递增子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/non-decreasing-subsequences/)

**思路：**

很像上面一道题，看似只需加一个“当前元素大于等于path.back”就行了？

实则不然，用上面那种vector\<bool>数组记录某个元素在当前层有无用过的前提是：nums是事先排好序的，一样的元素都挨在一起了。而本题是不允许改变原数组的。

所以，用哈希表来记录某个元素在当前层是否用过，而在每一层，该哈希表会重置。这里用数组这种哈希结构比较省时省力一些。

> 程序运行的时候对unordered_set 频繁的insert，unordered_set需要做哈希映射（也就是把key通过hash function映射为唯一的哈希值）相对费时间，而且每次重新定义set，insert的时候其底层的符号表也要做相应的扩充，也是费事的。

![491. 递增子序列1](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201124200229824.png)

另外要注意终止条件：本题其实类似求子集问题，也是要遍历树形结构找每一个节点，可以不加终止条件，startIndex每次都会加1，并不会无限递归。

**代码：**

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking(vector<int>& nums, int startIndex) {
        if (path.size() > 1) {
            result.push_back(path);
        }
        
        int used[201] = {0}; // 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) {
                    continue;
            }
            used[nums[i] + 100] = 1; // 记录这个元素在本层用过了，本层后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
```



## 46. 全排列 [medium]

[46. 全排列 - 力扣（LeetCode）](https://leetcode.cn/problems/permutations/)

**思路：**

排列问题，不需要startIndex了，因为排列是有序的。只需在一个path中将已经用过的元素过滤掉即可。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20211027181706.png)

这里我们选择used数组标记当前路径已经用过的元素。

终止条件为path.size() == nums.size()

**代码：**

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking (vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }

    }  
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
```



## 47. 全排列II [medium]

[47. 全排列 II - 力扣（LeetCode）](https://leetcode.cn/problems/permutations-ii/)

**思路：**

在上题基础上，加入了for层去重，去重思路与[491.递增子序列 [medium]](#491.递增子序列 [medium])中所用到的如出一辙。

**代码：**

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void backtracking (vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        int usedFor[20] = {0};
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true || usedFor[nums[i] + 10] == 1) continue;
            path.push_back(nums[i]);
            usedFor[nums[i] + 10] = 1;
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }

    }  
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
```



## 332. 重新安排行程 [hard]

[332. 重新安排行程 - 力扣（LeetCode）](https://leetcode.cn/problems/reconstruct-itinerary/)

**思路：**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/2020111518065555.png)

1. 如何记录映射关系？

   一个出发机场与一个到达机场为一段路径，那么自然想到了`map<string, string>`，但注意，同一个机场可能即是出发机场又是到达机场，那么这样就有可能进入死循环路径。所以这里用`unordered_map<string, map<string, int>>`来记录，意为<出发机场, <到达机场，到达机场的使用次数>>。首先，在初始化该map时，记录每个机场出现了几次，然后循环中每循环一次就-1，如果到0就说明该机场的使用次数用完了。该映射初始化如下所示：

   ```c++
   for (const vector<string>& vec : tickets) {
       targets[vec[0]][vec[1]]++; // 记录映射关系
   }
   result.push_back("JFK"); // 起始机场
   ```

2. 如何保证字典顺序？

   注意咯，target的value是一个map，map是有序的。这也就是说，当一个出发机场对应多个到达机场时，会将多个到达机场进行排序。

3. 为什么有返回值？

   因为找到一条path就直接当作答案咯，不用遍历整棵树

**代码：**

> 我抄的，我做不出来555 TAT

```c++
class Solution {
private:
    //<出发机场, map<到达机场, 航班次数>> target
    unordered_map<string, map<string, int>> targets;
    bool backtracking(int ticketNum, vector<string>& result) {
        if(result.size() == ticketNum + 1) {
            return true;
        }
        // result[result.size() - 1]指上一次到达的机场（起始机场为JFK）
        for (pair<const string, int>& target : targets[result[result.size() - 1]]) {
            if (target.second > 0) {
                result.push_back(target.first);
                target.second --;
                if (backtracking(ticketNum, result)) return true;
                result.pop_back();
                target.second ++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> result;
        for (const vector<string>& vec : tickets) {
            targets[vec[0]][vec[1]]++;
        }
        result.push_back("JFK");
        backtracking(tickets.size(), result);
        return result;
    }
};
```



## 51. N皇后 [hard]

[51. N 皇后 - 力扣（LeetCode）](https://leetcode.cn/problems/n-queens/)

**思路：**

for—>行，递归—>列，如下：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210130182532303.jpg)

终止条件：走到叶子结点，也就是row == n

如何判断是否可放？最朴实的想法，检查列，以及四个方向的斜边。

**代码：**

```c++
class Solution {
private:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string>& chessboard) {
        if (row == n) {
            result.push_back(chessboard);
            return;
        }

        for(int col = 0; col < n; col ++) {
            if (isValid(row, col, chessboard, n)) {
                chessboard[row][col] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

    bool isValid (int row, int col, vector<string>& chessboard, int n) {
        // 检查列
        for (int i = 0; i < row; i++) {
            if (chessboard[i][col] == 'Q') return false;
        }

        // 检查第一象限
        for (int i = row, j = col; i >= 0 && j < n ;i--, j++ ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第二象限
        for (int i = row, j = col; i >= 0 && j >= 0 ;i--, j-- ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第三象限
        for (int i = row, j = col; i < n && j >= 0 ;i++, j-- ) {
            if (chessboard[i][j] == 'Q') return false; 
        }

        // 检查第四象限
        for (int i = row, j = col; i < 0 && j < 0 ;i++, j++ ) {
            if (chessboard[i][j] == 'Q') return false; 
        }    

        return true;    
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};
```



## 37. 解数独 [hard]

[37. 解数独 - 力扣（LeetCode）](https://leetcode.cn/problems/sudoku-solver/)

**思路：**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/2020111720451790.png)

返回值：bool，因为只需找一条path

终止条件：无，找到叶子结点自动返回。如何知道是叶子结点？递归的下一层棋盘比上一层棋盘多一个数，那棋盘满了（row，col都到了8）问题就会终止。

会不会有始终填不满的情况？不会，九个数试完直接返回false，表示当前棋盘无解。

**代码：**

```c++
class Solution {
private:
    bool backtracking(vector<vector<char>>& board) {
        for(int row = 0; row < board.size(); row++) {
            for (int col = 0; col < board[0].size(); col++){
                if (board[row][col] == '.'){
                    for (char k = '1'; k <= '9'; k++) {
                        if(isValid(row, col, k, board)) {
                            board[row][col] = k;
                            if (backtracking(board)) return true; // 如果找到合适的就立刻返回
                            board[row][col] = '.';
                        }
                    }
                    return false; // 9个数试完了都不行，返回false
                }
            }
        }
        return true;
    }

    bool isValid(int row, int col, char k, vector<vector<char>>& board) {
        // row[0, 8]  col[0, 8]
        // 检查行
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == '.') continue;
            if (board[row][i] == k) return false;
        }

        // 检查列
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == '.') continue;
            if (board[i][col] == k) return false;
        }

        // 检查3x3
        int startRow = 3 * (row / 3);
        int startCol = 3 * (col / 3);
        for (int i = startRow; i < startRow + 3; i++){
            for (int j = startCol; j < startCol + 3; j++){
                if (board[i][j] == '.') continue;
                if (board[i][j] == k) return false;
            }
        }
        
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};
```



# 贪心算法

## 基础理论

### 什么是贪心？

**贪心的本质是选择每一阶段的局部最优，从而达到全局最优**。

例如，有一堆钞票，你可以拿走十张，如果想达到最大的金额，就每次拿最大的（局部最优），最终结果就是拿走最大数额的钱（全局最优）。

### 什么时候用贪心？

不好意思，没有固定套路。**手动模拟一下感觉可以局部最优推出整体最优，而且想不到反例，那么就试一试贪心**。

### 一般解题步骤

贪心算法一般分为如下四步：

- 将问题分解为若干个子问题
- 找出适合的贪心策略
- 求解每一个子问题的最优解
- 将局部最优解堆叠成全局最优解

这个四步其实过于理论化了，我们平时在做贪心类的题目 很难去按照这四步去思考，真是有点“鸡肋”。

做题的时候，只要想清楚 局部最优 是什么，如果推导出全局最优，其实就够了。



## 455. 分发饼干 [easy]

[455. 分发饼干 - 力扣（LeetCode）](https://leetcode.cn/problems/assign-cookies/)

**思路：**

给每个孩子大于等于胃口值中最小的那个饼干即可。

两个数组先从小到大排序，然后根据以上规则看能满足到第几个孩子。

**代码：**

```c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0;
        int j = 0;
        while (i < g.size()){
            if (j >= s.size()) break;
            if (s[j] >= g[i]) {
                i++;
                j++;
            } else j++;
        }
        return i;
    }
};
```



## 376. 摆动序列 [medium]

[376. 摆动序列 - 力扣（LeetCode）](https://leetcode.cn/problems/wiggle-subsequence/)

**思路：**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201124174327597.png)

局部最优：删除单调坡度上的节点（不包括单调坡度两端的节点），那么这个坡度就可以有两个局部峰值。

整体最优：整个序列有最多的局部峰值，从而达到最长摆动序列。

**情况一：上下坡有平坡**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20230106172613.png)

在图中，当i指向第一个2的时候，`prediff > 0 && curdiff = 0` ，当 i 指向最后一个2的时候 `prediff = 0 && curdiff < 0`。

如果我们采用，删左面三个2的规则，那么 当 `prediff = 0 && curdiff < 0` 也要记录一个峰值，因为他是把之前相同的元素都删掉留下的峰值。

所以我们记录峰值的条件应该是： `(preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)`，为什么这里允许 prediff == 0 ，就是为了 上面我说的这种情况。

**情况二：数组首尾两端**

数组中仅有两个不同元素，那么结果为2。为了计算prediff与curdiff，需要三个数，这时给最前面（首部）或最后面（尾部）加一个与首尾一样大的数字，例如：[2, 5] -> [2, 2, 5]，那么根据情况一的规则，这个2也就算是峰值了。

**情况三：单调坡度有平坡**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20230108171505.png)

 图中，我们可以看出，版本一的代码在三个地方记录峰值，但其实结果因为是2，因为 单调中的平坡 不能算峰值（即摆动）。

之所以版本一会出问题，是因为我们实时更新了 prediff。

那么我们应该什么时候更新prediff呢？

我们只需要在 这个坡度 摆动变化的时候，更新prediff就行，这样prediff在 单调区间有平坡的时候 就不会发生变化，造成我们的误判。

**代码：**

```c++
class Solution {
private:

public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0;
        int preDiff = 0;
        int result = 1;
        for (int i = 0; i < nums.size() - 1; i++){
            curDiff = nums[i+1] - nums[i];
            if((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff;
            }
        }
        return result;
    }
};
```



## 53. 最大子序和 [medium]

[53. 最大子数组和 - 力扣（LeetCode）](https://leetcode.cn/problems/maximum-subarray/)

**思路：**

贪心：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/53.最大子序和.gif)

从第一个数字开始向后累加，当累加结果<0时，下一个元素从零开始加。这就是贪心算法的思路。

局部最优：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数加上下一个元素 “连续和”只会越来越小。

全局最优：选取最大“连续和”。

result初始化为int32的最小值，之后遇到比result大的sum，就更新result。这样就算是数组只有一个元素也可以正确输出该元素。

动规：

1. dp数组以及下标的含义

   dp[i]：以nums[i]结尾的最大子序和为dp[i]（注意：凡是题目涉及到连续，动规时就该考虑以第i位结尾，而不是[0, i]中有）

2. 确定递推公式

   就看dp[i - 1]加不加nums[i]，不加的话，就从nums[i]重新开始

   dp[i] = max(dp[i - 1] + nums[i], nums[i])。

   其实相当于如果dp[i - 1]都是负数了，那就丢掉从新开始咯

3. dp数组如何初始化

   dp[0] = nums[0]

4. 确定遍历顺序

   从左到右

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210303104129101.png)

**代码：**

贪心：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT32_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++){
            count += nums[i];
            if(count > result) {
                result = count;
            }
            if (count <= 0) count = 0;
        }
        return result;
    }
};
```

动规：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int result = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]); // 状态转移公式
            if (dp[i] > result) result = dp[i]; // result 保存dp[i]的最大值
        }
        return result;
    }
};
```



## 122. 买卖股票的最佳时机II [medium]

[122. 买卖股票的最佳时机 II - 力扣（LeetCode）](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)

**思路：**

贪心：

总利润是可以拆解为每天的利润之和的。那么，仅需要将每天为正数的利润加起来就可以了。

动规：

与[上一题](#121. 买卖股票的最佳时机 [easy])不同的地方在于递推公式。

dp\[i][0]，第i天买入股票，不再是0-prices[i]，而在更之前可能已经赚过一笔了，所以是dp\[i - 1][1] - prices[i]。除此之外其余都一样。

**代码：**

贪心：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sum = 0;
        for (int i = 0; i < prices.size() - 1; i++){
            if(prices[i + 1] - prices[i] > 0) {
                sum += prices[i + 1] - prices[i];
            }
        }
        return sum;
    }
};
```

动规：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], dp[0][1] - prices[i]);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0][0] = dp[1][0];
            dp[0][1] = dp[1][1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
```



## 55. 跳跃游戏 [medium]

[55. 跳跃游戏 - 力扣（LeetCode）](https://leetcode.cn/problems/jump-game/)

**思路：**

无需真正思考在当前格子上要走几步，只需判断：当前格子是否可以覆盖到终点即可。

每次移动取最大跳跃步数（得到最大的覆盖范围），每移动一个单位，就更新最大覆盖范围。

**贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点**。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201124154758229.png)

**代码：**

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        if (nums.size() == 1) return true; // 只有一个元素，就是能达到
        for (int i = 0; i <= cover; i++) { // 注意这里是小于等于cover
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) return true; // 说明可以覆盖到终点了
        }
        return false;
    }
};
```



## 45. 跳跃游戏II [medium]

[45. 跳跃游戏 II - 力扣（LeetCode）](https://leetcode.cn/problems/jump-game-ii/)

**思路：**

解题的时候，要从覆盖范围出发，不管怎么跳，覆盖范围内一定是可以跳到的，以最小的步数增加覆盖范围，覆盖范围一旦覆盖了终点，得到的就是最小步数！

这里需要统计两个覆盖范围，当前这一步的最大覆盖和下一步最大覆盖。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201201232309103.png)

**代码：**

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int curDistance = 0;    // 当前覆盖最远距离下标
        int ans = 0;            // 记录走的最大步数
        int nextDistance = 0;   // 下一步覆盖最远距离下标
        for (int i = 0; i < nums.size(); i++) {
            nextDistance = max(nums[i] + i, nextDistance);  // 更新下一步覆盖最远距离下标
            if (i == curDistance) {                         // 遇到当前覆盖最远距离下标
                if (curDistance < nums.size() - 1) {       // 如果当前覆盖最远距离下标不是终点
                    ans++;                                  // 需要走下一步
                    curDistance = nextDistance;             // 更新当前覆盖最远距离下标（相当于加油了）
                    if (nextDistance >= nums.size() - 1) break; // 下一步的覆盖范围已经可以达到终点，结束循环
                } else break;                               // 当前覆盖最远距到达集合终点，不用做ans++操作了，直接结束
            }
        }
        return ans;
    }
};
```



## 1005.K次取反后最大化的数组和 [easy]

[1005. K 次取反后最大化的数组和 - 力扣（LeetCode）](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/)

**思路：**

- 第一步：将数组按照绝对值大小从大到小排序，**注意要按照绝对值的大小**
- 第二步：从前向后遍历，遇到负数将其变为正数，同时K--
- 第三步：如果K还大于0，那么反复转变数值最小的元素，将K用完
- 第四步：求和

**代码：**

```c++
class Solution {
static bool cmp(int a, int b) {
    return abs(a) > abs(b);
}
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end(), cmp);       // 第一步
        for (int i = 0; i < A.size(); i++) { // 第二步
            if (A[i] < 0 && K > 0) {
                A[i] *= -1;
                K--;
            }
        }
        if (K % 2 == 1) A[A.size() - 1] *= -1; // 第三步
        int result = 0;
        for (int a : A) result += a;        // 第四步
        return result;
    }
};
```



## 134. 加油站 [medium]

[134. 加油站 - 力扣（LeetCode）](https://leetcode.cn/problems/gas-station/)

**思路：**

rest[i] = gas[i] - cost[i]

首先，rest[i]的全部元素和totalSum如果大于等于0，则说明一定有解。反之就返回-1

从0开始遍历累加rest[i]，记录于curSum，倘若走到第i个元素，curSum<0，则说明从第i个元素之前的所有元素都不可能为正确的解，应当从i+1开始重新累加curSum。

**局部最优：当前累加rest[i]的和curSum一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。全局最优：找到可以跑一圈的起始位置**。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20230117165628.png)

**代码：**

```c++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int resultIdx = 0;
        for(int i = 0; i < gas.size(); i++) {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if (curSum < 0) {
                curSum = 0;
                resultIdx = i + 1;
            }
        }

        if (totalSum < 0) return -1;

        return resultIdx;
    }
};
```



## 135. 分发糖果 [hard]

[135. 分发糖果 - 力扣（LeetCode）](https://leetcode.cn/problems/candy/)

**思路：**

1. 初始化`candyVec(ratings.size(), 1)`

2. 从前向后遍历，如果ratings[i] > ratings[i - 1] 那么[i]的糖 一定要比[i - 1]的糖多一个，所以贪心：candyVec[i] = candyVec[i - 1] + 1

   **这一步保证了只看左边，满足要求的最小量**

3. 从后往前遍历，如果 ratings[i] > ratings[i + 1]，此时candyVec[i] = max(candyVec[i + 1] + 1, candyVec[i]）

   candyVec[i]是只看左边，满足的最小量；candyVec[i + 1] + 1是只看右边，满足的最小量。如何选出一个同时满足左右的值？挑一个大的，就可以保证比左右都大了。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201117115658791.png)

**代码：**

```c++
class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candyVec(ratings.size(), 1);

        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) candyVec[i] = candyVec[i - 1] + 1;
        }

        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
            }
        }

        int result = 0;
        for (int i = 0; i < candyVec.size(); i++){
            result += candyVec[i];
        }
        return result;
    }
};

```



## 860. 柠檬水找零 [easy]

[860. 柠檬水找零 - 力扣（LeetCode）](https://leetcode.cn/problems/lemonade-change/)

**思路：**

情况非常少，可以模拟完所有情况：

- 情况一：账单是5，直接收下。
- 情况二：账单是10，消耗一个5，增加一个10
- 情况三：账单是20，优先消耗一个10和一个5，如果不够，再消耗三个5

为什么情况三优先消耗一个10块钱？**因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能！**这就是本题贪的体现了。

**代码：**

```c++
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (int bill : bills) {
            if (bill == 5) five ++;
            if (bill == 10) {
                if (five <= 0) return false;
                ten ++;
                five --;
            }
            if (bill == 20) {
                if (five > 0 && ten > 0) {
                    five --;
                    ten --;
                } else if (five >= 3){
                     five -= 3;
                } else return false;
            }
        }
        return true;
    }
};
```



##  406. 根据身高重建队列 [medium]

[406. 根据身高重建队列 - 力扣（LeetCode）](https://leetcode.cn/problems/queue-reconstruction-by-height/)

**思路：**

两个维度排序，一个一个来，不然顾此失彼。这里选择首先按身高排序，然后按k插入新数列。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201216201851982.png)

按照身高排序之后，优先按身高高的people的k来插入，后序插入节点也不会影响前面已经插入的节点，最终按照k的规则完成了队列。

**局部最优：优先按身高高的people的k来插入。插入操作过后的people满足队列属性**

**全局最优：最后都做完插入操作，整个队列满足题目队列属性**

------

还需要注意一个点，插入操作，链表比数组时性能好得多。c++中，vector底层由数组实现，list底层由链表实现。

大家都知道对于普通数组，一旦定义了大小就不能改变，例如int a[10];，这个数组a至多只能放10个元素，改不了的。而对于动态数组，就是可以不用关心初始时候的大小，可以随意往里放数据，那么耗时的原因就在于动态数组的底层实现。那么动态数组为什么可以不受初始大小的限制，可以随意push_back数据呢？

首先vector的底层实现也是普通数组。当对vector进行超出长度地push_back时，数组会重新申请一个二倍于原数组大小的数组，然后把数据都拷贝过去，并释放原数组内存。时间复杂度是O(n)（对，就是这么原始粗暴的方法！）

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201218185902217.png)

所以在进行高频插入操作时，优先选择list来做。

**代码：**

```c++
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp); 
        list<vector<int>> que;
        for (int i = 0; i < people.size(); i++){
            int position = people[i][1];
            std::list<vector<int>>::iterator it = que.begin();
            while (position--){
                it ++;
            }
            que.insert(it, people[i]);
        }

        return vector<vector<int>>(que.begin(), que.end());
            
    }
};
```



## 452. 用最少数量的箭引爆气球 [medium]

[452. 用最少数量的箭引爆气球 - 力扣（LeetCode）](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)

**思路：**

找重叠最多的区域射箭。

换句话说，从左到右排序后，从第二个开始，发现其与前一个有重叠，就不用另外射一箭了。但是要缩小右边界为较小的那一个，因为这是射箭的右边界。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201123101929791.png)

**代码：**

```c++
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // 气球i和气球i-1不挨着，注意这里不是>=
                result ++; // 需要一支箭
            }
            else { // i 与 i - 1 重叠
                // 更新重叠气球的最小又边界，result不加，看下一个和缩小后的右边界是否有重叠，若还有，继续缩小；若没有，result ++
                points[i][1] = min(points[i - 1][1], points[i][1]); 
            }
        }
        return result;    
    }   
};
```



## 435. 无重叠区间 [medium]

[435. 无重叠区间 - 力扣（LeetCode）](https://leetcode.cn/problems/non-overlapping-intervals/)

**思路：**

和上面射气球的思路很像，几乎是一样的。先按左边界从小到大排序，然后从左到右遍历，发现重叠右边界缩小，计数+1

**代码：**

```c++
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int result = 0;
        for (int i = 1; i < intervals.size(); i++){
            if (intervals[i][0] < intervals[i - 1][1]) {
                result ++;
                intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]);
            }
        }
        return result; 
    }
};
```



## 56. 合并区间 [medium]

[56. 合并区间 - 力扣（LeetCode）](https://leetcode.cn/problems/merge-intervals/)

**思路：**

和上两道题很像，自己看代码吧。🙈

**代码：**

```c++
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] <= result.back()[1]) {
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};
```



##  763. 划分字母区间 [medium]

[763. 划分字母区间 - 力扣（LeetCode）](https://leetcode.cn/problems/partition-labels/)

**思路：**

首先遍历一遍，统计每个字母的最远下标，存在数组里。

然后再从左向右遍历一遍，每遍历一个，就更新一下最远下标为当前与已记录的最远下标更远的那个，直到遍历到所记录的最远下标本身，就说明当前这个位置就是分割点。

我知道有点绕，看图好好体会一下：

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201222191924417.png)

**代码：**

```c++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int hash[26] = {0}; // i为字符，hash[i]为字符出现的最后位置
        for (int i = 0 ; i < s.size(); i++) { // 统计每一个字符最后出现的位置
            hash[s[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++) {
            right = max(right, hash[s[i] - 'a']); // 已经遍历到字符出现的最远边界
            if (i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return result;
    }
};
```



##  738.单调递增的数字 [medium]

[738. 单调递增的数字 - 力扣（LeetCode）](https://leetcode.cn/problems/monotone-increasing-digits/)

**思路：**

判断数字的个十百位，转字符串用下标更方便一些。

例如98，一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），首先想让strNum[i - 1]--，然后strNum[i]给为9，这样这个整数就是89，即小于98的最大的单调递增整数。

**代码：**

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string strNum = to_string(n);
        // flag用来标记赋值9从哪里开始
        // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
        int flag = strNum.size();
        for (int i = strNum.size() - 1; i > 0; i--) {
            if (strNum[i - 1] > strNum[i]) {
                flag = i;
                strNum[i - 1] --;
            }
        }

        for (int i = flag; i < strNum.size(); i++) {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }
};
```



## 968. 监控二叉树 [hard]

[968. 监控二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-cameras/)

**思路：**

要明确一个原则：摄像头不能放叶子结点，不然会天然损失一层视野。

**所以我们要从下往上看，局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少！**由此自然而然选择后序遍历。

如何判断哪个结点改装摄像头？在遍历时，我们给每个结点赋予一个状态：

0：该结点无覆盖

1：该结点有摄像头

2：该结点有覆盖

注意，空节点应被赋予2状态，不然叶子结点就该装插眼了。

以空节点这个赋予规则起手，就可以进行后序遍历了。每到一个新结点，判断其左右孩子的状态以确定其自身的状态，若自身状态为1就摄像头计数+1

左右孩子的情况，可分为以下四种：

情况一：左右孩子都有覆盖 ——> 当前结点无覆盖

情况二：左右孩子至少有一个无覆盖 ——> 当前结点装摄像头

情况三：左右孩子至少有一个摄像头 ——> 当前结点有覆盖

情况四：头节点为无覆盖 ——> 在主函数中result+1  （因为递归到root就停止了，并没有在递归中+1，所以在主函数中补上，实则为情况二）

**代码：**

```c++
class Solution {
private:
    int result;
    int traversal(TreeNode* cur) {
        // 空节点，有覆盖
        if (cur == nullptr) return 2;

        int left = traversal(cur->left);
        int right = traversal(cur->right);

        // 情况一 左右子结点都有覆盖
        if (left == 2 && right == 2) return 0;

        // 情况二
        // left == 0 && right == 0 左右节点无覆盖
        // left == 1 && right == 0 左节点有摄像头，右节点无覆盖
        // left == 0 && right == 1 左节点有无覆盖，右节点摄像头
        // left == 0 && right == 2 左节点无覆盖，右节点覆盖
        // left == 2 && right == 0 左节点覆盖，右节点无覆盖
        if (left == 0 || right == 0) {
            result ++;
            return 1;
        }

        // 情况三
        // left == 1 && right == 2 左节点有摄像头，右节点有覆盖
        // left == 2 && right == 1 左节点有覆盖，右节点有摄像头
        // left == 1 && right == 1 左右节点都有摄像头
        if (left == 1 || right == 1) return 2;

        // 实际不会走到这里的，上面已经覆盖了所有情况
        return -1;
    }
public:
    int minCameraCover(TreeNode* root) {
        result = 0;
        // 情况四 root无覆盖
        if (traversal(root) == 0) {
            result ++;
        }
        return result;
    }
};
```



# 动态规划

## 基础理论

动态规划，英文：Dynamic Programming，简称DP，如果某一问题有很多重叠子问题，使用动态规划是最有效的。

**对于动态规划问题，我将拆解为如下五步曲，这五步都搞清楚了，才能说把动态规划真的掌握了！**

1. dp数组以及下标的含义

2. 确定递推公式

3. dp数组如何初始化

4. 确定遍历顺序

5. 举例推导dp数组

写之前一定要把dp数组在具体情况中模拟一遍，在debug时也可以打印出dp数组看一看



## 509. 斐波那契数 [easy]

[509. 斐波那契数 - 力扣（LeetCode）](https://leetcode.cn/problems/fibonacci-number/)

**思路：**

1. dp数组以及下标的含义：

   dp数组即斐波那契数列本身，下标表示斐波那契数列的第i位

2. 确定递推公式

   dp[i] = dp[i -1] - dp[i - 2] (i > 2)

3. dp数组如何初始化

   dp[0] = 0; dp[1] = 1;

4. 确定遍历顺序

   从前向后遍历

5. 举例推导dp数组：略

**代码：**

```C++
class Solution {
public:
    int fib(int n) {
        if(n <= 1) return n;
        int dp[2];
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++){
            int sum = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = sum;
        }
        return dp[1];
    }
};
```



## 70. 爬楼梯 [easy]

[70. 爬楼梯 - 力扣（LeetCode）](https://leetcode.cn/problems/climbing-stairs/)

**思路**：

1. 确定dp数组（dp table）以及下标的含义

   dp[i]意为爬到第i层楼梯，有dp[i]种方法。

2. 确定递推公式

   首先是dp[i - 1]，上i-1层楼梯，有dp[i - 1]种方法，那么再一步跳一个台阶不就是dp[i]了么。

   还有就是dp[i - 2]，上i-2层楼梯，有dp[i - 2]种方法，那么再一步跳两个台阶不就是dp[i]了么。

   那么dp[i]就是 dp[i - 1]与dp[i - 2]之和！

   所以dp[i] = dp[i - 1] + dp[i - 2] 。

3. dp数组如何初始化

   题目规定n>0，所以没必要讨论dp[0]的初始化。

   dp[1] = 1， dp[2] = 2

4. 确定遍历顺序

   从dp[3]开始往后遍历

5. 举例推导dp数组

   n = 5：0， 1， 2， 3， 5， 8， 

**代码：**

```c++
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int dp[2];
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2; i < n; i++){
            int sum = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = sum;
        }
        return dp[1];
    }
};
```



## 746. 使用最小花费爬楼梯 [easy]

[746. 使用最小花费爬楼梯 - 力扣（LeetCode）](https://leetcode.cn/problems/min-cost-climbing-stairs/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   **到达第i台阶所花费的最少体力为dp[i]**

2. 确定递推公式

   **可以有两个途径得到dp[i]，一个是dp[i-1] 一个是dp[i-2]**。选一个花费小的：

   dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);

3. dp数组如何初始化

   dp[0] = 0，dp[1] = 0;

4. 确定遍历顺序

   从前向后遍历

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20221026175104.png)

**代码：**

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size() + 1);
        dp[0] = 0;
        dp[1] = 0;
        for(int i = 2; i <= cost.size(); i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[cost.size()];
    }
};
```



## 62. 不同路径 [medium]

[62. 不同路径 - 力扣（LeetCode）](https://leetcode.cn/problems/unique-paths/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp[i][j] ：表示从（0 ，0）出发，到(i, j) 有dp\[i][j]条不同的路径

2. 确定递推公式

   想要求dp\[i][j]，只能有两个方向来推导出来，即dp\[i - 1][j] 和 dp\[i][j - 1]。

   那么很自然，dp\[i][j] = dp\[i - 1][j] + dp\[i][j - 1]，

3. dp数组如何初始化

   ```c++
   for (int i = 0; i < m; i++) dp[i][0] = 1;
   for (int j = 0; j < n; j++) dp[0][j] = 1;
   ```

4. 确定遍历顺序

   这里要看一下递推公式dp\[i][j] = dp\[i - 1][j] + dp\[i][j - 1]，dp\[i][j]都是从其上方和左方推导而来，那么从左到右一层一层遍历就可以了。

   这样就可以保证推导dp\[i][j]的时候，dp\[i - 1][j] 和 dp\[i][j - 1]一定是有数值的。

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20201209113631392.png)

**代码：**

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int j = 0; j < n; j++) dp[0][j] = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```



## 63. 不同路径II [medium]

[63. 不同路径 II - 力扣（LeetCode）](https://leetcode.cn/problems/unique-paths-ii/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp\[i][j]：走到网格grid\[i][j]有几种方式。

2. 确定递推公式

   只能向右或向下走，因此：dp\[i][j] = dp\[i - 1][j] + dp\[i][j-1]

   由于存在障碍，障碍点出dp为0，因此：

   ```c++
   if (obstacleGrid[i][j] != 1) {
   	dp[i][j] = dp[i - 1][j] + dp[i][j-1]
   } else dp[i][j] = 0;
   ```

   还需考虑，若障碍出现在起点或终点，那还玩个p，直接return0

3. dp数组如何初始化

   两条边上一旦出现障碍，后面的格子应该都是0才对。

   ```c++
   for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
   for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
   ```

4. 确定遍历顺序

   从左到右，从上到下，一层层遍历

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210104114610256.png)

**代码：**

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1) return 0; //如果在起点或终点出现了障碍，直接返回0
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
        for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++){
                if (obstacleGrid[i][j] != 1) {
	                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                } else dp[i][j] = 0;
            }
        }

        return dp[m - 1][n - 1];
    }
};
```



## 343. 整数拆分 [medium]

[343. 整数拆分 - 力扣（LeetCode）](https://leetcode.cn/problems/integer-break/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp[i]：分拆数字i，可以得到的最大乘积为dp[i]

2. 确定递推公式

   从1遍历j，然后有两种渠道得到dp[i]（0 < j < i）。一个是 j * (i - j)，也就是将i拆分成两份；另一个是j * dp[i - j]，也就是将i拆分成多份（>2）。

   那么在取最大值的时候，为什么还要比较dp[i]呢？因为在递推公式推导的过程中，每次计算dp[i]，取最大的而已。(一个i循环中有多个j)。

3. dp数组如何初始化

   拆分0，1显然没有意义，所以初始化从dp[2]开始。显然dp[2] = 1。

4. 确定遍历顺序

   dp[i]依赖dp[i - j]，故从前向后遍历

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230310160208567.png)

**代码：**

```c++
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++){
            for(int j = 1; j <= i/2; j++) {
                dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
            }
        }
        return dp[n];
    }
};
```



## 96. 不同的二叉搜索树 [medium]

[96. 不同的二叉搜索树 - 力扣（LeetCode）](https://leetcode.cn/problems/unique-binary-search-trees/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp[i]意味给定整数i，有搜索二叉树dp[i]种。

2. 确定递推公式

   在1-n中选一个i做根节点，则其左子树范围是[1, i)，右子树范围是(i, n]。故左子树的组成方案有dp[i - 1]，右子树的组成方案有dp[n - i]

   故选择i作为根节点，共有dp[i-1] * dp[n-i]种方案。

   i从1~n，将所有结果累加起来就是dp[n]的值。

   可以优化，因为是左右对称的，如若n = 4，那么根节点取1与根节点取4的方案是一样多的。具体优化见代码。

3. dp数组如何初始化

   dp[0] = 1; dp[1] = 1;

4. 确定遍历顺序

   从左至右

5. 举例推导dp数组

**代码：**

```c++
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i / 2; j++) { // 左右对称，算一半即可
                dp[i] += dp[j - 1] * dp[i - j];
            }
            if(i % 2 == 0) dp[i] = dp[i] * 2;
            else dp[i] = dp[i] * 2 + dp[i / 2]  * dp[i / 2]; // 中位数做根节点
        }
        return dp[n];
    }
};
```



## 0-1背包基础理论

背包问题是这样一类问题：现有一个背包的容量（能容纳的重量）为n，有m件需要装到背包中的物品（下标为0, 1, 2, ..., m - 1），其中第i件（0 <= i <= m-1）的重量为weight[i]，价值为value[i]，求解该背包可装的最大价值为多少？

上面的描述中每个物品只能装一次，此类问题被称为0-1背包问题，除此之外还有完全背包、多重背包等模式，详见下图。此处我们只讨论0-1背包。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210117171307407.png)

**思路：**

**二维dp数组：**

1. 确定dp数组（dp table）以及下标的含义

   dp\[i][j]意为：从0~i中选择任意件物品，装到容量为j的背包中，其能装的最大价值为dp\[i][j]

2. 确定递推公式

   有两个方向推出来dp[i][j]，

   - **不放物品i**：由dp\[i - 1][j]推出，即背包容量为j，里面不放物品i的最大价值，此时dp[i][j]就是dp\[i - 1][j]。(其实就是当物品i的重量大于背包j的重量时，物品i无法放进背包中，所以被背包内的价值依然和前面相同。)
   - **放物品i**：由dp\[i - 1][j - weight[i]]推出，dp\[i - 1][j - weight[i]] 为背包容量为j - weight[i]的时候不放物品i的最大价值，那么dp\[i - 1][j - weight[i]] + value[i] ，就是背包放物品i得到的最大价值

   故：$dp[i][j] = max(dp[i - 1][j], dp[i - 1][j-weight[i]] + value[i])$

3. dp数组如何初始化

   当j=0时，dp\[i][0] = 0。

   当i=0时，dp\[0][j] = 0 (if j < weight[0]) 或 = value[0] (else)

   其他值初始为0（随便什么其实都可以）

4. 确定遍历顺序

   当前位置数据只依赖其左上角与正上方的数据，所以从上到下，从左到右遍历。先i后j与先j后i都可，这里只介绍先i后j，这个理解比较容易些

   ```c++
   for(int i = 1; i < weight.size(); i++) { // 遍历物品
       for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
           if (j < weight[i]) dp[i][j] = dp[i - 1][j];
           else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
   
       }
   }
   ```

5. 举例推导dp数组

   背包最大重量为4。

   物品为：

   |       | 重量 | 价值 |
   | :---: | :--: | :--: |
   | 物品0 |  1   |  15  |
   | 物品1 |  3   |  20  |
   | 物品2 |  4   |  30  |

   则推导dp数组为：

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210118163425129.jpg)

**一维dp数组：**

上面的二维数组可以优化为一维数组，节省空间。（时间是一样滴）

在使用二维数组的时候，递推公式：$dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);$

**其实可以发现如果把dp[i - 1]那一层拷贝到dp[i]上，表达式完全可以是：$dp[i][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i]);$**

**与其把dp[i - 1]这一层拷贝到dp[i]上，不如只用一个一维数组了**，只用dp[j]（一维数组，也可以理解是一个滚动数组）。

这就是滚动数组的由来，需要满足的条件是上一层可以重复利用，直接拷贝到当前层。

1. 确定dp数组（dp table）以及下标的含义

   dp[j]表示：容量为j的背包，所背的物品价值可以最大为dp[j]

2. 确定递推公式

   dp[j]有两个选择，一个是取自己dp[j] 相当于 二维dp数组中的dp\[i-1][j]，即不放物品i，一个是取dp[j - weight[i]] + value[i]，即放物品i。二者中取一个最大的。
   $$
   dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
   $$

3. dp数组如何初始化

   显然有dp[0] = 0，其他的地方，可以注意到是取最大值，那么初始化一个比所有价值小的值就可以了。例如所有价值都大于0，那就初始化为0。

4. 确定遍历顺序

   首先说结论：需要在j的维度从后向前遍历

   ```c++
   for(int i = 0; i < weight.size(); i++) { // 遍历物品
       for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
           dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
       }
   }
   ```

   为什么从后向前？在二维dp里，我么知道更新当前位置的数据，需要的是其左上方的数据。那么压缩到一维后，其左的数据不一定是左上方，若已经更新过，则是同一行的左方。

   所以我们需要从后往前更新，以确保更新这个位置时，其左边的数据都是未更新的，也就是左上方的数据。这样做的实际意义是，为了防止一个物品被多次添加到背包中。

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210110103614769.png)





## 416. 分割等和子集 [medium]

[416. 分割等和子集 - 力扣（LeetCode）](https://leetcode.cn/problems/partition-equal-subset-sum/)

**思路：**

抽象为背包问题，需要求容量为sum/2的背包所能装的最大值，物品是数组元素本身，其重量与价值也是本身。若dp[sum/2] == sum/2，就表示这个背包可以被装满，即满足了题目的要求。

**代码：**

```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        if (sum % 2 == 0) sum /= 2;
        else return false;

        vector<int> dp(sum + 1);

        for (int i = 0; i < nums.size(); i++){
            for (int j = sum; nums[i] <= j; j--) {
                dp[j] = max(dp[j], dp[j-nums[i]]+nums[i]);
            }
        }

        return dp[sum] == sum;
    }
};

```



## 1049. 最后一块石头的重量II [medium]

[1049. 最后一块石头的重量 II - 力扣（LeetCode）](https://leetcode.cn/problems/last-stone-weight-ii/)

**思路：**

把数组分成两份，使得两份的总和尽可能接近。这里抽象为背包问题，背包容量为sum/2，求该背包所能装的最大价值。物品的重量与价值均为其本身。

1. 确定dp数组（dp table）以及下标的含义

   dp[j]表示容量为j的背包，所能装下的最大价值

2. 确定递推公式

   dp[j] = max(dp[j], dp[j-nums[i]]+nums[i])

3. dp数组如何初始化

   dp[0] = 0，其他也初始化为0

4. 确定遍历顺序

   从后向前遍历。

5. 举例推导dp数组

**代码：**

```c++
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for (int stone: stones) {
            sum += stone;
        }
        int target = sum/2;
        vector<int> dp(target + 1, 0);   // [0, target]

        for (int i = 0; i < stones.size(); i++) {
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }

        return abs(sum - dp[target] - dp[target]);
    }
};
```



	## 494. 目标和 [medium]

[494. 目标和 - 力扣（LeetCode）](https://leetcode.cn/problems/target-sum/)

**思路：**

如何转换成背包问题？首先数列可以分为两部分，一部分加+号（left）一部分加-号（right），这两部分和之差刚好等于target。

那么就有：left = (target + sum)/2 ，以此作为背包容量，统计装满背包的方法。

1. 确定dp数组（dp table）以及下标的含义

   dp[j] 表示：填满j（包括j）这么大容积的包，有dp[j]种方法

2. 确定递推公式

   有哪些来源可以推出dp[j]呢？

   只要搞到nums[i]，凑成dp[j]就有dp[j - nums[i]] 种方法。

   例如：dp[j]，j 为5，

   - 已经有一个1（nums[i]） 的话，有 dp[4]种方法 凑成 容量为5的背包。
   - 已经有一个2（nums[i]） 的话，有 dp[3]种方法 凑成 容量为5的背包。
   - 已经有一个3（nums[i]） 的话，有 dp[2]中方法 凑成 容量为5的背包
   - 已经有一个4（nums[i]） 的话，有 dp[1]中方法 凑成 容量为5的背包
   - 已经有一个5 （nums[i]）的话，有 dp[0]中方法 凑成 容量为5的背包

   那么凑整dp[5]有多少方法呢，也就是把 所有的 dp[j - nums[i]] 累加起来。

   ```c++
   dp[j] += dp[j - nums[i]]
   ```

3. dp数组如何初始化

   从递推公式可以看出，在初始化的时候dp[0] 一定要初始化为1，因为dp[0]是在公式中一切递推结果的起源，如果dp[0]是0的话，递推结果将都是0。

4. 确定遍历顺序

   一维背包的正常顺序

5. 举例推导dp数组

   输入：nums: [1, 1, 1, 1, 1], S: 3

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210125120743274.jpg)

**代码：**

```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) sum += nums[i];
        if (abs(S) > sum) return 0; // 此时没有方案
        if ((S + sum) % 2 == 1) return 0; // 此时没有方案
        int bagSize = (S + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};
```



## 474. 一和零 [medium]

[474. 一和零 - 力扣（LeetCode）](https://leetcode.cn/problems/ones-and-zeroes/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   **dp\[i][j]：最多有i个0和j个1的strs的最大子集的大小为dp\[i][j]**

2. 确定递推公式

   dp\[i][j] 可以由前一个strs里的字符串推导出来，strs里的字符串有zeroNum个0，oneNum个1。

   dp\[i][j] 就可以是 dp\[i - zeroNum][j - oneNum] + 1。

   然后我们在遍历的过程中，取dp\[i][j]的最大值。

   所以递推公式：dp\[i][j] = max(dp\[i][j], dp\[i - zeroNum][j - oneNum] + 1);

3. dp数组如何初始化

   初始化0

4. 确定遍历顺序

   ```cpp
   for (string str : strs) { // 遍历物品
       int oneNum = 0, zeroNum = 0;
       for (char c : str) {
           if (c == '0') zeroNum++;
           else oneNum++;
       }
       for (int i = m; i >= zeroNum; i--) { // 遍历背包容量且从后向前遍历！
           for (int j = n; j >= oneNum; j--) {
               dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
           }
       }
   }
   ```

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210120111201512.jpg)

**代码：**

```c++
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); // 默认初始化0
        for (string str : strs) { // 遍历物品
            int oneNum = 0, zeroNum = 0;
            for (char c : str) {
                if (c == '0') zeroNum++;
                else oneNum++;
            }
            for (int i = m; i >= zeroNum; i--) { // 遍历背包容量且从后向前遍历！
                for (int j = n; j >= oneNum; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
```



## 完全背包基础理论

完全背包和01背包问题唯一不同的地方就是，**每种物品有无限件**。

**思路：**

我们知道01背包内嵌的循环是从大到小遍历，为了保证每个物品仅被添加一次。

而完全背包的物品是可以添加多次的，所以要从小到大去遍历，即：

```c++
for(int i = 0; i < weight.size(); i++) { // 遍历物品
    for(int j = weight[i]; j <= bagWeight ; j++) { // 遍历背包容量
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
}
```

实际上，完全背包一维dp的循环次序，是可以互换的，即j在外层i在内层。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210126104529605.jpg)

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210729234011.png)

先遍历背包在遍历物品，代码如下：

```cpp
// 先遍历背包，再遍历物品
for(int j = 0; j <= bagWeight; j++) { // 遍历背包容量
    for(int i = 0; i < weight.size(); i++) { // 遍历物品
        if (j - weight[i] >= 0) dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
    cout << endl;
}
```



## 518. 零钱兑换II [medium]

[518. 零钱兑换 II - 力扣（LeetCode）](https://leetcode.cn/problems/coin-change-ii/)

**思路：**

每个数字不限制数量，自然是完全背包。这里是求背包完全装满的情况，所以递推公式需要更改，和[494. 目标和 [medium]](#494. 目标和 [medium])这道题的思路一样。

需要注意，这里的双层循环顺序不能改变。先将coins一溜烟看过去，看一遍。不然就会出现重复的（组合变成排列）。

**代码：**

```c++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < coins.size(); i++){
            for (int j = coins[i]; j < dp.size(); j++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        
        return dp[amount];
    }
};
```



## 377. 组合总和IV [medium]

[377. 组合总和 Ⅳ - 力扣（LeetCode）](https://leetcode.cn/problems/combination-sum-iv/)

**思路：**

上道题的排列版本，交换for循环内外层顺序即可。

**代码：**

```c++
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 0; j < dp.size(); j++){
            for (int i = 0; i < nums.size(); i++) {
                // C++测试用例有两个数相加超过int的数据，所以需要在if里加上dp[i] < INT_MAX - dp[i - num]。
                if (j - nums[i] >= 0 && dp[j] < __INT_MAX__ - dp[j - nums[i]]) { 
                    dp[j] += dp[j - nums[i]];
                }
            }  
        }
        
        return dp[target];        
    }
};
```



## 322. 零钱兑换 [medium]

**[322. 零钱兑换 - 力扣（LeetCode）](https://leetcode.cn/problems/coin-change/)**

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp[j]：凑够j块钱所需要的最小硬币数

2. 确定递推公式

   凑足j - coins[i]块钱最少需要dp[j - coins[i]]个硬币。那么只需加上一个硬币coins[i]就凑够j块钱了！

   所以dp[j]要从dp[j - coins[i]] + 1中取最小的。

   故有递推公式：dp[j] = min(dp[j - coins[i]] + 1, dp[j]);

3. dp数组如何初始化

   根据题意，dp[0] = 0

   递推公式求min，其余的数就要初始化为绝对大的数，这样就不会错误覆盖了

4. 确定遍历顺序

   本题求钱币最小个数，**那么钱币有顺序和没有顺序都可以，都不影响钱币的最小个数**。

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210201111833906.jpg)

**代码：**

```c++
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) { // 遍历物品
            for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                if (dp[j - coins[i]] != INT_MAX) { // 如果dp[j - coins[i]]是初始值则跳过
                    dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
                }
            }
        }
        if (dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
```



## 279. 完全平方数 [medium]

[279. 完全平方数 - 力扣（LeetCode）](https://leetcode.cn/problems/perfect-squares/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp[j] 表示j能拆成最少dp[j]个完全平方数之和

2. 确定递推公式

   dp[j] = min(dp[j - i * i] + 1, dp[j])

3. dp数组如何初始化

   显然dp[0] = 0（题目的完全平方数从1开始），其余的取INT_MAX

4. 确定遍历顺序

   求最小数，无关排列还是组合，所以背包物品哪个在外面都可以

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210202112617341.jpg)

**代码：**

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, __INT_MAX__);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++) {
            for (int j = i * i; j <= n; j++) {
                dp[j] = min(dp[j - i * i] + 1, dp[j]);
            }
        }
        return dp[n];
    }
};
```



## 139. 单词拆分 [medium]

[139. 单词拆分 - 力扣（LeetCode）](https://leetcode.cn/problems/word-break/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   **dp[i] : 字符串长度为i的话，dp[i]为true，表示可以拆分为一个或多个在字典中出现的单词**。

2. 确定递推公式

   如果确定dp[j] 是true，且 [j, i] 这个区间的子串出现在字典里，那么dp[i]一定是true。（j < i ）。

   所以递推公式是 if([j, i] 这个区间的子串出现在字典里 && dp[j]是true) 那么 dp[i] = true。

3. dp数组如何初始化

   从递推公式中可以看出，dp[i] 的状态依靠 dp[j]是否为true，那么dp[0]就是递推的根基，dp[0]一定要为true，否则递推下去后面都都是false了。

   下标非0的dp[i]初始化为false，只要没有被覆盖说明都是不可拆分为一个或多个在字典中出现的单词。

4. 确定遍历顺序

   排列顺序，需要按照一定的顺序选取字典中的单词

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210202162652727.jpg)

**代码：**

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {   // 遍历背包
            for (int j = 0; j < i; j++) {       // 遍历物品
                string word = s.substr(j, i - j); //substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
```



## 多重背包简介

有N种物品和一个容量为V 的背包。第i种物品最多有Mi件可用，每件耗费的空间是Ci ，价值是Wi 。求解将哪些物品装入背包可使这些物品的耗费的空间 总和不超过背包容量，且价值总和最大。

多重背包和01背包是非常像的， 为什么和01背包像呢？

每件物品最多有Mi件可用，把Mi件摊开，其实就是一个01背包问题了。

例如：

背包最大重量为10。

物品为：

|       | 重量 | 价值 | 数量 |
| ----- | ---- | ---- | ---- |
| 物品0 | 1    | 15   | 2    |
| 物品1 | 3    | 20   | 3    |
| 物品2 | 4    | 30   | 2    |

问背包能背的物品最大价值是多少？

和如下情况有区别么？

|       | 重量 | 价值 | 数量 |
| ----- | ---- | ---- | ---- |
| 物品0 | 1    | 15   | 1    |
| 物品0 | 1    | 15   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品2 | 4    | 30   | 1    |
| 物品2 | 4    | 30   | 1    |

毫无区别，这就转成了一个01背包问题了，且每个物品只用一次。

这种方式来实现多重背包的代码如下：

```cpp
void test_multi_pack() {
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    vector<int> nums = {2, 3, 2};
    int bagWeight = 10;
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] > 1) { // nums[i]保留到1，把其他物品都展开
            weight.push_back(weight[i]);
            value.push_back(value[i]);
            nums[i]--;
        }
    }

    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // 遍历物品
        for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
        for (int j = 0; j <= bagWeight; j++) {
            cout << dp[j] << " ";
        }
        cout << endl;
    }
    cout << dp[bagWeight] << endl;

}
int main() {
    test_multi_pack();
}
```



## 198. 打家劫舍 [medium]

[198. 打家劫舍 - 力扣（LeetCode）](https://leetcode.cn/problems/house-robber/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   **dp[i]：考虑下标i（包括i）以内的房屋，最多可以偷窃的金额为dp[i]**。

2. 确定递推公式

   决定dp[i]的因素就是第i房间偷还是不偷。

   如果偷第i房间，那么dp[i] = dp[i - 2] + nums[i] ，即：第i-1房一定是不考虑的，找出 下标i-2（包括i-2）以内的房屋，最多可以偷窃的金额为dp[i-2] 加上第i房间偷到的钱。

   如果不偷第i房间，那么dp[i] = dp[i - 1]，即考 虑i-1房，（**注意这里是考虑，并不是一定要偷i-1房，这是很多同学容易混淆的点**）

   然后dp[i]取最大值，即dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);

3. dp数组如何初始化

   dp[0] = nums[0]

   dp [1] = max(nums[0], nums[1])

4. 确定遍历顺序

   dp[i] 是根据dp[i - 2] 和 dp[i - 1] 推导出来的，那么一定是从前到后遍历！

   代码如下：

   ```cpp
   for (int i = 2; i < nums.size(); i++) {
       dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
   }
   ```

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210221170954115.jpg)

**代码：**

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0); 
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++){
           dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }

        return dp[dp.size() - 1];
    }
};
```



## 213. 打家劫舍II [medium]

[213. 打家劫舍 II - 力扣（LeetCode）](https://leetcode.cn/problems/house-robber-ii/)

**思路：**

这道题与上道题的区别是房子连成环了。那么把环断开就好了：

要把环断开，可分为两种情况：

1. 不考虑队尾：

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210129160821374-20230310134003961.jpg)

2. 不考虑队首：

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210129160842491-20230310134008133.jpg)

那么在两种情况中分别用上一题的动规思路去求解一个最大值，最终二选一选更大的一个就好了。

**代码：**

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        return max(robRange(nums, 0, nums.size() - 2), robRange(nums, 1, nums.size() - 1));
    }

    // 198.打家劫舍逻辑
    int robRange(vector<int>& nums, int start, int end) {
        if (start == end) return nums[start];
        vector<int> dp(nums.size() - 1, 0);
        dp[0] = nums[start];
        dp[1] = max(nums[start], nums[start + 1]);
        for (int i = 2; i < dp.size(); i ++) {
            dp[i] = max(dp[i  - 2] + nums[start + i], dp[i - 1]);
        }
        return dp[dp.size() - 1];
    }
};
```



##  337. 打家劫舍 III [medium]

[337. 打家劫舍 III - 力扣（LeetCode）](https://leetcode.cn/problems/house-robber-iii/)

**思路：**

> 树形动归的入门题

讨论当前结点偷不偷，就要考虑子节点偷没偷，故采用后序遍历。

在遍历时，记录当前结点偷与没偷两种情况的值，并把它们返回到上层结点做参考。这里采用长度为2的dp数组，dp[0]记录没偷，dp[1]记录偷了

当遇到空节点，dp = {0 ,0}，以此为初始化

递推公式为

```c++
// 不偷当前结点，则俩子节点爱咋咋，选两个最大值加起来
dp[0] = max(left[0], left[1]) + max(right[0], right[1]);
// 偷当前结点，则俩子节点一个都不能偷
dp[1] = cur->val + left[0] + right[0];
// 由于取dp中的max，所以情况一若选了left[0]与right[0]，则会被情况二覆盖掉。父子仨高低得偷一个
```

**代码：**

```c++
class Solution {
public:
    vector<int> travelsal(TreeNode* cur) {
        if(cur == nullptr) return vector<int> {0, 0};
        vector<int> left = travelsal(cur->left);
        vector<int> right = travelsal(cur->right);
        vector<int> dp(2);
        dp[0] = max(left[0], left[1]) + max(right[0], right[1]);
        dp[1] = cur->val + left[0] + right[0];
        return dp;
    }

    int rob(TreeNode* root) {
        return max(travelsal(root)[0], travelsal(root)[1]);
    }
};
```



## 121. 买卖股票的最佳时机 [easy]

[121. 买卖股票的最佳时机 - 力扣（LeetCode）](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/)

**思路：**

贪心：

当遍历到i时，找[0,i]中的最小值记录与low，并计算prices[i] - low，并于之前的result进行比较，记录一个最大差值，即为最终结果

动规：

1. 确定dp数组（dp table）以及下标的含义

   dp\[i][0]表示第i天时，持有股票（也就是在[0,i]中某天买入，没卖）的情况下的最大利润。

   dp\[i][1]表示第i天时，不持有股票（也就是在[1, i]中某天卖出，或根本就没买）的情况下的最大利润

2. 确定递推公式

   dp\[i][0]由两个状态推出：

   - 第i-1天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：dp\[i - 1][0]
   - 第i天买入股票，所得现金就是买入今天的股票后所得现金即：-prices[i]

   ```c++
   dp[i][0] = max(dp[i - 1][0], -prices[i]);
   ```

   dp\[i - 1][1]由两个状态推出：

   - 第i-1天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：dp\[i - 1][1]
   - 第i天卖出股票，所得现金就是按照今天股票价格卖出后所得现金即：prices[i] + dp\[i - 1][0]

   ```c++
   dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
   ```

3. dp数组如何初始化

   ```
   dp[0][0] = -prices[0];
   dp[0][1] = 0;
   ```

4. 确定遍历顺序

   肯定从前向后啦

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210224225642465.png)

**代码：**

贪心：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            low = min(low, prices[i]);  // 取最左最小价格
            result = max(result, prices[i] - low); // 直接取最大区间利润
        }
        return result;
    }
};
```

动规：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 只依赖上一行，滚动数组省空间
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], -prices[i]);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0][0] = dp[1][0];
            dp[0][1] = dp[1][1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
```



## [122. 买卖股票的最佳时机II [medium]](#122. 买卖股票的最佳时机II [medium])



##  123. 买卖股票的最佳时机III [hard]

[123. 买卖股票的最佳时机 III - 力扣（LeetCode）](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/description/)

**思路：**

1. dp数组以及下标的含义：

   dp\[i][0]：第i天第一次持有

   dp\[i][1]：第i天第一次不持有

   dp\[i][2]：第i天第二次持有

   dp\[i][3]：第i天第二次不持有

2. 确定递推公式

   ```c++
   dp[i][0] = max(0 - prices[i], dp[i - 1][0]);
   dp[i][1] = max(dp[i - 1][0] + prices[i], dp[i - 1][1]);  
   dp[i][2] = max(dp[i - 1][1] - prices[i], dp[i - 1][2]);
   dp[i][3] = max(dp[i - 1][2] + prices[i], dp[i - 1][3]);
   ```

3. dp数组如何初始化

   ```c++
   dp[0][0] = -prices[0];
   dp[0][1] = 0;
   dp[0][2] = -prices[0];
   dp[0][3] = 0;
   ```

4. 确定遍历顺序

   顺序遍历

5. 举例推导dp数组：

**代码：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(4));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = -prices[0];
        dp[0][3] = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[1][0] = max(0 - prices[i], dp[0][0]);
            dp[1][1] = max(dp[0][0] + prices[i], dp[0][1]);  
            dp[1][2] = max(dp[0][1] - prices[i], dp[0][2]);
            dp[1][3] = max(dp[0][2] + prices[i], dp[0][3]);
            dp[0] = dp[1];
        }
        return max(max(dp[1][0], dp[1][1]), max(dp[1][2], dp[1][3]));
        
    }
};
```



##  188. 买卖股票的最佳时机IV [hard]

**思路：**

与上题无二，上题是k = 2的特殊情况，只需明确：j为奇数时买入，偶数时卖出即可。

**代码：**

```c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(2 * k));
        for(int j = 0; j < 2 * k; j++) {
            if (j % 2 == 0) {
                dp[0][j] = -prices[0];
            } else dp[0][j] = 0;
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < 2 * k; j++){
                if (j == 0)          dp[1][j] = max(0 - prices[i]           , dp[0][j]);
                else if (j % 2 == 0) dp[1][j] = max(dp[0][j - 1] - prices[i], dp[0][j]);
                else                 dp[1][j] = max(dp[0][j - 1] + prices[i], dp[0][j]);
            }
            dp[0] = dp[1];
        }
        
        int result = 0;
        for (int j = 0; j < 2 * k; j++) {
            result = max(result, dp[1][j]);
        }
        return result;
    }
};
```



##  309. 最佳买卖股票时机含冷冻期 [medium]

[309. 最佳买卖股票时机含冷冻期 - 力扣（LeetCode）](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

**思路：**

1. dp数组以及下标的含义

   四种状态：

   dp\[i][0]：持有股票

   dp\[i][1]：保持卖出股票的状态（两天前就卖出了股票，度过一天冷冻期。或者是前一天就是卖出股票状态，一直没操作）

   dp\[i][2]：今天卖出股票

   dp\[i][3]：今天为冷冻期状态，但冷冻期状态不可持续，只有一天！

2. 确定递推公式

   ```c++
   dp[i][0] = max(dp[i - 1][0], dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]); // 前一天已持有、前一天冷冻期、前一天已卖出
   dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
   dp[i][2] = dp[i - 1][0] + prices[i];
   dp[i][3] = dp[i - 1][2]
   ```

3. dp数组如何初始化

   ```c++
   dp[0][0] = -prices[0];
   dp[0][1] = 0;
   dp[0][2] = 0;
   dp[0][3] = 0;
   ```

4. 确定遍历顺序

5. 举例推导dp数组

**代码：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(4));
        dp[0][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], max(dp[0][3] - prices[i], dp[0][1] - prices[i])); // 前一天已持有、前一天冷冻期、前一天已卖出
            dp[1][1] = max(dp[0][1], dp[0][3]);
            dp[1][2] = dp[0][0] + prices[i];
            dp[1][3] = dp[0][2];
            dp[0] = dp[1];
        }

        int result = 0;
        for (int j = 0; j < 4; j++) {
            result = max(result, dp[1][j]);
        }

        return result;
    }
};
```



##  714. 买卖股票的最佳时机含手续费 [medium]

[714. 买卖股票的最佳时机含手续费 - 力扣（LeetCode）](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

**思路：**

在[这道题](#122. 买卖股票的最佳时机II [medium])的基础上，每次交易（卖出或者买入选一个）减去fee即可。

**代码：**

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(2, vector<int>(2));
        dp[0][0] = -prices[0] - fee;
        for (int i = 1; i < prices.size(); i++){
            dp[1][0] = max(dp[0][0], dp[0][1] - prices[i] - fee);
            dp[1][1] = max(dp[0][1], dp[0][0] + prices[i]);
            dp[0] = dp[1];
        }

        return max(dp[1][0], dp[1][1]);
    }
};
```



## 300. 最长递增子序列 [medium]

[300. 最长递增子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/longest-increasing-subsequence/)

**思路：**

1. dp数组以及下标的含义

   **dp[i]表示i之前包括i的以nums[i]结尾的最长递增子序列的长度**（很刁钻）

2. 确定递推公式

   位置i的最长升序子序列等于从0到i-1各个位置的最长升序子序列 + 1 的最大值。

   ```c++
   if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1); // 这里 j 属于[0, i - 1]，这样做目的是取所有dp[j] + 1中最大的那个
   ```

3. dp数组如何初始化

   dp[i] = 1；

4. 确定遍历顺序

   从前往后，i在外层j在内层

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210110170945618.jpg)

**代码：**

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if(nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);                
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};
```



## 674. 最长连续递增序列 [easy]

[674. 最长连续递增序列 - 力扣（LeetCode）](https://leetcode.cn/problems/longest-continuous-increasing-subsequence/)

**思路：**

与上一题不同的只有递推公式。

上一题的递推公式要从[0, i - 1]中取一个最大的dp[j]再 + 1（nums[i] > nums[j]）, 在此题中只用与前一个数字比较，大了就+1小了回到1。

也可以用贪心来做，也就是遇到nums[i] > nums[i - 1]的情况，count就++，否则count为1，记录count的最大值就可以了。

**代码：**

贪心：

```c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int result = 1; // 连续子序列最少也是1
        int count = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) { // 连续记录
                count++;
            } else { // 不连续，count从头开始
                count = 1;
            }
            if (count > result) result = count;
        }
        return result;
    }
};
```

动规：

```c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) dp[i]  = dp[i - 1] + 1;
            result = max(result, dp[i]);
        }
        return result;
    }
};
```



## 718. 最长重复子数组 [medium]

[718. 最长重复子数组 - 力扣（LeetCode）](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)

**思路：**

1. dp数组以及下标的含义

   dp\[i][j] ：以下标i - 1为结尾的A，和以下标j - 1为结尾的B，最长重复子数组长度为dp\[i][j]。

2. 确定递推公式

   根据dp[i][j]的定义，dp\[i][j]的状态只能由dp\[i - 1][j - 1]推导出来。

   即当A[i - 1] 和B[j - 1]相等的时候，dp\[i][j] = dp\[i - 1][j - 1] + 1;

   根据递推公式可以看出，遍历i 和 j 要从1开始！

3. dp数组如何初始化

   dp\[i][0] = dp\[0][j] = 0

   这样初始化仅仅为了满足递推公式，并无实际意义

4. 确定遍历顺序

   从前往后，内外层顺序都可

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/2021011215282060.jpg)

**代码：**

```c++
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1));
        int result = 0;
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};
```



## 1143.最长公共子序列 [medium]

[1143. 最长公共子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/longest-common-subsequence/)

**思路**

1. dp数组以及下标的含义

   dp\[i][j]：长度为[0, i - 1]的字符串text1与长度为[0, j - 1]的字符串text2的最长公共子序列为dp\[i][j]

2. 确定递推公式

   ```cpp
   if (text1[i - 1] == text2[j - 1]) {
       dp[i][j] = dp[i - 1][j - 1] + 1;
   } else {
       // 如果text1[i - 1] 与 text2[j - 1]不相同，那就看看text1[0, i - 2]与text2[0, j - 1]的最长公共子序列 和 text1[0, i - 1]与text2[0, j - 2]的最长公共子序列，取最大的。
       dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
   }
   ```

3. dp数组如何初始化

   同上题

4. 确定遍历顺序

   从前往后，从上往下

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210210150215918.jpg)

**代码：**

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1));
        int result = 0;
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};
```



## 1035.不相交的线 [medium]

[1035. 不相交的线 - 力扣（LeetCode）](https://leetcode.cn/problems/uncrossed-lines/description/)

**思路：**

和上道题一样。

对了，上道题result多此一举，看下面：

**代码：**

```c++
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if(nums1[i - 1] == nums2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }            
        }
        return dp[nums1.size()][nums2.size()];
    }
};
```



##  [53. 最大子序和 [medium]](#53. 最大子序和 [medium])



## 392. 判断子序列 [medium]

[392. 判断子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/is-subsequence/)

**思路：**

正常思路：

双指针，i是s的指针，j是t的指针。匹配上了俩都++，没匹配上j++。最后i到头了就true，没到头就false

动规：

1. dp数组以及下标的含义

   dp\[i][j]：以s[i - 1]结尾的字符串与t[j - 1]结尾的字符串，**相同子序列的长度为dp\[i][j]**

2. 确定递推公式

   ```
   if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] ++;
   else dp[i][j] = dp[i][j - 1];
   ```

   很像[1143.最长公共子序列 [medium]](#1143.最长公共子序列 [medium])，但本题只有t中可以删字符，所以还是有些差别

3. dp数组如何初始化

   ```
   dp[0][j] = 0;
   ```

4. 确定遍历顺序

   从左到右

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/2021030317364166.jpg)



**代码：**

双指针：

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;
        int j = 0;
        while (i < s.size() & j < t.size()){
            if (s[i] == t[j]) {
                i ++;
                j ++;
            } else {
                j ++;
            }
        }
        if (i == s.size()) return true;
        else return false;
    }
};
```

动规：

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = dp[i][j - 1];
            }
        }
        return dp[s.size()][t.size()] == s.size();
    }
};
```



## 115. 不同的子序列 [hard]

[115. 不同的子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/distinct-subsequences/)

**思路：**

1. 确定dp数组（dp table）以及下标的含义

   dp\[i][j]：以i-1为结尾的s子序列中出现以j-1为结尾的t的个数为dp\[i][j]。

2. 确定递推公式

   这一类问题，基本是要分析两种情况

   - s[i - 1] 与 t[j - 1]相等

     如果用s[i - 1]来匹配，个数为dp\[i - 1][j - 1]，即不需要考虑当前s子串和t子串的最后一位字母，所以只需要 dp\[i-1][j-1]。

     如果不用s[i - 1]来匹配，个数为dp\[i - 1][j]，即不考虑s子串最后一个字母。

     t子串不能删除，所以有上面两种情况，两种情况加起来：dp\[i][j] = dp\[i - 1][j - 1] + dp\[i - 1][j]

   - s[i - 1] 与 t[j - 1] 不相等

     那就就和去掉当前s位的情况一样咯，即dp\[i][j] = dp\[i - 1][j];

3. dp数组如何初始化

   由于是从左方与上方初始化，所以dp\[i][0] 和dp\[0][j]是一定要初始化的。

   dp\[i][0] 表示：以i-1为结尾的s可以随便删除元素，出现空字符串的个数。所以 = 1

   dp\[0][j]：空字符串s可以随便删除元素，出现以j-1为结尾的字符串t的个数。所以 = 0

   dp\[0][0]应该是1，空字符串当然包括一个空字符串。（你要不要听听你在说什么？）

4. 确定遍历顺序

   从左到右，从上到下

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/115.不同的子序列.jpg)

**代码：**

```c++
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1));
        for(int i = 0; i <= s.size(); i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if(s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
                else dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[s.size()][t.size()];
    }
};
```



## 583. 两个字符串的删除操作 [medium]

[583. 两个字符串的删除操作 - 力扣（LeetCode）](https://leetcode.cn/problems/delete-operation-for-two-strings/)

**思路：**

本质是求两个字符串的最长公共子序列，和[1143题](#1143.最长公共子序列 [medium])几乎一样，最后的返回值有些差别，毕竟本题求得是最少删除数。

**代码：**

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if(word1[i -1] == word2[j - 1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
        return word1.size() + word2.size() - 2 * dp[word1.size()][word2.size()];
    }
};
```



## 72. 编辑距离 [hard]

[72. 编辑距离 - 力扣（LeetCode）](https://leetcode.cn/problems/edit-distance/)

**思路：**

1. dp数组以及下标的含义

   **dp\[i][j] 表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp\[i][j]**。

2. 确定递推公式

   如果word1[i - 1] == word2[j - 1]，则不用任何编辑。此时dp\[i][j] = dp\[i - 1][j - 1]

   如果word1[i - 1] != word2[j - 1]，则需要编辑，编辑分为删，改，增三种：

   - 删

     word1删除一个元素，那么就是以下标i - 2为结尾的word1 与 j-1为结尾的word2的最近编辑距离再加上一个操作。

     ```c++
     dp[i][j] = dp[i - 1][j] + 1;
     ```

     word2删除一个元素，那么就是以下标i - 1为结尾的word1 与 j-2为结尾的word2的最近编辑距离再加上一个操作。

     ```c++
     dp[i][j] = dp[i][j - 1] + 1;
     ```

   - 增：

     其实word1删除word1[i - 1]，就相当于word2加上这个元素。所以增包含在删里了。

   - 改：

     `word1`替换`word1[i - 1]`，使其与`word2[j - 1]`相同，此时不用增删加元素。

     由于替换后word1[i - 1] == word2[j - 1]，所以有：dp\[i][j] = dp\[i - 1][j - 1] + 1;

   综上：

   ```c++
   if (word1[i - 1] == word2[j - 1]) {
       dp[i][j] = dp[i - 1][j - 1];
   }
   else {
       dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
   }
   ```

3. dp数组如何初始化

   dp\[i][0] ：以下标i-1为结尾的字符串word1，和空字符串word2，最近编辑距离为dp\[i][0]。那么显然dp\[i][0] = i

   同理，dp\[0][j] = j

4. 确定遍历顺序

   从左到右，从上到下

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210114162132300.jpg)

**代码：**

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```



## 647. 回文子串 [medium]

[647. 回文子串 - 力扣（LeetCode）](https://leetcode.cn/problems/palindromic-substrings/)

**思路：**

双指针法：

如何判断一个字符串是回文串？答曰：从中间向两边两个指针，各自向左向右走，那么当这两个指针指的字符不为空且相等，就可以说找到了一个回文串。

字符串中每一个字符都可以当作”中间“，当然，每相邻得两个字符也可以当作”中间“。

动规：

1. dp数组以及下标的含义

   dp\[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串，如果是dp\[i][j]为true，否则为false。

2. 确定递推公式

   当s[i] != s[j]时，没啥好说了，一定是false

   当s[i] == s[j]时，就比较复杂了：

   - i == j：子串就一个字符，当然true
   - i和j差1，那两个一样的字符，一眼true
   - 以上之外呢，就要与前辈dp\[i + 1][j - 1]一样，也就是先保证里层是回文。

   综上：

   ```c++
   if (s[i] == s[j]) {
       if (j - i <= 1) { // 情况一 和 情况二
           result++;
           dp[i][j] = true;
       } else if (dp[i + 1][j - 1]) { // 情况三
           result++;
           dp[i][j] = true;
       }
   }
   ```

3. dp数组如何初始化

   dp\[i][j]可以初始化为true么？ 当然不行，怎能刚开始就全都匹配上了。

   所以dp\[i][j]初始化为false。

4. 确定遍历顺序

   观察上面的递推公式，发现出现了dp\[i + 1][j - 1]，这玩意在左下角。

   所以应当从左到右，从下到上。也就是i从大到小，j从小到大。

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210121171059951-20230310132153163.jpg)

**代码：**

双指针法：

```c++
class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, s.size()); // 以i为中心
            result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return result;
    }
    int extend(const string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
    }
};
```

动规：

```c++
class Solution {
public:
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) {  // 注意遍历顺序
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    if (j - i <= 1) { // 情况一 和 情况二
                        result++;
                        dp[i][j] = true;
                    } else if (dp[i + 1][j - 1]) { // 情况三
                        result++;
                        dp[i][j] = true;
                    }
                }
            }
        }
        return result;
    }
};
```



## 516. 最长回文子序列 [medium]

[516. 最长回文子序列 - 力扣（LeetCode）](https://leetcode.cn/problems/longest-palindromic-subsequence/)

**思路：**

1. dp数组以及下标的含义

   dp\[i][j]：子串[i, j]中最长回文序列的长度

2. 确定递推公式

   s[i] == s[j]：dp\[i][j] = dp\[i + 1][j - 1] + 2;

   s[i] != s[j]：这时显然，同时加入s[i]与s[j]对于回文序列的长度没有贡献。加一个或许还有贡献（bbba），所以取两边只加一个的最大值

   dp\[i][j] = max(dp\[i + 1][j], dp\[i][j - 1])

3. dp数组如何初始化

   可以看到，dp数组计算不到i == j时的情况。故需初始化。

   显然，当i与j相等，那就是取一个字符，本身就是回文序列。=1

4. 确定遍历顺序

   从下向上，从左往右，同时确保i < j（i > j赋值0即可。）

5. 举例推导dp数组

   ![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/20210127151521432.jpg)

**代码：**

```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size()));
        for(int i = 0; i < s.size(); i++) {
            dp[i][i] = 1;
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = 0; j < s.size(); j++) {
                if(j > i) {
                    if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
                    else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
```



## 动规总结

终于做完一遍啦，感觉有些题还是迷迷糊糊。需要二刷。

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230322202558390.png)

<img src="https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230322202648617.png" style="zoom: 200%;" />

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230322202729557.png)

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230322202807980.png)

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20230322202857050.png)



# 单调栈

单调栈即从栈头到栈尾元素单调递增或递减的栈。

什么时候想到用单调栈？**通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了**。

## 739. 每日温度 [medium]

[739. 每日温度 - 力扣（LeetCode）](https://leetcode.cn/problems/daily-temperatures/)

**思路：** 

用一个单调递增栈来记录遍历过的数组。明确：单调递增栈是下面的元素 >= 上面的元素。如果新入栈的元素大于当前栈顶元素，就将栈顶逐一pop出直到新入栈的元素 <= 栈顶元素即可。

本题是要求右边第一个比它大的元素，故用单调递增栈。这样一来，当栈顶a元素被b元素挤出来，那么就可以说b就是右边第一个比a大的元素。那如果用下标代替元素本身入栈，那res[index(a)] = index(b) - index(a)。

**代码：**

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        vector<int> result(temperatures.size(), 0);
        st.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            if(temperatures[i] <= temperatures[st.top()]) st.push(i);
            else {
                while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }    
        }
        return result;
    }
};
```



## 496. 下一个更大元素 I [easy]

[496. 下一个更大元素 I - 力扣（LeetCode）](https://leetcode.cn/problems/next-greater-element-i/)

**思路：**

查找下一个更大元素的方法和上题一样，区别在于需要确定被挤掉的元素在nums[1]中的位置。这里我没采用map来实现：键为元素，值为下标

**代码：**

```c++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> umap;
        for (int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }

        vector<int> result(nums1.size(), -1);
        stack<int> sta;
        sta.push(nums2[0]);
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] <= sta.top()) sta.push(nums2[i]);
            else {
                while (!sta.empty() && nums2[i] > sta.top()) {
                    if (umap.count(sta.top()) > 0) { // 查看nums1里有没有这个元素
                        result[umap[sta.top()]] = nums2[i];
                    }
                    sta.pop();
                }
                sta.push(nums2[i]);
            }
        }
        return result;
    }
};
```



##  503. 下一个更大元素II [medium]

[503. 下一个更大元素 II - 力扣（LeetCode）](https://leetcode.cn/problems/next-greater-element-ii/)

**思路：**

环形数组，可以在数组后面续上相同的一份，以此来模拟环形队列（最多也就是找两圈嘛）。基本思路和上两题没差。

但其实也不用真的续上一节，只需在遍历时取模就行，详见代码。

**代码：**

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        stack<int> st;
        for (int i = 0; i < nums.size() * 2; i++) {
            // 模拟遍历两边nums，注意一下都是用i % nums.size()来操作
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};
```



## 42. 接雨水 [hard]

[42. 接雨水 - 力扣（LeetCode）](https://leetcode.cn/problems/trapping-rain-water/)

**思路：**

单调栈：

当一个柱子左右两边均有比他高的柱子时，我们就可以说这里是一个槽，假设左边第一个比他高的柱子下标为i，右边第一个比他高的柱子下标为j，那这个槽的高度为min(height[i], height[j]) - height[自己]，宽度为i - j - 1。

明白上面的原理就好办了：单调栈，如果栈高大于1的话，说明下面那个元素就是上面元素的左边最近的高于他的元素，而新入栈将要挤掉它的，就是右边最近的高于他的元素。

如果新入栈的元素和栈顶元素同样大，就要先pop再push，因为我们要求宽度的时候 如果遇到相同高度的柱子，需要使用最右边的柱子来计算宽度。

双指针 + 动规：

经过上面的分析我们知道，这道题核心的点在于：遍历到每一个元素时，**需要知道它左边与右边离他最近的那个高于他的柱子（如果有的话）**在哪里。

如果用朴素的双指针去做，就每遍历到一个元素，就向左向右去找，若有的话就用较矮的那个和它一减，得到这个柱子能盛多少水（这里只需考虑这个柱子本身）；没有的话就不能盛水。

可以用动规思想优化一下：我们把每一个位置的左边最高高度记录在一个数组上（maxLeft），右边最高高度记录在一个数组上（maxRight），当前位置，左边的最高高度是前一个位置的左边最高高度和本高度的最大值，右边同理。

**代码：**

单调栈：

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int result = 0;
        st.push(0);
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            } else if (height[i] == height[st.top()]){
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if(!st.empty()) {
                        int h = min(height[i], height[st.top()]) - height[mid];
                        int w = i - st.top() - 1;
                        result += h * w;
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
```

双指针：

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        int size = maxRight.size();

        // 记录每个柱子左边柱子最大高度
        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++) {
            maxLeft[i] = max(height[i], maxLeft[i - 1]);
        }
        // 记录每个柱子右边柱子最大高度
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);
        }
        // 求和
        int sum = 0;
        for (int i = 0; i < size; i++) {
            int count = min(maxLeft[i], maxRight[i]) - height[i];
            if (count > 0) sum += count;
        }
        return sum;
    }
};
```



## 84. 柱状图中最大的矩形 [hard]

[84. 柱状图中最大的矩形 - 力扣（LeetCode）](https://leetcode.cn/problems/largest-rectangle-in-histogram/)

**思路：**

和上道题很像，上道题是找每个元素左右两边第一个高的，这道题是找第一个低的。然后h * w算面积。

注意，最低的那个柱子，w应该是总长度，所以要该height两边补0。

**代码：**

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        st.push(0);

        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if(!st.empty()) {
                        int left = st.top();
                        int right = i;
                        int w = right - left - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
```



# 其他

## 13. 罗马数字转整数 [easy]

[13. 罗马数字转整数 - 力扣（LeetCode）](https://leetcode.cn/problems/roman-to-integer/)

**思路：**

从左往右查看字符串，每次看一个字符并与后面的字符比较，从而算出数值。

**代码思路：**

1. 首先建立罗马字母与整数的映射表（可以是hash表，也可以是case语句）
2. 从左到右遍历遍历字符串，取得当前位置与下一个位置的数值
3. 比较两个数值，确定是+还是-
4. 倒数第二个字符看完后，跳出循环，最后一个肯定是+

**代码：**

```java
class Solution {
	public int romanToInt(String s) {
		int result = 0;
		int preNum = getValue(s.charAt(0));

		for(int i = 1; i < s.length(); i++){
			int num = getValue(s.charAt(i));
        
			if(preNum < num){
				result -= preNum;
			}
			else{
				result += preNum;
			}
        
			preNum = num;
		}

		result += preNum;
		return result;

	}

	private int getValue(char ch){
		switch (ch){
			case 'I' : return 1;
			case 'V' : return 5;
			case 'X' : return 10;
			case 'L' : return 50;
			case 'C' : return 100;
			case 'D' : return 500;
			case 'M' : return 1000;
			default : return 0;
		}
	}
}
```

然后看到一个很秀的答案，贴一下：

```java
class Solution {
    public int romanToInt(String s) {
        s = s.replace("IV","a");
        s = s.replace("IX","b");
        s = s.replace("XL","c");
        s = s.replace("XC","d");
        s = s.replace("CD","e");
        s = s.replace("CM","f");
    
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            res += getValue(s.charAt(i));
        }
        return res;
    }

    public int getValue(char c) {
        switch(c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            case 'a': return 4;
            case 'b': return 9;
            case 'c': return 40;
            case 'd': return 90;
            case 'e': return 400;
            case 'f': return 900;
        }
        return 0;
    }
}
```

别问，问就是打表！



## 14. 最长公共前缀 [easy]

[14. 最长公共前缀 - 力扣（LeetCode）](https://leetcode.cn/problems/longest-common-prefix/)

**思路：**

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/14_fig2.png)

**代码思路：**

1. 以第一个单词为模板，遍历其中字母
2. 在遍历中嵌套遍历，比较剩下所有单词的相应位置字母是否与之相同（或是单词在该位置无字母）
3. 如遇到不相同的或到头的，则停止，记录当前遍历的位置，输出第一个单词到这个字母的字串即可。

**代码：**

```java
class Solution {
	public String longestCommonPrefix(String[] strs) {
		// 若其中无字符
		if (strs == null || strs.length == 0) {
			return "";
		}

		int length = strs[0].length();
		int count = strs.length;

		// 遍历第一个str的每个字母
		for(int i = 0; i < length; i++){
			char c = strs[0].charAt(i);

			// 比较后面每个strs的相应位字母
			for(int j = 1; j < count; j++){
				// 若比到该字符串的末尾（前面相同才会向后移动）或比到了不相同的字符
				if(i == strs[j].length() || strs[j].charAt(i) != c){
					return strs[0].substring(0, i);
				}
			}
		}

		return strs[0];

	}
}
```



## 9. 回文数 [easy]

[9. 回文数 - 力扣（LeetCode）](https://leetcode.cn/problems/palindrome-number/)

**思路：**

可以转换为字符串，用两个指针分别从两头开始比较。也可以借用栈的思想，开两个栈，比较栈顶元素（奇数位需去掉中间那个数字）。但还有一个更巧妙的方法就是直接求这个数字的倒序数，判断与原数是否相等即可。

**代码思路：**

1. 求目标的倒序数（求法见代）
2. 判断输出

（这很优雅😍）

**代码：**

```java
class Solution {
    public boolean isPalindrome(int x) {
		if(x < 0){
			return false;
		}
		int reversedNum = 0;
		int tempNum = x;
		while(tempNum != 0){
            // 这里是求倒序数，利用除以10取余得到原数最后一位，若最后一位为0则停止，这样也兼顾了诸如1200这样的情况。
			reversedNum = reversedNum * 10 + tempNum % 10;
			tempNum = tempNum / 10;
		}

		if(reversedNum == x){
			return true;
		}

		else{
			return false;
		}
	}
}
```



## 7. 求反转数 [medium]

[7. 整数反转 - 力扣（LeetCode）](https://leetcode.cn/problems/reverse-integer/)

第一道中等题，可喜可贺。

其实思路和上道一样的，看着差不多就做了，结果发现难点是在于那个溢出的判断。

**思路：**

求反转数思路看上题。至于如何判断溢出——

![](https://sunnyx-1306524139.cos.ap-chengdu.myqcloud.com/img/image-20220902182358609.png)

还是牛的，我没想到。

**代码思路：**

上道的基础上加一个判断，详见代码，此处略。

**代码：**

```java
class Solution {
    public int reverse(int x) {
        // 这里不涉及到与原数比较，就不用保留x了
		int reversedNum = 0;
    
		while(x != 0){
			int tempNum = x % 10;

			if(reversedNum > 214748364 || (reversedNum == 214748364 && tempNum > 7)) {
				return 0;
			}

			if(reversedNum < -214748364  || (reversedNum == -214748364 && tempNum < -8)) {
				return 0;
			}

			reversedNum = reversedNum * 10 + tempNum;
			x /= 10;
		}

		return reversedNum;
    }
}
```



# 剑指offer

## 剑指 Offer 03. 数组中重复的数字 [easy]

[剑指 Offer 03. 数组中重复的数字 - 力扣（LeetCode）](https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/?favorite=xb9nqhhg)

**思路：**

思路一：

哈希法，时间O(N) 空间O(N)

思路二：

长度为n的数组中元素大小为[0, n-1]，那既然如此，我们可以将见到的元素放到索引的位置，如果交换时，发现索引处已存在该元素，则重复 

时间O(N) 空间O(1)

**代码：**

哈希：

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> set;
        for(int i = 0; i < nums.size(); i++) {
            if(set.find(nums[i]) == set.end()) set.insert(nums[i]);
            else return nums[i];
        }
        return -1;
    }
};
```

方法二：

```c++
int findRepeatNumber(vector<int>& nums) {
    for(int i=0;i<nums.size();i++){
        while(nums[i]!=i){
            if(nums[nums[i]] == nums[i]) return nums[i];
            int tmp = nums[i];
            nums[i] = nums[tmp];
            nums[tmp] = tmp;
        }
    }
    return -1;
}
```



## 剑指 Offer 04. 二维数组中的查找 [medium]

[剑指 Offer 04. 二维数组中的查找 - 力扣（LeetCode）](https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/?favorite=xb9nqhhg)

**思路：**

一言以蔽之：站在矩阵右上角看，这是一颗搜索二叉树。

**代码：**

```c++
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;
        int row = 0;
        int col = matrix[0].size() - 1;
        while(row < matrix.size() && col >= 0) {
            if(matrix[row][col] > target) col --;
            else if (matrix[row][col] < target) row ++;
            else return true;
        }   
        return false;
    }
};
```



## [剑指 Offer 05. 替换空格 [easy]](#剑指Offer | 05. 替换空格 [easy])



## 剑指 Offer 06. 从尾到头打印链表 [easy]

[剑指 Offer 06. 从尾到头打印链表 - 力扣（LeetCode）](https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

**思路：**

看了三种方法

方法一：遍历链表，数值先存在栈中，再由栈导入数组，时间复杂度O(2n), 空间复杂度O(2n)

方法二：遍历链表，获取链表长度，预先声明定长数组，从后往前填。时间复杂度O(2n)，空间复杂度O(n)

方法三：遍历链表，直接正向存入数组，再用双指针反转。时间复杂度O(3/2n)，空间复杂度O(n)

**代码：**

```c++
//方法三
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        ListNode* cur = head;
        vector<int> result;
        while(cur != nullptr) {
            result.push_back(cur->val);
            cur = cur->next;
        }
        for (int i = 0; i < result.size() / 2; i++) {
            int tmp = result[i];
            result[i] = result[result.size() - 1 - i];
            result[result.size() - 1 - i] = tmp;
        }
        return result;
    }
};
```



## 剑指 Offer 09. 用两个栈实现队列 [easy]

[剑指 Offer 09. 用两个栈实现队列 - 力扣（LeetCode）](https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

**思路：**

维护两个栈，appendSta栈口模拟队尾，seleteSta栈口模拟队首。当调用队列的append方法时，像appendSta压入元素，此栈顶元素表示队尾元素；当调用队列的delete方法时，若deleteSta不为空，直接从该栈口pop（因为该栈口模拟队首），若为空，就将元素逐一从appendSta移到deleteSta（会首尾颠倒，这就是为什么deleteSta栈口是队首），再从deleteSta栈口pop。

**代码：**

```c++
class CQueue {
public:
    stack<int> appendSta;
    stack<int> deleteSta;
    CQueue() {
    }
    
    void appendTail(int value) {
        appendSta.push(value);
    }
    
    int deleteHead() {
        int result = -1;
        if (!deleteSta.empty()) {
            result = deleteSta.top();
            deleteSta.pop();
        } else {
            int tmp;
            while (!appendSta.empty()) {
                tmp = appendSta.top();
                appendSta.pop();
                deleteSta.push(tmp);
            }
            if (!deleteSta.empty()) {
                result = deleteSta.top();
                deleteSta.pop();
            }
        }
        return result;
    }
};
```



## [剑指 Offer 10- I. 斐波那契数列 [easy]](#509. 斐波那契数 [easy])



## 剑指 Offer 10- II. 青蛙跳台阶问题 [easy]

同[70. 爬楼梯 [easy]](#70. 爬楼梯 [easy])

 为什么要模1000000007（跟我念，一，八个零，七）。参考https://www.liuchuo.net/archives/645

大数相乘，大数的排列组合等为什么要取模

- 1000000007是一个质数（素数），对质数取余能最大程度避免结果冲突/重复
- int32位的最大值为2147483647，所以对于int32位来说1000000007足够大。
- int64位的最大值为2^63-1，用最大值模1000000007的结果求平方，不会在int64中溢出。
- 所以在大数相乘问题中，因为(a∗b)%c=((a%c)∗(b%c))%c，所以相乘时两边都对1000000007取模，再保存在int64里面不会溢出。

这道题为什么要取模，取模前后的值不就变了吗？

- 确实：取模前 f(43) = 701408733, f(44) = 1134903170, f(45) = 1836311903, 但是 f(46) > 2147483647结果就溢出了。
- _____，取模后 f(43) = 701408733, f(44) = 134903163 , f(45) = 836311896, f(46) = 971215059没有溢出。
- 取模之后能够计算更多的情况，如 f(46)
- 这道题的测试答案与取模后的结果一致。
- 总结一下，这道题要模1000000007的根本原因是标准答案模了1000000007。不过大数情况下为了防止溢出，模1000000007是通用做法，原因见第一点。



## 剑指 Offer 11. 旋转数组的最小数字 [easy]

[剑指 Offer 11. 旋转数组的最小数字 - 力扣（LeetCode）](https://leetcode.cn/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)

**思路：**

有序数组，二分法。

所谓旋转，可以看做是数组由两个有序数组拼接而成，其中第一个有序数组的首数字一定比第二个有序数组的首数字来的大，所以只需找到第二个有序数组的起点在哪里就可以了。

```
i = 0; 
j = nums.size() - 1; 
m = (i + j) / 2;
```

如果nums[m] < nums[j]，此时可以断定m一定是在第二个有序数组中，所以搜索范围缩小到[i, m]

如果nums[m] > nums[j]，此时可以断定m一定是在第一个有序数组中，所以搜索范围缩小到[m + 1, j]

如果nums[m] = nums[j]，此时无法断定m在哪个有序数组中，但可以肯定的是删掉nums[j]并不影响我们找最小值（就算它是第二个有序数组的起点）

**代码：**

```c++
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
```









## [剑指 Offer 24. 反转链表 [easy]](#剑指 Offer 24. 反转链表) 



## 剑指 Offer 26. 树的子结构 [medium]

[剑指 Offer 26. 树的子结构 - 力扣（LeetCode）](https://leetcode.cn/problems/shu-de-zi-jie-gou-lcof/)

**思路：**

两棵树同时进行对称的前序遍历（要先比较根节点），比较每个结点是否相等。

从哪里开始前序遍历呢？在A中找到一个和B根节点相等的结点，看看以这两个结点为根节点的树是否相等。

**代码：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == nullptr || B == nullptr) return false; // 空树不是任意树的子树
        if (isEqual(A, B)) return true; // 如果以A、B为根节点的两棵树相等，返回true
        else return isSubStructure(A->left, B) || isSubStructure(A->right, B); // 否则检查A的左子树、右子树是否有和B相等的树（前序）
    }

    // 比较以A、B为根节点的树是否相等
    bool isEqual(TreeNode* A, TreeNode* B) {
        if (B == nullptr) return true; // 终止条件：B比到了空节点，说明上面的结点都匹配上了
        if (A == nullptr) return false; // 终止条件：A比到了空节点但B还有，说明不匹配
        if (A->val == B->val) return isEqual(A->left, B->left) && isEqual(A->right, B->right); // 前序
        else return false; // 发现不相等，直接终止
    }
};
```



## [剑指 Offer 27. 二叉树的镜像 [easy]](#266. 翻转二叉树 [easy])



## [剑指 Offer 28. 对称的二叉树 [easy]](#101. 对称二叉树 [easy])



## 剑指 Offer 30. 包含min函数的栈 [easy]

[剑指 Offer 30. 包含min函数的栈 - 力扣（LeetCode）](https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/)

**思路：**

当栈顶数字确定时，那么当前栈内最小值就是唯一的。因为栈顶元素之前的元素肯定都在栈里。

所以我们再维护一个栈，去记录当栈顶为当前数字的情况下，最小值是多少。

**代码：**

```c++
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> sta;
    stack<int> minsta;
    MinStack() {
    }
    
    void push(int x) {
        sta.push(x);
        if (minsta.empty()) {
            minsta.push(x);
        } else minsta.push(::min(x, minsta.top()));
    }
    
    void pop() {
        sta.pop();
        minsta.pop();
    }
    
    int top() {
        return sta.top();
    }
    
    int min() {
        return minsta.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
```



## 剑指 Offer 32 - I. 从上到下打印二叉树 [medium]

[剑指 Offer 32 - I. 从上到下打印二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof/)

**思路：**

层序遍历，写不出来进厂吧

**代码：**

```c++
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> result;
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        while (!que.empty()) {
            TreeNode* node = que.front();
            result.push_back(node->val);
            que.pop();
            if (node->left != nullptr) que.push(node->left);
            if (node->right != nullptr) que.push(node->right);
        }
        return result;
    }
};
```



## [剑指 Offer 32 - II. 从上到下打印二叉树 II [easy]](#102. 二叉树的层序遍历 [medium])



## 剑指 Offer 32 - III. 从上到下打印二叉树 III [medium]

[剑指 Offer 32 - III. 从上到下打印二叉树 III - 力扣（LeetCode）](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/)

**思路：**

需要一个标志位标记当前结点处于单数层还是双数层。

单数层从队首读结点，子节点从左到右插入队尾；双数层从队尾读结点，子节点从右到左插入队首。

**代码：**

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        deque<TreeNode*> que;
        vector<vector<int>> result;
        bool flag = true; 
        if (root != nullptr) que.push_back(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i ++) {
                if (flag) { // true代表单数层，此时从队首读，其子结点从左到右加入队尾
                    TreeNode* node = que.front();
                    que.pop_front();
                    vec.push_back(node->val);
                    if (node->left != nullptr) que.push_back(node->left);
                    if (node->right != nullptr) que.push_back(node->right);
                } else { // false代表双数层，此时从队尾读，其子节点从右到左加入队头
                    TreeNode* node = que.back();
                    que.pop_back();
                    vec.push_back(node->val);
                    if(node->right != nullptr) que.push_front(node->right);
                    if(node->left != nullptr) que.push_front(node->left);
                } 
            }
            result.push_back(vec);
            flag = !flag;
        }
        return result;
    }
};
```





## 剑指 Offer 35. 复杂链表的复制 [medium]

[剑指 Offer 35. 复杂链表的复制 - 力扣（LeetCode）](https://leetcode.cn/problems/fu-za-lian-biao-de-fu-zhi-lcof/)

**思路：**

若顺序创建新链表，会导致next指针和随机指针没有被创建的情况。

所以我们用回溯的方式创建链表，若检查到该结点的next和random没被创建，就先创建，然后返回该结点的指针即可。

**代码：**

```c++
class Solution {
public:
    unordered_map<Node*, Node*> map;
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        if (!map.count(head)) {
            Node* newHead = new Node(head->val);
            map[head] = newHead;
            newHead->next = copyRandomList(head->next);
            newHead->random = copyRandomList(head->random);
        }
        return map[head];
    }
};
```



## [剑指 Offer 42. 连续子数组的最大和 [easy]](#53. 最大子序和 [medium])



## 剑指 Offer 47. 礼物的最大价值 [medium]

[剑指 Offer 47. 礼物的最大价值 - 力扣（LeetCode）](https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof/)

**思路：**

最朴素的二维dp

1. dp数组以及下标的含义

   dp\[i][j]：走到grid\[i][j]所能拿到的最大价值。

2. 确定递推公式

   grid\[i][j]只能由grid\[i-1][j]与grid\[i][j-1]走来，所以：

   ```c++
   dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
   ```

3. dp数组如何初始化

   由左方与上方推出，所以要初始化第一行与第一列：

   ```c++
   dp[0][0] = grid[0][0];
   for(int i = 1; i < m; i++) {
   	dp[i][0] = dp[i - 1][0] + grid[i][0];
   }
   for(int j = 1; j < n; j++) {
   	dp[0][j] = dp[0][j - 1] + grid[0][j];
   }
   ```

4. 确定遍历顺序

   从左到右，从上到下

5. 举例推导dp数组

   略

**代码：**

```c++
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        dp[0][0] = grid[0][0];
        for(int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for(int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```



## 剑指 Offer 50. 第一个只出现一次的字符 [easy]

[剑指 Offer 50. 第一个只出现一次的字符 - 力扣（LeetCode）](https://leetcode.cn/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/comments/)

**思路：**

考察对哈希表（map）的使用。本体采用<char, bool>

先遍历一遍字符串，如果字符只出现一次，其对应的值就是true；

再遍历一遍字符串，找到第一个值为true的键

**代码：**

```c++
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, bool> dic;
        for(char c : s)
            dic[c] = dic.find(c) == dic.end(); // true说明还没出现过
        for(char c : s)
            if(dic[c]) return c;
        return ' ';
    }
};
```



## 剑指 Offer 53 - I. 在排序数组中查找数字 I [easy]

[剑指 Offer 53 - I. 在排序数组中查找数字 I - 力扣（LeetCode）](https://leetcode.cn/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)

**思路：**

二分法找到mid等于target，此时所有target都被包含在[left, right]里。

找到等于的边界，左右缩短再重新使用二分。

**代码：**

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                if (nums[left] != target) left ++;
                else if (nums[right] != target) right --;
                else break;
            }
        }
        return right - left + 1;
    }
};
```



## 剑指 Offer 53 - II. 0～n-1中缺失的数字 [easy]

[剑指 Offer 53 - II. 0～n-1中缺失的数字 - 力扣（LeetCode）](https://leetcode.cn/problems/que-shi-de-shu-zi-lcof/)

**思路：**

有序数组用二分

**代码：**

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int left = 0;
        int right = nums.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] != mid) {
                right = mid;
            } else left = mid + 1;
        }
        return left;
    }
};
```



## [剑指 Offer 58 - II. 左旋转字符串 [easy]](#剑指Offer | 58-II.左旋转字符串 [easy])



## [剑指 Offer 63. 股票的最大利润 [medium]](#121. 买卖股票的最佳时机 [easy])
