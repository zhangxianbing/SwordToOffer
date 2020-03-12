/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:50
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-13 10:08:06
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 数组 & 多指针问题
//# 此类问题尽可能只遍历一遍数组以达到原地改变原数组
//# 1.双指针之前后指针，遍历数组的指针在前，更新数组的指针在后。此方法适合情景：剔除原数组中不合要求的元素，留下符合要求的元素，如：LC26，LC27，LC283
//# 2.双指针之对撞指针，LC167，LC125
//# 3.三指针，遍历指针+两个对撞指针，实际是1，2的延伸，典型的如快排、归并排序的子过程操作，LC75，LC88，LC215
//# 4.滑动窗口，也属于双指针，LC209
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 前后指针
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC26. 删除排序数组中的重复项
namespace LC26 {
int removeDuplicates(vector<int> &nums) {
  if (nums.empty())
    return 0;
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != nums[j]) {
      nums[++j] = nums[i];
    }
  }
  return j + 1;
}
} // namespace LC26

// LC80. 删除排序数组中的重复项 II
namespace LC80 {
int removeDuplicates(vector<int> &nums) {
  if (nums.size() <= 2)
    return nums.size();
  int index = 2;
  for (int i = 2; i < nums.size(); i++) {
    if (nums[i] != nums[index - 2])
      nums[index++] = nums[i];
  }
  return index;
}
} // namespace LC80

// LC27. 移除元素
namespace LC27 {
int removeElement(vector<int> &nums, int val) {
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != val) {
      nums[j++] = nums[i];
    }
  }

  return j;
}
} // namespace LC27
// LC283. 移动零
namespace LC283 {
void moveZeroes(vector<int> &nums) {
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0) {
      if (j < i)
        nums[j] = nums[i]; // 优化1：减少不必要的赋值
      j++;
    }
  }
  for (; j < nums.size(); j++) {
    nums[j] = 0;
  }
}
} // namespace LC283

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 对撞指针
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC167. 两数之和 II - 输入有序数组 (对撞指针)
namespace LC167 {
vector<int> twoSum(vector<int> &nums, int target) {
  int n = nums.size(), l = 0, r = n - 1;
  while (l < r) {
    int s = nums[l] + nums[r];
    if (s < target)
      l++;
    else if (s > target)
      r--;
    else
      break;
  }
  return {l + 1, r + 1};
}
} // namespace LC167

// LC125. 验证回文串 (对撞指针)
namespace LC125 {
bool isPalindrome(string s) {
  int n = s.size(), l = 0, r = n - 1;
  while (l < r) {
    while (l < n && !isalnum(s[l]))
      l++;
    if (l == n)
      break;
    while (!isalnum(s[r]))
      r--;
    if ((s[l++] & 0xDF) != (s[r--] & 0xDF))
      return false;
  }
  return true;
}
} // namespace LC125

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 三指针
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC75. 颜色分类 （快排子过程）
namespace LC75 {
void sortColors(vector<int> &nums) {
  int n = nums.size();
  if (n <= 1)
    return;
  int l = -1, r = n, i = 0;
  while (i < r) {
    if (nums[i] == 0)
      swap(nums[++l], nums[i++]);
    else if (nums[i] == 1)
      i++;
    else if (nums[i] == 2)
      swap(nums[--r], nums[i]);
  }
}
} // namespace LC75

// LC215. 数组中的第K个最大元素 (利用快排)
namespace LC215 {
int findKthLargest(vector<int> &nums, int l, int r, int K) {
  int i = l - 1, j = r + 1, k = l;
  int ref = nums[l];
  while (k < j) {
    if (nums[k] < ref)
      swap(nums[++i], nums[k++]);
    else if (nums[k] > ref)
      swap(nums[--j], nums[k]);
    else
      k++;
  }
  if (K <= i)
    return findKthLargest(nums, l, i, K);
  if (K >= j)
    return findKthLargest(nums, j, r, K);
  return nums[i + 1];
}
int findKthLargest(vector<int> &nums, int K) {
  return findKthLargest(nums, 0, nums.size() - 1, nums.size() - K);
}
} // namespace LC215

// LC122. 买卖股票的最佳时机 II
namespace LC122 {
int maxProfit(vector<int> &prices) {
  int ret = 0;
  for (int i = 1; i < prices.size(); i++) {
    int delta = prices[i] - prices[i - 1];
    ret += delta > 0 ? delta : 0;
  }
  return ret;
}
} // namespace LC122

// LC1. 两数之和
namespace LC1 {} // namespace LC1

// LC4. 寻找两个有序数组的中位数
namespace LC4 {} // namespace LC4

// LC11. 盛最多水的容器
namespace LC11 {} // namespace LC11

