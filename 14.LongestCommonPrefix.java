//编写一个函数来查找字符串数组中的最长公共前缀。 
//
// 如果不存在公共前缀，返回空字符串 ""。 
//
// 
//
// 示例 1： 
//
// 
//输入：strs = ["flower","flow","flight"]
//输出："fl"
// 
//
// 示例 2： 
//
// 
//输入：strs = ["dog","racecar","car"]
//输出：""
//解释：输入不存在公共前缀。 
//
// 
//
// 提示： 
//
// 
// 1 <= strs.length <= 200 
// 0 <= strs[i].length <= 200 
// strs[i] 仅由小写英文字母组成 
// 
// Related Topics 字符串 👍 2341 👎 0


package leetcode.editor.cn;

/**
 * 最长公共前缀
 * @author DY
 * @date 2022-07-16 21:50:07
 */
public class P14_LongestCommonPrefix{
	public static void main(String[] args) {
		//测试代码
		Solution solution = new P14_LongestCommonPrefix().new Solution();
	}

	//力扣代码
//leetcode submit region begin(Prohibit modification and deletion)
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
//leetcode submit region end(Prohibit modification and deletion)

}
