/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 12:45:53
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-11 15:13:32
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 图
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

// LC742. 二叉树最近的叶节点
namespace LC742 {
//* 思路：先前序遍历，建立无向图，找到k节点,再从k节点开始bfs
void dfs(unordered_map<TreeNode*, vector<TreeNode*>>& M, TreeNode*& start,
         int k, TreeNode* pre, TreeNode* root) {
  if (!root) return;
  if (root->val == k) start = root;
  if (pre) {
    M[root].push_back(pre);
    M[pre].push_back(root);
  }
  dfs(M, start, k, root, root->left);
  dfs(M, start, k, root, root->right);
}
int findClosestLeaf(TreeNode* root, int k) {
  unordered_map<TreeNode*, vector<TreeNode*>> M;
  TreeNode* start;
  dfs(M, start, k, NULL, root);
  unordered_set<TreeNode*> seen;
  queue<TreeNode*> Q;
  Q.push(start);
  seen.insert(start);
  while (!Q.empty()) {
    int n = Q.size();
    while (n-- > 0) {
      auto cur = Q.front();
      Q.pop();
      seen.insert(cur);
      if (!cur->left && !cur->right) return cur->val;
      for (auto node : M[cur]) {
        if (seen.find(node) == seen.end()) Q.push(node);
      }
    }
  }
  return 0;
}
}  // namespace LC742

// LC863. 二叉树中所有距离为 K 的结点
namespace LC863 {}  // namespace LC863