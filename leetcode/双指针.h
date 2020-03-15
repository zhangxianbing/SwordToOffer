/*
 * @Author: zhangxianbing
 * @Date: 2019-08-12 20:24:17
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-18 16:26:39
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 双指针
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

// LC11. 盛最多水的容器
namespace LC11 {
int maxArea(vector<int> &height) {
  int l = 0, lMax = l, r = height.size() - 1, rMax = r;
  int V = min(height[lMax], height[rMax]) * (rMax - lMax);
  while (l < r) {
    if (height[lMax] > height[rMax]) {
      do {
        r--;
      } while (r > l && height[r] <= height[rMax]);
      rMax = r;
    } else {
      do {
        l++;
      } while (l < r && height[l] <= height[lMax]);
      lMax = l;
    }
    V = max(V, min(height[lMax], height[rMax]) * (rMax - lMax));
  }
  return V;
}
} // namespace LC11

// LC42. 接雨水
namespace LC42 {
int trap(vector<int> &height) {}
} // namespace LC42

// LC15. 三数之和
namespace LC15 {} // namespace LC15

// LC713. 乘积小于K的子数组
namespace LC713 {} // namespace LC713

// LC1004. 最大连续1的个数 III
namespace LC1004 {} // namespace LC1004

// LC632. 最小区间
namespace LC632 {} // namespace LC632

// LC487. 最大连续1的个数 II
namespace LC487 {} // namespace LC487

// LC159. 至多包含两个不同字符的最长子串
namespace LC159 {} // namespace LC159

// LC88. 合并两个有序数组
namespace LC88 {} // namespace LC88

// LC838. 推多米诺
namespace LC838 {} // namespace LC838

// LC19. 删除链表的倒数第N个节点
namespace LC19 {} // namespace LC19

// LC457. 环形数组循环
namespace LC457 {} // namespace LC457

// LC930. 和相同的二元子数组
namespace LC930 {} // namespace LC930

// LC18. 四数之和
namespace LC18 {} // namespace LC18

// LC76. 最小覆盖子串
namespace LC76 {} // namespace LC76

// LC16. 最接近的三数之和
namespace LC16 {} // namespace LC16

// LC141. 环形链表
namespace LC141 {} // namespace LC141

// LC344. 反转字符串
namespace LC344 {} // namespace LC344

// LC992. K 个不同整数的子数组
namespace LC992 {} // namespace LC992

// LC234. 回文链表
namespace LC234 {} // namespace LC234

// LC845. 数组中的最长山脉
namespace LC845 {} // namespace LC845

// LC30. 串联所有单词的子串
namespace LC30 {} // namespace LC30

// LC167. 两数之和 II - 输入有序数组
namespace LC167 {} // namespace LC167

// LC881. 救生艇
namespace LC881 {} // namespace LC881

// LC287. 寻找重复数
namespace LC287 {} // namespace LC287

// LC923. 三数之和的多种可能
namespace LC923 {} // namespace LC923

// LC28. 实现 strStr()
namespace LC28 {} // namespace LC28

// LC26. 删除排序数组中的重复项
namespace LC26 {} // namespace LC26

// LC567. 字符串的排列
namespace LC567 {} // namespace LC567

// LC349. 两个数组的交集
namespace LC349 {} // namespace LC349

// LC125. 验证回文串
namespace LC125 {} // namespace LC125

// LC977. 有序数组的平方
namespace LC977 {} // namespace LC977

// LC524. 通过删除字母匹配到字典里最长单词
namespace LC524 {} // namespace LC524

// LC826. 安排工作以达到最大收益
namespace LC826 {} // namespace LC826

// LC350. 两个数组的交集 II
namespace LC350 {} // namespace LC350

// LC61. 旋转链表
namespace LC61 {} // namespace LC61

// LC209. 长度最小的子数组
namespace LC209 {} // namespace LC209

// LC283. 移动零
namespace LC283 {
void moveZeroes(vector<int> &nums) {
  int i = 0, j = 0, n = nums.size();
  for (; i < n; i++)
    if (nums[i])
      nums[j++] = nums[i];
  for (i = j; i < n; i++)
    nums[i] = 0;
}
} // namespace LC283

// LC142. 环形链表 II
namespace LC142 {} // namespace LC142

// LC75. 颜色分类
namespace LC75 {} // namespace LC75

// LC424. 替换后的最长重复字符
namespace LC424 {} // namespace LC424

// LC345. 反转字符串中的元音字母
namespace LC345 {} // namespace LC345

// LC532. 数组中的K-diff数对
namespace LC532 {} // namespace LC532

// LC27. 移除元素
namespace LC27 {} // namespace LC27

// LC844. 比较含退格的字符串
namespace LC844 {} // namespace LC844

// LC763. 划分字母区间
namespace LC763 {} // namespace LC763

// LC86. 分隔链表
namespace LC86 {} // namespace LC86

// LC80. 删除排序数组中的重复项 II
namespace LC80 {} // namespace LC80

// LC1093. 大样本统计
namespace LC1093 {} // namespace LC1093

// LC986. 区间列表的交集
namespace LC986 {} // namespace LC986

// LC925. 长按键入
namespace LC925 {} // namespace LC925

// LC904. 水果成篮
namespace LC904 {} // namespace LC904

// LC828. 独特字符串
namespace LC828 {} // namespace LC828

// LC723. 粉碎糖果
namespace LC723 {} // namespace LC723

// LC360. 有序转化数组
namespace LC360 {} // namespace LC360

// LC259. 较小的三数之和
namespace LC259 {} // namespace LC259
