/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 11:29:43
 * @LastEditTime: 2019-08-09 11:42:48
 * @LastEditors: zhangxianbing
 */
#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 二叉树
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

//! 二叉树的各种遍历以及衍生遍历

// TODO 144. 二叉树的前序遍历
namespace LC144 {
vector<int> preorderTraversal(TreeNode* root) {
  vector<int> res;
  stack<TreeNode*> s;
  while (root || !s.empty()) {
    if (root) {
      res.push_back(root->val);
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      root = root->right;
    }
  }
  return res;
}
}  // namespace LC144

// TODO 94. 二叉树的中序遍历
namespace LC94 {
vector<int> inorderTraversal(TreeNode* root) {
  vector<int> res;
  stack<TreeNode*> s;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      res.push_back(root->val);
      root = root->right;
    }
  }
  return res;
}
}  // namespace LC94

// TODO 102. 二叉树的层次遍历
namespace LC102 {
vector<vector<int>> levelOrder(TreeNode* root) {
  if (!root) return {};
  vector<vector<int>> res;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size();
    if (n <= 0) break;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      q.pop();
      v.push_back(node->val);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
    res.push_back(v);
  }
  return res;
}
}  // namespace LC102

// TODO 107. 二叉树的层次遍历 II
namespace LC107 {
vector<vector<int>> levelOrderBottom(TreeNode* root) {
  if (!root) return {};
  vector<vector<int>> res;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size();
    if (n <= 0) break;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      q.pop();
      v.push_back(node->val);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
    res.push_back(v);
  }
  reverse(res.begin(), res.end());
  return res;
}
}  // namespace LC107

// TODO 103. 二叉树的锯齿形层次遍历
namespace LC103 {
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
  if (!root) return {};
  vector<vector<int>> res;
  queue<TreeNode*> q;
  q.push(root);
  int m = 0;
  while (!q.empty()) {
    int n = q.size();
    if (n <= 0) break;
    m++;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      q.pop();
      v.push_back(node->val);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
    if (m % 2 == 0) reverse(v.begin(), v.end());
    res.push_back(v);
  }
  return res;
}
}  // namespace LC103

// TODO 589. N叉树的前序遍历
namespace LC589 {
vector<int> preorder(Node* root) {
  if (!root) return {};
  vector<int> res;
  stack<Node*> s;
  s.push(root);
  while (!s.empty()) {
    auto node = s.top();
    s.pop();
    res.push_back(node->val);
    for (auto it = (node->children).rbegin(); it != (node->children).rend();
         ++it)
      s.push(*it);
  }
  return res;
}
}  // namespace LC589

// TODO 429. N叉树的层序遍历
namespace LC429 {
vector<vector<int>> levelOrder(Node* root) {
  if (!root) return {};
  vector<vector<int>> res;
  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size();

    vector<int> v;
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      q.pop();
      v.push_back(node->val);
      for (int j = 0; j < node->children.size(); j++) {
        q.push(node->children[j]);
      }
    }
    res.push_back(v);
  }
  return res;
}
}  // namespace LC429

// TODO 255. 验证前序遍历序列二叉搜索树
namespace LC255 {}  // namespace LC255

// TODO 314. 二叉树的垂直遍历
namespace LC314 {
//* 思路：此题本质还是一个层序遍历，每个节点附加一个偏移量
vector<vector<int>> verticalOrder(TreeNode* root) {
  if (!root) return {};
  vector<vector<int>> res;
  map<int, vector<int>> hash;
  queue<pair<TreeNode*, int>> Q;
  Q.push(make_pair(root, 1));
  while (!Q.empty()) {
    auto node = Q.front();
    Q.pop();
    hash[node.second].push_back(node.first->val);
    auto left = node.first->left, right = node.first->right;
    if (left) Q.push(make_pair(left, node.second - 1));
    if (right) Q.push(make_pair(right, node.second + 1));
  }
  for (auto val : hash) res.push_back(val.second);
  return res;
}
}  // namespace LC314