// LC15. 三数之和
namespace LC15 {} // namespace LC15

// LC16. 最接近的三数之和
namespace LC16 {} // namespace LC16

// LC18. 四数之和
namespace LC18 {} // namespace LC18

// LC27. 移除元素
namespace LC27 {} // namespace LC27

// LC31. 下一个排列
namespace LC31 {} // namespace LC31

// LC33. 搜索旋转排序数组
namespace LC33 {} // namespace LC33

// LC34. 在排序数组中查找元素的第一个和最后一个位置
namespace LC34 {} // namespace LC34

// LC35. 搜索插入位置
namespace LC35 {} // namespace LC35

// LC39. 组合总和
namespace LC39 {} // namespace LC39

// LC40. 组合总和 II
namespace LC40 {} // namespace LC40

// LC41. 缺失的第一个正数
namespace LC41 {} // namespace LC41

// LC42. 接雨水
namespace LC42 {} // namespace LC42

// LC45. 跳跃游戏 II
namespace LC45 {} // namespace LC45

// LC48. 旋转图像
namespace LC48 {} // namespace LC48

// LC53. 最大子序和
namespace LC53 {} // namespace LC53

// LC54. 螺旋矩阵
namespace LC54 {} // namespace LC54

// LC55. 跳跃游戏
namespace LC55 {} // namespace LC55

// LC56. 合并区间
namespace LC56 {} // namespace LC56

// LC57. 插入区间
namespace LC57 {} // namespace LC57

// LC59. 螺旋矩阵 II
namespace LC59 {} // namespace LC59

// LC62. 不同路径
namespace LC62 {} // namespace LC62

// LC63. 不同路径 II
namespace LC63 {} // namespace LC63

// LC64. 最小路径和
namespace LC64 {} // namespace LC64

// LC66. 加一
namespace LC66 {} // namespace LC66

// LC73. 矩阵置零
namespace LC73 {} // namespace LC73

// LC74. 搜索二维矩阵
namespace LC74 {} // namespace LC74

// LC78. 子集
namespace LC78 {} // namespace LC78

// LC79. 单词搜索
namespace LC79 {} // namespace LC79

// LC80. 删除排序数组中的重复项 II
namespace LC80 {} // namespace LC80

// LC81. 搜索旋转排序数组 II
namespace LC81 {} // namespace LC81

// LC84. 柱状图中最大的矩形
namespace LC84 {} // namespace LC84

// LC85. 最大矩形
namespace LC85 {} // namespace LC85

// LC88. 合并两个有序数组
namespace LC88 {} // namespace LC88

// LC90. 子集 II
namespace LC90 {} // namespace LC90

// LC105. 从前序与中序遍历序列构造二叉树
namespace LC105 {} // namespace LC105

// LC106. 从中序与后序遍历序列构造二叉树
namespace LC106 {} // namespace LC106

// LC118. 杨辉三角
namespace LC118 {} // namespace LC118

// LC119. 杨辉三角 II
namespace LC119 {} // namespace LC119

// LC120. 三角形最小路径和
namespace LC120 {} // namespace LC120

// LC126. 单词接龙 II
namespace LC126 {} // namespace LC126

// LC128. 最长连续序列
namespace LC128 {} // namespace LC128

// LC152. 乘积最大子序列
namespace LC152 {} // namespace LC152

// LC153. 寻找旋转排序数组中的最小值
namespace LC153 {} // namespace LC153

// LC154. 寻找旋转排序数组中的最小值 II
namespace LC154 {} // namespace LC154

// LC162. 寻找峰值
namespace LC162 {} // namespace LC162

// LC163. 缺失的区间
namespace LC163 {} // namespace LC163

// LC169. 求众数
namespace LC169 {} // namespace LC169

// LC189. 旋转数组
namespace LC189 {
void rotate(vector<int> &nums, int k) {
  if (nums.empty())
    return;
  k = k % nums.size();
  reverse(nums.begin(), nums.end());
  reverse(nums.begin(), nums.begin() + k);
  reverse(nums.begin() + k, nums.end());
}
} // namespace LC189

// LC209. 长度最小的子数组
namespace LC209 {} // namespace LC209

// LC216. 组合总和 III
namespace LC216 {} // namespace LC216

// LC217. 存在重复元素
namespace LC217 {} // namespace LC217

// LC219. 存在重复元素 II
namespace LC219 {} // namespace LC219

// LC228. 汇总区间
namespace LC228 {} // namespace LC228

// LC229. 求众数 II
namespace LC229 {} // namespace LC229

// LC238. 除自身以外数组的乘积
namespace LC238 {} // namespace LC238

// LC243. 最短单词距离
namespace LC243 {} // namespace LC243

