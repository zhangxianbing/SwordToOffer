/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:37:21
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-13 18:14:42
 * @Description: file content
 */
#pragma once
#include "../public.h"

//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 动态规划
//# 有些问题用递归会造成很多重复的计算，可修改为备忘录
//# 动态规划的关键在于如何定义状态，以让状态转移方程好写
//#
//#如果状态转移方程中，新状态只和相邻的一个状态有关，可以不用整个dp数组，只需要一个变量储存相邻的那个状态就足够了，这样可以把空间复杂度降到O(1)
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
/*
  通常我们遍历子串或者子序列有三种遍历方式:
  1)以某个节点为开头的所有子序列:如[a][a,b],[a,b,c]...再从以b为开头的子序列开始遍历[b][b,c]..
  2)根据子序列的长度为标杆,如先遍历出子序列长度为1的子序列,在遍历出长度为2的等等**
  3)(Kadane算法)以子序列的结束节点为基准,先遍历出以某个节点为结束的所有子序列,因为每个节点都可能会是子序列的结束节点,因此要遍历下整个序列,如:以b为结束点的所有子序列:[a,b][b]以c为结束点的所有子序列:[a,b,c][b,c][c]

  第一种遍历方式通常用于暴力解法,第二种遍历方式LC5.最长回文子串中的解法就用到了
  第三种遍历方式因为可以产生递推关系,采用动态规划时,经常通过此种遍历方式,如背包问题,最大公共子串,这里的动态规划解法也是以先遍历出以某个节点为结束节点的所有子序列的思路
*/

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 动态规划 - 入门题
//$$经典的问题有：斐波拉契数、爬楼梯、买卖股票最佳时机、打家劫舍、粉刷房子、
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC509. 斐波那契数
namespace LC509 {
int fib(int N) {
  int d[31];
  d[0] = 0;
  d[1] = 1;
  for (int i = 2; i <= N; i++) d[i] = d[i - 1] + d[i - 2];
  return d[N];
}
}  // namespace LC509

// LC1137. 第 N 个泰波那契数
namespace LC1137 {
int tribonacci(int n) {
  int l0 = 0;
  int l1 = 1;
  int l2 = 1;
  int l3 = 0;

  if (n == 0) {
    return l0;
  } else if (n == 1) {
    return l1;
  } else if (n == 2) {
    return l2;
  } else {
    for (int i = 3; i <= n; ++i) {
      l3 = l0 + l1 + l2;
      l0 = l1;
      l1 = l2;
      l2 = l3;
    }
  }

  return l3;
}
}  // namespace LC1137

// LC70. 爬楼梯
namespace LC70 {
int climbStairs(int n) {
  vector<long long> ret(n + 1, 1);
  for (int i = 2; i < n + 1; i++) {
    ret[i] = ret[i - 1] + ret[i - 2];
  }
  return ret[n];
}
}  // namespace LC70

// LC746. 使用最小花费爬楼梯
namespace LC746 {
int minCostClimbingStairs(vector<int>& cost) {
  int n = cost.size();
  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 0;
  for (int i = 2; i <= n; i++) {
    dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
  }
  return dp[n];
}
}  // namespace LC746

// LC53. 最大子序和
namespace LC53 {
// 思路2：同思路1本质是一样的,只不过省去了存dp的内存
int maxSubArray(vector<int>& nums) {
  int res = INT32_MIN, sum = 0;
  for (auto num : nums) {
    if (sum < 0) sum = 0;
    sum += num;
    res = max(res, sum);
  }
  return res;
}
// 思路：dp[i]表示以nums[i]结束的最大和，
// 则状态转移方程：dp[i] = max(dp[i-1]+nums[i],nums[i])
// int maxSubArray(vector<int>& nums) {
//   vector<int> dp(nums.size());
//   dp[0] = nums[0];
//   int res = dp[0];
//   for (int i = 1; i < nums.size(); i++) {
//     dp[i] = max(dp[i - 1] + nums[i], nums[i]);
//     res = max(res, dp[i]);
//   }
//   return res;
// }
}  // namespace LC53