// TODO 987. 二叉树的垂序遍历
namespace LC987 {
vector<vector<int>> verticalTraversal(TreeNode* root) {
  if (!root) return {};
  vector<vector<int>> res;
  map<int, vector<pair<int, int>>> M;  // 先按x排序，再按y排序，再按val排序
  queue<pair<TreeNode*, pair<int, int>>> Q;  // 节点及坐标
  Q.push(make_pair(root, make_pair(0, 0)));
  while (!Q.empty()) {
    auto item = Q.front();
    Q.pop();
    auto node = item.first, left = node->left, right = node->right;
    auto x = item.second.first, y = item.second.second;
    M[x].push_back(make_pair(y, node->val));
    if (left) Q.push(make_pair(left, make_pair(x - 1, y + 1)));
    if (right) Q.push(make_pair(right, make_pair(x + 1, y + 1)));
  }
  for (auto& item : M) {
    auto& v = item.second;
    sort(v.begin(), v.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
           return a.first == b.first ? a.second < b.second : a.first < b.first;
         });
    vector<int> tmp;
    for (auto i : v) tmp.push_back(i.second);
    res.push_back(tmp);
  }
  return res;
}
}  // namespace LC987

// TODO 199. 二叉树的右视图
namespace LC199 {
//* 思路：本质是根-右-左的遍历顺序
vector<int> rightSideView(TreeNode* root) {
  if (!root) return {};
  vector<int> res;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size();
    if (n <= 0) break;
    res.push_back(q.front()->val);
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      q.pop();
      if (node->right) q.push(node->right);
      if (node->left) q.push(node->left);
    }
  }
  return res;
}
}  // namespace LC199

//! 二叉树的其他递归相关问题

// TODO 104. 二叉树的最大深度
namespace LC104 {
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
}  // namespace LC104

// TODO 111. 二叉树的最小深度
namespace LC111 {
int minDepth(TreeNode* root) {
  if (!root) return 0;
  if (!root->left) return minDepth(root->right) + 1;
  if (!root->right) return minDepth(root->left) + 1;
  return min(minDepth(root->left), minDepth(root->right)) + 1;
}
}  // namespace LC111

// TODO 226.反转二叉树
namespace LC226 {
TreeNode* invertTree(TreeNode* root) {
  if (!root) return NULL;
  root->left = invertTree(root->left);
  root->right = invertTree(root->right);
  swap(root->left, root->right);
  return root;
}
}  // namespace LC226

// TODO 100. 相同的树
namespace LC100 {
bool isSameTree(TreeNode* p, TreeNode* q) {
  if (!p && !q) return true;
  if (bool(p) != bool(q)) return false;
  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}
}  // namespace LC100

// TODO 101. 对称二叉树
namespace LC101 {
bool isMirror(TreeNode* p, TreeNode* q) {
  if (!p && !q) return true;
  if (bool(p) != bool(q)) return false;
  return p->val == q->val && isMirror(p->left, q->right) &&
         isMirror(p->right, q->left);
}
bool isSymmetric(TreeNode* root) {
  if (!root) return true;
  return isMirror(root->left, root->right);
}
}  // namespace LC101

// TODO 110. 平衡二叉树
namespace LC110 {
//* 思路1： 自顶向下
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
bool isBalanced(TreeNode* root) {
  if (!root) return true;
  if (abs(maxDepth(root->left) - maxDepth(root->right)) > 1) return false;
  return isBalanced(root->left) && isBalanced(root->right);
}
//* 思路2： 自底向上
bool isBalanced2(TreeNode* root) {}
}  // namespace LC110

namespace LC222 {}  // namespace LC222

namespace LC112 {}  // namespace LC112

namespace LC404 {}  // namespace LC404

namespace LC257 {}  // namespace LC257

namespace LC113 {}  // namespace LC113

namespace LC129 {}  // namespace LC129

namespace LC437 {}  // namespace LC437

// TODO 96. 不同的二叉搜索树 （见 动态规划 部分）
namespace LC96 {}  // namespace LC96

// TODO 95. 不同的二叉搜索树 II （见 动态规划 部分）
namespace LC95 {}  // namespace LC95

//! 二分搜索树
namespace LC235 {}  // namespace LC235

namespace LC98 {}  // namespace LC98

namespace LC450 {}  // namespace LC450

namespace LC108 {}  // namespace LC108

namespace LC230 {}  // namespace LC230

namespace LC236 {}  // namespace LC236

//! 与遍历序列相关的的二叉树问题

// TODO 1028. 从先序遍历还原二叉树
namespace LC1028 {
TreeNode* recoverFromPreorder(string S) {}
}  // namespace LC1028