// LC245. 最短单词距离 III
namespace LC245 {} // namespace LC245

// LC259. 较小的三数之和
namespace LC259 {} // namespace LC259

// LC268. 缺失数字
namespace LC268 {} // namespace LC268

// LC277. 搜寻名人
namespace LC277 {} // namespace LC277

// LC280. 摆动排序
namespace LC280 {} // namespace LC280

// LC287. 寻找重复数
namespace LC287 {} // namespace LC287

// LC289. 生命游戏
namespace LC289 {} // namespace LC289

// LC370. 区间加法
namespace LC370 {} // namespace LC370

// LC380. 常数时间插入、删除和获取随机元素
namespace LC380 {} // namespace LC380

// LC381. O(1) 时间插入、删除和获取随机元素 - 允许重复
namespace LC381 {} // namespace LC381

// LC414. 第三大的数
namespace LC414 {} // namespace LC414

// LC442. 数组中重复的数据
namespace LC442 {} // namespace LC442

// LC448. 找到所有数组中消失的数字
namespace LC448 {} // namespace LC448

// LC457. 环形数组循环
namespace LC457 {} // namespace LC457

// LC485. 最大连续1的个数
namespace LC485 {} // namespace LC485

// LC495. 提莫攻击
namespace LC495 {} // namespace LC495

// LC531. 孤独像素 I
namespace LC531 {} // namespace LC531

// LC532. 数组中的K-diff数对
namespace LC532 {} // namespace LC532

// LC533. 孤独像素 II
namespace LC533 {} // namespace LC533

// LC548. 将数组分割成和相等的子数组
namespace LC548 {} // namespace LC548

// LC560. 和为K的子数组
namespace LC560 {} // namespace LC560

// LC561. 数组拆分 I
namespace LC561 {} // namespace LC561

// LC562. 矩阵中最长的连续1线段
namespace LC562 {} // namespace LC562

// LC565. 数组嵌套
namespace LC565 {} // namespace LC565

// LC566. 重塑矩阵
namespace LC566 {} // namespace LC566

// LC581. 最短无序连续子数组
namespace LC581 {} // namespace LC581

// LC605. 种花问题
namespace LC605 {} // namespace LC605

// LC611. 有效三角形的个数
namespace LC611 {} // namespace LC611

// LC621. 任务调度器
namespace LC621 {} // namespace LC621

// LC624. 数组列表中的最大距离
namespace LC624 {} // namespace LC624

// LC628. 三个数的最大乘积
namespace LC628 {} // namespace LC628

// LC643. 子数组最大平均数 I
namespace LC643 {} // namespace LC643

// LC644. 最大平均子段和 II
namespace LC644 {} // namespace LC644

// LC661. 图片平滑器
namespace LC661 {} // namespace LC661

// LC665. 非递减数列
namespace LC665 {} // namespace LC665

// LC667. 优美的排列 II
namespace LC667 {} // namespace LC667

// LC670. 最大交换
namespace LC670 {} // namespace LC670

// LC674. 最长连续递增序列
namespace LC674 {} // namespace LC674

// LC689. 三个无重叠子数组的最大和
namespace LC689 {} // namespace LC689

// LC695. 岛屿的最大面积
namespace LC695 {} // namespace LC695

// LC697. 数组的度
namespace LC697 {} // namespace LC697

// LC713. 乘积小于K的子数组
namespace LC713 {} // namespace LC713

// LC714. 买卖股票的最佳时机含手续费
namespace LC714 {} // namespace LC714

// LC717. 1比特与2比特字符
namespace LC717 {} // namespace LC717

// LC718. 最长重复子数组
namespace LC718 {} // namespace LC718

// LC719. 找出第 k 小的距离对
namespace LC719 {} // namespace LC719

// LC723. 粉碎糖果
namespace LC723 {} // namespace LC723

// LC724. 寻找数组的中心索引
namespace LC724 {} // namespace LC724

// LC729. 我的日程安排表 I
namespace LC729 {} // namespace LC729

// LC747. 至少是其他数字两倍的最大数
namespace LC747 {} // namespace LC747

// LC755. 倒水
namespace LC755 {} // namespace LC755

// LC766. 托普利茨矩阵
namespace LC766 {} // namespace LC766

// LC768. 最多能完成排序的块 II
namespace LC768 {} // namespace LC768

// LC769. 最多能完成排序的块
namespace LC769 {} // namespace LC769

// LC775. 全局倒置与局部倒置
namespace LC775 {} // namespace LC775

// LC782. 变为棋盘
namespace LC782 {} // namespace LC782

// LC792. 匹配子序列的单词数
namespace LC792 {} // namespace LC792

// LC795. 区间子数组个数
namespace LC795 {} // namespace LC795

