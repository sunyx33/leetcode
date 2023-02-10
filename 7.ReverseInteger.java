//给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。 
//
// 如果反转后整数超过 32 位的有符号整数的范围 [−2³¹, 231 − 1] ，就返回 0。 
//假设环境不允许存储 64 位整数（有符号或无符号）。
//
// 
//
// 示例 1： 
//
// 
//输入：x = 123
//输出：321
// 
//
// 示例 2： 
//
// 
//输入：x = -123
//输出：-321
// 
//
// 示例 3： 
//
// 
//输入：x = 120
//输出：21
// 
//
// 示例 4： 
//
// 
//输入：x = 0
//输出：0
// 
//
// 
//
// 提示： 
//
// 
// -2³¹ <= x <= 2³¹ - 1 
// 
// Related Topics 数学 👍 3614 👎 0


package leetcode.editor.cn;

/**
 * 整数反转
 * @author Sunnyx
 * @date 2022-09-02 17:53:22
 */
public class P7_ReverseInteger{
	 public static void main(String[] args) {
	 	 //测试代码
	 	 Solution solution = new P7_ReverseInteger().new Solution();
		 solution.reverse(1123456789);
	 }
	 
//力扣代码
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    public int reverse(int x) {
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
//leetcode submit region end(Prohibit modification and deletion)

}