//^ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ^//
//^ 六道股票题
//^ 通解框架：
//^https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/solution/yi-ge-tong-yong-fang-fa-tuan-mie-6-dao-gu-piao-wen
//^ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ^//
// LC121. 买卖股票的最佳时机
namespace LC121 {
// 思路：状态转移框架
//<改进:如果状态转移方程中，新状态只和相邻的一个状态有关，可以不用整个dp数组，只需要一个变量储存相邻的那个状态就足够了，这样可以把空间复杂度降到O(1)
int maxProfit(vector<int>& prices) {
  int n = prices.size();
  // dp0[i],dp1[i]分别表示第i天一开始手上无股票、有股票的最大收益
  int dp0 = 0, dp1 = INT32_MIN;
  for (auto price : prices) {
    dp0 = max(dp0, dp1 + price);
    dp1 = max(dp1, -price);
  }
  return dp0;
}
// 思路：状态转移框架
// int maxProfit(vector<int>& prices) {
//   int n = prices.size();
//   // dp0[i],dp1[i]分别表示第i天手上无股票、有股票的最大收益
//   vector<int> dp0(n), dp1(n);
//   for (int i = 0; i < n; i++) {
//     if (i == 0) {
//       dp0[i] = 0;
//       dp1[i] = -prices[i];
//       continue;
//     }
//     dp0[i] = max(dp0[i - 1], dp1[i - 1] + prices[i]);
//     dp1[i] = max(dp1[i - 1], -prices[i]);
//   }
//   return dp0[n - 1];
// }
// 改进
// int maxProfit(vector<int>& prices) {
//   int n = prices.size(), pre_profit = 0, max_profit = 0;
//   for (int i = 1; i < n; i++) {
//     pre_profit = max(0, pre_profit + prices[i] - prices[i - 1]);
//     max_profit = max(max_profit, pre_profit);
//   }
//   return max_profit;
// }
}  // namespace LC121

// LC122. 买卖股票的最佳时机 II
namespace LC122 {
// 思路2：状态转移框架
int maxProfit(vector<int>& prices) {
  int n = prices.size();
  // dp0[i],dp1[i]分别表示第i天一开始手上无股票、有股票的最大收益
  int dp0 = 0, dp1 = INT32_MIN;
  for (auto price : prices) {
    int tmp = dp0;
    dp0 = max(dp0, dp1 + price);
    dp1 = max(dp1, tmp - price);
  }
  return dp0;
}
// 思路：贪心算法
// int maxProfit(vector<int>& prices) {
//   int n = prices.size(), res = 0;
//   for (int i = 0, j = 0; j < n; j++) {
//     i = j;
//     while (j + 1 < n && prices[j + 1] > prices[j]) j++;
//     res += prices[j] - prices[i];
//   }
//   return res;
// }
}  // namespace LC122

// LC123. 买卖股票的最佳时机 III
namespace LC123 {
// 思路：状态转移框架
int maxProfit(vector<int>& prices) {
  // dp10 dp20分别表示共交易1/2次，手头无股票时的最大收益
  // dp11 dp21分别表示共交易1/2次，手头有股票时的最大收益
  int dp10 = 0, dp20 = 0, dp11 = INT32_MIN, dp21 = INT32_MIN;
  for (auto price : prices) {
    dp20 = max(dp20, dp21 + price);
    dp21 = max(dp21, dp10 - price);
    dp10 = max(dp10, dp11 + price);
    dp11 = max(dp11, -price);
  }
  return dp20;
}
}  // namespace LC123

// LC188. 买卖股票的最佳时机 IV
namespace LC188 {}  // namespace LC188

// LC714. 买卖股票的最佳时机含手续费
namespace LC714 {
// 思路：状态转移框架
int maxProfit(vector<int>& prices, int fee) {
  int n = prices.size();
  // dp0[i],dp1[i]分别表示第i天一开始手上无股票、有股票的最大收益
  int dp0 = 0, dp1 = INT32_MIN;
  for (auto price : prices) {
    int tmp = dp0;
    dp0 = max(dp0, dp1 + price);
    dp1 = max(dp1, tmp - price - fee);
  }
  return dp0;
}
}  // namespace LC714