// LC825. 适龄的朋友
namespace LC825 {} // namespace LC825

// LC830. 较大分组的位置
namespace LC830 {} // namespace LC830

// LC832. 翻转图像
namespace LC832 {} // namespace LC832

// LC835. 图像重叠
namespace LC835 {} // namespace LC835

// LC840. 矩阵中的幻方
namespace LC840 {} // namespace LC840

// LC849. 到最近的人的最大距离
namespace LC849 {} // namespace LC849

// LC867. 转置矩阵
namespace LC867 {} // namespace LC867

// LC870. 优势洗牌
namespace LC870 {} // namespace LC870

// LC873. 最长的斐波那契子序列的长度
namespace LC873 {} // namespace LC873

// LC888. 公平的糖果交换
namespace LC888 {} // namespace LC888

// LC891. 子序列宽度之和
namespace LC891 {} // namespace LC891

// LC896. 单调数列
namespace LC896 {} // namespace LC896

// LC900. RLE 迭代器
namespace LC900 {} // namespace LC900

// LC905. 按奇偶排序数组
namespace LC905 {} // namespace LC905

// LC907. 子数组的最小值之和
namespace LC907 {} // namespace LC907

// LC914. 卡牌分组
namespace LC914 {} // namespace LC914

// LC915. 分割数组
namespace LC915 {} // namespace LC915

// LC918. 环形子数组的最大和
namespace LC918 {} // namespace LC918

// LC922. 按奇偶排序数组 II
namespace LC922 {} // namespace LC922

// LC926. 将字符串翻转到单调递增
namespace LC926 {} // namespace LC926

// LC941. 有效的山脉数组
namespace LC941 {} // namespace LC941

// LC945. 使数组唯一的最小增量
namespace LC945 {} // namespace LC945

// LC950. 按递增顺序显示卡牌
namespace LC950 {} // namespace LC950

// LC954. 二倍数对数组
namespace LC954 {} // namespace LC954

// LC962. 最大宽度坡
namespace LC962 {} // namespace LC962

// LC969. 煎饼排序
namespace LC969 {} // namespace LC969

// LC974. 和可被 K 整除的子数组
namespace LC974 {} // namespace LC974

// LC977. 有序数组的平方
namespace LC977 {} // namespace LC977

// LC978. 最长湍流子数组
namespace LC978 {} // namespace LC978

// LC985. 查询后的偶数和
namespace LC985 {} // namespace LC985

// LC989. 数组形式的整数加法
namespace LC989 {} // namespace LC989

// LC999. 车的可用捕获量
namespace LC999 {} // namespace LC999

// LC1002. 查找常用字符
namespace LC1002 {} // namespace LC1002

// LC1007. 行相等的最少多米诺旋转
namespace LC1007 {} // namespace LC1007

// LC1010. 总持续时间可被 60 整除的歌曲
namespace LC1010 {} // namespace LC1010

// LC1011. 在 D 天内送达包裹的能力
namespace LC1011 {} // namespace LC1011

// LC1013. 将数组分成和相等的三个部分
namespace LC1013 {} // namespace LC1013

// LC1014. 最佳观光组合
namespace LC1014 {} // namespace LC1014

// LC1064. 不动点
namespace LC1064 {} // namespace LC1064

// LC1018. 可被 5 整除的二进制前缀
namespace LC1018 {} // namespace LC1018

// LC1086. 前五科的均分
namespace LC1086 {} // namespace LC1086

// LC1085. 最小元素各数位之和
namespace LC1085 {} // namespace LC1085

// LC1099. 小于 K 的两数之和
namespace LC1099 {} // namespace LC1099

// LC1031. 两个非重叠子数组的最大和
namespace LC1031 {} // namespace LC1031

// LC1133. 最大唯一数
namespace LC1133 {} // namespace LC1133

// LC1035. 不相交的线
namespace LC1035 {} // namespace LC1035

// LC1040. 移动石子直到连续 II
namespace LC1040 {} // namespace LC1040

// LC1051. 高度检查器
namespace LC1051 {} // namespace LC1051

// LC1052. 爱生气的书店老板
namespace LC1052 {} // namespace LC1052

// LC1053. 交换一次的先前排列
namespace LC1053 {} // namespace LC1053

// LC1074. 元素和为目标值的子矩阵数量
namespace LC1074 {} // namespace LC1074

// LC1089. 复写零
namespace LC1089 {} // namespace LC1089

// LC1122. 数组的相对排序
namespace LC1122 {} // namespace LC1122

// LC1144. 递减元素使数组呈锯齿状
namespace LC1144 {} // namespace LC1144

// LC1146. 快照数组
namespace LC1146 {} // namespace LC1146
