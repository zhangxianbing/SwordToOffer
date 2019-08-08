#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 动态规划
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

// TODO 96. 不同的二叉搜索树
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

// TODO 95. 不同的二叉搜索树 II
namespace LC95 {}  // namespace LC95