// LC309. 最佳买卖股票时机含冷冻期
namespace LC309 {
// 思路：状态转移框架
int maxProfit(vector<int>& prices) {
  int n = prices.size();
  // dp0[i],dp1[i]分别表示第i天一开始手上无股票、有股票的最大收益
  int dp0 = 0, dp1 = INT32_MIN, pre_dp0 = 0;
  for (int i = 0; i < n; i++) {
    int tmp = dp0;
    dp0 = max(dp0, dp1 + prices[i]);
    dp1 = max(dp1, pre_dp0 - prices[i]);
    pre_dp0 = tmp;
  }
  return dp0;
}
}  // namespace LC309

//^ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ^//
//^ 打家劫舍问题
//^ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ^//
// LC198. 打家劫舍
namespace LC198 {
int rob(vector<int>& nums) {
  int preNo = 0, preYes = 0;  //分别为不打劫当前、打劫当前可获得最多的钱
  for (auto num : nums) {
    int temp = preNo;
    preNo = max(preNo, preYes);
    preYes = num + temp;
  }
  return max(preYes, preNo);
}
// 思路2
// int rob(int num[], int n) {
//   int a = 0, b = 0;
//   for (int i = 0; i < n; i++) {
//     if (i % 2 == 0) {
//       a = max(a + num[i], b);
//     } else {
//       b = max(a, b + num[i]);
//     }
//   }
//   return max(a, b);
// }
// 思路1
// int rob(vector<int>& nums) {
//   int n = nums.size();
//   if (n == 0) return 0;
//   if (n == 1) return nums[0];
//   if (n == 2) return max(nums[0], nums[1]);
//   vector<int> dp(n, 0);
//   dp[0] = nums[0];
//   dp[1] = nums[1];
//   dp[2] = nums[0] + nums[2];
//   for (int i = 3; i < n; i++) {
//     dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i];
//   }
//   return max(dp[n - 1], dp[n - 2]);
// }
}  // namespace LC198

// LC213. 打家劫舍 II
namespace LC213 {}  // namespace LC213

// LC337. 打家劫舍 III
namespace LC337 {}  // namespace LC337

// LC276. 栅栏涂色
namespace LC276 {
int numWays(int n, int k) {
  if (n == 0) return 0;
  if (n == 1) return k;
  if (n == 2) return k * k;
  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = k;
  dp[2] = k * k;
  for (int i = 3; i <= n; i++) {
    dp[i] = (dp[i - 1] + dp[i - 2]) * (k - 1);
  }
  return dp[n];
}
}  // namespace LC276

// LC256. 粉刷房子
namespace LC256 {
int minCost(vector<vector<int>>& costs) {
  int n = costs.size();
  if (n == 0) return 0;
  for (int i = 1; i < n; i++) {
    costs[i][0] += min(costs[i - 1][1], costs[i - 1][2]);
    costs[i][1] += min(costs[i - 1][0], costs[i - 1][2]);
    costs[i][2] += min(costs[i - 1][0], costs[i - 1][1]);
  }
  return min(min(costs[n - 1][0], costs[n - 1][1]), costs[n - 1][2]);
}
}  // namespace LC256

// LC265. 粉刷房子 II
namespace LC265 {}  // namespace LC265

// LC303. 区域和检索 - 数组不可变
namespace LC303 {
// 思路2：
class NumArray {
 public:
  vector<int> sumArray;

  NumArray(vector<int>& nums) {
    sumArray.push_back(0);
    int last = 0;
    for (int i : nums) sumArray.push_back(last += i);
  }

  int sumRange(int i, int j) { return sumArray[j + 1] - sumArray[i]; }
};
// 思路：暴力方法
// class NumArray {
//  public:
//   vector<vector<int>> dp;
//   NumArray(vector<int>& nums) {
//     int n = nums.size();
//     dp = vector<vector<int>>(n, vector<int>(n, 0));
//     for (int i = 0; i < n; i++) {
//       for (int j = i; j < n; j++) {
//         if (j == 0)
//           dp[i][j] = nums[0];
//         else {
//           dp[i][j] = dp[i][j - 1] + nums[j];
//         }
//       }
//     }
//   }

//   int sumRange(int i, int j) { return dp[i][j]; }
// };
}  // namespace LC303

// LC304. 二维区域和检索 - 矩阵不可变
namespace LC304 {
class NumMatrix {
 private:
  int row, col;
  vector<vector<int>> sums;

