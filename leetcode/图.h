/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 12:45:53
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-12 21:06:41
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

// LC765. 情侣牵手
namespace LC765 {}  // namespace LC765

// LC743. 网络延迟时间
namespace LC743 {}  // namespace LC743

// LC399. 除法求值
namespace LC399 {}  // namespace LC399

// LC133. 克隆图
namespace LC133 {}  // namespace LC133

// LC959. 由斜杠划分区域
namespace LC959 {}  // namespace LC959

// LC207. 课程表
namespace LC207 {}  // namespace LC207

// LC839. 相似字符串组
namespace LC839 {}  // namespace LC839

// LC854. 相似度为 K 的字符串
namespace LC854 {}  // namespace LC854

// LC310. 最小高度树
namespace LC310 {}  // namespace LC310

// LC332. 重新安排行程
namespace LC332 {}  // namespace LC332

// LC444. 序列重建
namespace LC444 {}  // namespace LC444

// LC1042. 不邻接植花
namespace LC1042 {}  // namespace LC1042

// LC996. 正方形数组的数目
namespace LC996 {}  // namespace LC996

// LC684. 冗余连接
namespace LC684 {}  // namespace LC684

// LC841. 钥匙和房间
namespace LC841 {}  // namespace LC841

// LC261. 以图判树
namespace LC261 {}  // namespace LC261

// LC685. 冗余连接 II
namespace LC685 {}  // namespace LC685

// LC210. 课程表 II
namespace LC210 {}  // namespace LC210

// LC1043. 分隔数组以得到最大和
namespace LC1043 {}  // namespace LC1043

// LC802. 找到最终的安全状态
namespace LC802 {}  // namespace LC802

// LC269. 火星词典
namespace LC269 {}  // namespace LC269

// LC997. 找到小镇的法官
namespace LC997 {}  // namespace LC997

// LC928. 尽量减少恶意软件的传播 II
namespace LC928 {}  // namespace LC928

// LC785. 判断二分图
namespace LC785 {}  // namespace LC785

// LC323. 无向图中连通分量的数目
namespace LC323 {}  // namespace LC323

// LC990. 等式方程的可满足性
namespace LC990 {}  // namespace LC990

// LC1102. 得分最高的路径
namespace LC1102 {}  // namespace LC1102

// LC1059. 从始点到终点的所有路径
namespace LC1059 {}  // namespace LC1059

// LC1135. 最低成本联通所有城市
namespace LC1135 {}  // namespace LC1135

// LC1136. 平行课程
namespace LC1136 {}  // namespace LC1136
