/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:37:21
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-09 11:42:35
 * @Description: file content
 */
#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 动态规划
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

// LC 96. 不同的二叉搜索树
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

// LC 95. 不同的二叉搜索树 II
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