 public:
  NumMatrix(vector<vector<int>>& matrix) {
    row = matrix.size();
    col = row > 0 ? matrix[0].size() : 0;
    sums = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));
    for (int i = 1; i <= row; i++) {
      for (int j = 1; j <= col; j++) {
        sums[i][j] = matrix[i - 1][j - 1] + sums[i - 1][j] + sums[i][j - 1] -
                     sums[i - 1][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1] -
           sums[row1][col2 + 1] + sums[row1][col1];
  }
};
}  // namespace LC304

// LC307. 区域和检索 - 数组可修改
namespace LC307 {}  // namespace LC307

// LC308. 二维区域和检索 - 可变
namespace LC308 {}  // namespace LC308

// LC1025. 除数博弈
namespace LC1025 {
bool divisorGame(int N) {
  if (N == 1) return false;
  vector<bool> dp(N + 1, false);
  dp[2] = true;
  for (int i = 3; i <= N; i++)
    for (int j = 1; j < i; j++)
      if (i % j == 0 && !dp[i - j]) dp[i] = true;
  return dp[N];
}
}  // namespace LC1025

// LC96. 不同的二叉搜索树
namespace LC96 {
int numTrees(int n) {
  if (n == 0) return 1;
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++) dp[i] += dp[j - 1] * dp[i - j];
  return dp[n];
}
}  // namespace LC96

// LC95. 不同的二叉搜索树 II
namespace LC95 {
vector<TreeNode*> generateTrees(int start, int end) {
  if (start > end) return {NULL};
  if (start == end) return {new TreeNode(start)};
  vector<TreeNode*> res;
  for (int i = start; i <= end; i++) {
    auto left = generateTrees(start, i - 1);
    auto right = generateTrees(i + 1, end);
    for (auto lnode : left)
      for (auto rnode : right) {
        auto root = new TreeNode(i);
        root->left = lnode;
        root->right = rnode;
        res.push_back(root);
      }
  }
  return res;
}
vector<TreeNode*> generateTrees(int n) {
  if (n == 0) return {};
  return generateTrees(1, n);
}
}  // namespace LC95

// LC5. 最长回文子串
namespace LC5 {}  // namespace LC5

// LC85. 最大矩形
namespace LC85 {}  // namespace LC85

// LC10. 正则表达式匹配
namespace LC10 {}  // namespace LC10

// LC72. 编辑距离
namespace LC72 {}  // namespace LC72

// LC312. 戳气球
namespace LC312 {}  // namespace LC312

// LC818. 赛车
namespace LC818 {}  // namespace LC818

// LC64. 最小路径和
namespace LC64 {}  // namespace LC64

// LC120. 三角形最小路径和
namespace LC120 {}  // namespace LC120

// LC351. 安卓系统手势解锁
namespace LC351 {}  // namespace LC351

// LC698. 划分为k个相等的子集
namespace LC698 {}  // namespace LC698

// LC363. 矩形区域不超过 K 的最大数值和
namespace LC363 {}  // namespace LC363

// LC718. 最长重复子数组
namespace LC718 {}  // namespace LC718

// LC466. 统计重复个数
namespace LC466 {}  // namespace LC466

// LC32. 最长有效括号
namespace LC32 {}  // namespace LC32

// LC338. 比特位计数
namespace LC338 {}  // namespace LC338

// LC629. K个逆序对数组
namespace LC629 {}  // namespace LC629

// LC847. 访问所有节点的最短路径
namespace LC847 {}  // namespace LC847

// LC647. 回文子串
namespace LC647 {}  // namespace LC647

// LC300. 最长上升子序列
namespace LC300 {}  // namespace LC300

// LC413. 等差数列划分
namespace LC413 {}  // namespace LC413

// LC673. 最长递增子序列的个数
namespace LC673 {}  // namespace LC673

// LC600. 不含连续1的非负整数
namespace LC600 {}  // namespace LC600

// LC264. 丑数 II
namespace LC264 {}  // namespace LC264

// LC221. 最大正方形
namespace LC221 {}  // namespace LC221

// LC638. 大礼包
namespace LC638 {}  // namespace LC638

// LC375. 猜数字大小 II
namespace LC375 {}  // namespace LC375

// LC689. 三个无重叠子数组的最大和
namespace LC689 {}  // namespace LC689

// LC664. 奇怪的打印机
namespace LC664 {}  // namespace LC664

// LC174. 地下城游戏
namespace LC174 {}  // namespace LC174

// LC357. 计算各个位数不同的数字个数
namespace LC357 {}  // namespace LC357

// LC516. 最长回文子序列
namespace LC516 {}  // namespace LC516

// LC132. 分割回文串 II
namespace LC132 {}  // namespace LC132

// LC321. 拼接最大数
namespace LC321 {}  // namespace LC321

// LC62. 不同路径
namespace LC62 {}  // namespace LC62

// LC97. 交错字符串
namespace LC97 {}  // namespace LC97

// LC920. 播放列表的数量
namespace LC920 {}  // namespace LC920

// LC368. 最大整除子集
namespace LC368 {}  // namespace LC368

// LC343. 整数拆分
namespace LC343 {}  // namespace LC343

// LC712. 两个字符串的最小ASCII删除和
namespace LC712 {}  // namespace LC712

// LC279. 完全平方数
namespace LC279 {}  // namespace LC279

// LC471. 编码最短长度的字符串
namespace LC471 {}  // namespace LC471

// LC650. 只有两个键的键盘
namespace LC650 {}  // namespace LC650

// LC691. 贴纸拼词
namespace LC691 {}  // namespace LC691

// LC801. 使序列递增的最小交换次数
namespace LC801 {}  // namespace LC801

// LC546. 移除盒子
namespace LC546 {}  // namespace LC546

// LC741. 摘樱桃
namespace LC741 {}  // namespace LC741

// LC552. 学生出勤记录 II
namespace LC552 {}  // namespace LC552

// LC877. 石子游戏
namespace LC877 {}  // namespace LC877

// LC813. 最大平均值和的分组
namespace LC813 {}  // namespace LC813

// LC87. 扰乱字符串
namespace LC87 {}  // namespace LC87

// LC410. 分割数组的最大值
namespace LC410 {}  // namespace LC410

// LC688. “马”在棋盘上的概率
namespace LC688 {}  // namespace LC688

// LC322. 零钱兑换
namespace LC322 {}  // namespace LC322

// LC464. 我能赢吗
namespace LC464 {}  // namespace LC464

// LC403. 青蛙过河
namespace LC403 {}  // namespace LC403

// LC486. 预测赢家
namespace LC486 {}  // namespace LC486

// LC152. 乘积最大子序列
namespace LC152 {}  // namespace LC152

// LC879. 盈利计划
namespace LC879 {}  // namespace LC879

// LC1012. 至少有 1 位重复的数字
namespace LC1012 {}  // namespace LC1012

// LC871. 最低加油次数
namespace LC871 {}  // namespace LC871

// LC808. 分汤
namespace LC808 {}  // namespace LC808

// LC361. 轰炸敌人
namespace LC361 {}  // namespace LC361

// LC91. 解码方法
namespace LC91 {}  // namespace LC91

// LC139. 单词拆分
namespace LC139 {}  // namespace LC139

// LC730. 统计不同回文子字符串
namespace LC730 {}  // namespace LC730

// LC115. 不同的子序列
namespace LC115 {}  // namespace LC115

// LC1055. 形成字符串的最短路径
namespace LC1055 {}  // namespace LC1055

// LC943. 最短超级串
namespace LC943 {}  // namespace LC943

// LC474. 一和零
namespace LC474 {}  // namespace LC474

// LC392. 判断子序列
namespace LC392 {}  // namespace LC392

// LC837. 新21点
namespace LC837 {}  // namespace LC837

// LC740. 删除与获得点数
namespace LC740 {}  // namespace LC740

// LC646. 最长数对链
namespace LC646 {}  // namespace LC646

// LC903. DI 序列的有效排列
namespace LC903 {}  // namespace LC903

// LC354. 俄罗斯套娃信封问题
namespace LC354 {}  // namespace LC354

// LC44. 通配符匹配
namespace LC44 {}  // namespace LC44

// LC727. 最小窗口子序列
namespace LC727 {}  // namespace LC727

// LC639. 解码方法 2
namespace LC639 {}  // namespace LC639

// LC651. 4键键盘
namespace LC651 {}  // namespace LC651

// LC377. 组合总和 Ⅳ
namespace LC377 {}  // namespace LC377

// LC467. 环绕字符串中唯一的子字符串
namespace LC467 {}  // namespace LC467

// LC63. 不同路径 II
namespace LC63 {}  // namespace LC63

// LC514. 自由之路
namespace LC514 {}  // namespace LC514

// LC887. 鸡蛋掉落
namespace LC887 {}  // namespace LC887

// LC494. 目标和
namespace LC494 {}  // namespace LC494

// LC1049. 最后一块石头的重量 II
namespace LC1049 {}  // namespace LC1049

// LC956. 最高的广告牌
namespace LC956 {}  // namespace LC956

// LC960. 删列造序 III
namespace LC960 {}  // namespace LC960

// LC416. 分割等和子集
namespace LC416 {}  // namespace LC416

// LC576. 出界的路径数
namespace LC576 {}  // namespace LC576

// LC931. 下降路径最小和
namespace LC931 {}  // namespace LC931

// LC523. 连续的子数组和
namespace LC523 {}  // namespace LC523

// LC873. 最长的斐波那契子序列的长度
namespace LC873 {}  // namespace LC873

// LC376. 摆动序列
namespace LC376 {}  // namespace LC376

// LC975. 奇偶跳
namespace LC975 {}  // namespace LC975

// LC517. 超级洗衣机
namespace LC517 {}  // namespace LC517

// LC838. 推多米诺
namespace LC838 {}  // namespace LC838

// LC140. 单词拆分 II
namespace LC140 {}  // namespace LC140

// LC935. 骑士拨号器
namespace LC935 {}  // namespace LC935

// LC983. 最低票价
namespace LC983 {}  // namespace LC983

// LC764. 最大加号标志
namespace LC764 {}  // namespace LC764

// LC787. K 站中转内最便宜的航班
namespace LC787 {}  // namespace LC787

// LC964. 表示数字的最少运算符
namespace LC964 {}  // namespace LC964

// LC940. 不同的子序列 II
namespace LC940 {}  // namespace LC940

// LC472. 连接词
namespace LC472 {}  // namespace LC472

// LC790. 多米诺和托米诺平铺
namespace LC790 {}  // namespace LC790

// LC418. 屏幕可显示句子的数量
namespace LC418 {}  // namespace LC418

// LC898. 子数组按位或操作
namespace LC898 {}  // namespace LC898

// LC1027. 最长等差数列
namespace LC1027 {}  // namespace LC1027

// LC446. 等差数列划分 II - 子序列
namespace LC446 {}  // namespace LC446

// LC978. 最长湍流子数组
namespace LC978 {}  // namespace LC978

// LC902. 最大为 N 的数字组合
namespace LC902 {}  // namespace LC902

// LC1000. 合并石头的最低成本
namespace LC1000 {}  // namespace LC1000

// LC1105. 填充书架
namespace LC1105 {}  // namespace LC1105

// LC1039. 多边形三角剖分的最低得分
namespace LC1039 {}  // namespace LC1039

// LC1074. 元素和为目标值的子矩阵数量
namespace LC1074 {}  // namespace LC1074

// LC968. 监控二叉树
namespace LC968 {}  // namespace LC968

// LC982. 按位与为零的三元组
namespace LC982 {}  // namespace LC982

// LC1024. 视频拼接
namespace LC1024 {}  // namespace LC1024

// LC967. 连续差相同的数字
namespace LC967 {}  // namespace LC967

// LC1147. 段式回文
namespace LC1147 {}  // namespace LC1147

// LC1067. 范围内的数字计数
namespace LC1067 {}  // namespace LC1067

// LC1048. 最长字符串链
namespace LC1048 {}  // namespace LC1048

// LC1125. 最小的必要团队
namespace LC1125 {}  // namespace LC1125

// LC568. 最大休假天数
namespace LC568 {}  // namespace LC568

// LC656. 金币路径
namespace LC656 {}  // namespace LC656

// LC750. 角矩形的数量
namespace LC750 {}  // namespace LC750

// LC1058. 最小化舍入误差以满足目标
namespace LC1058 {}  // namespace LC1058

// LC1066. 校园自行车分配 II
namespace LC1066 {}  // namespace LC1066

// LC1136. 平行课程
namespace LC1136 {}  // namespace LC1136

// LC1092. 最短公共超序列
namespace LC1092 {}  // namespace LC1092
