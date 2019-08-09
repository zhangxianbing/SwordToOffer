/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 11:29:43
 * @LastEditTime: 2019-08-09 16:20:38
 * @LastEditors: zhangxianbing
 */
#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 二叉树
//! 二叉树天然具有递归的结构，因此涉及很多问题都和遍历、递归有关，
//! 递归的关键是如何抽象出左右子树的解和母树的解之间的关系,这有点类似动态规划的思想
//! 注意有的递归问题可以在自底向上时提前截断，防止重复不必要的遍历计算
//! 二叉树一般涉及的问题类型有：
//!     常规遍历、变种遍历以及遍历衍生而来的问题（其实基本所有树的问题都涉及到遍历）
//!     树的路径、距离相关问题
//!     遍历序列相关问题
//!     深度优先遍历（前中后序遍历）和广度优先遍历（层序遍历）
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

//! 二叉树的其他递归相关问题，关键是分解问题

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

// TODO 572. 另一个树的子树
namespace LC572 {
bool isSameTree(TreeNode* p, TreeNode* q) {
  if (!p && !q) return true;
  if (bool(p) != bool(q)) return false;
  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}
bool isSubtree(TreeNode* s, TreeNode* t) {
  if (!s) return false;
  return isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
}
}  // namespace LC572

// TODO 250. 统计同值子树
namespace LC250 {
// 这里实际是前序遍历了一遍树来判断是否root树为同值树
// 也可以用中序遍历，后序遍历，只要是深度优先遍历就行
int helper(TreeNode* root, int val) {
  if (!root) return 0;
  if (root->val != val) return -1;
  int l = helper(root->left, val);
  if (l == -1) return -1;
  int r = helper(root->right, val);
  if (r == -1) return -1;
  return 1;
}
int countUnivalSubtrees(TreeNode* root) {
  if (!root) return 0;
  return countUnivalSubtrees(root->left) + countUnivalSubtrees(root->right) +
         (helper(root, root->val) > 0);
}
}  // namespace LC250

// TODO 508. 出现次数最多的子树元素和
namespace LC508 {}  // namespace LC508

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
int maxDepth1(TreeNode* root) {
  if (!root) return 0;
  return max(maxDepth1(root->left), maxDepth1(root->right)) + 1;
}
bool isBalanced1(TreeNode* root) {
  if (!root) return true;
  if (abs(maxDepth1(root->left) - maxDepth1(root->right)) > 1) return false;
  return isBalanced1(root->left) && isBalanced1(root->right);
}
//* 思路2： 自底向上(提前截断)
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  int left = maxDepth(root->left), right = maxDepth(root->right);
  if (left == -1 || right == -1) return -1;
  int res = abs(left - right);
  return res > 1 ? -1 : (max(left, right) + 1);
}
bool isBalanced(TreeNode* root) { return maxDepth(root) != -1; }
}  // namespace LC110

// TODO 222. 完全二叉树的节点个数
namespace LC222 {
int countNodes(TreeNode* root) {
  if (!root) return 0;
  return countNodes(root->left) + countNodes(root->right) + 1;
}
}  // namespace LC222

namespace LC404 {}  // namespace LC404

namespace LC257 {}  // namespace LC257

namespace LC113 {}  // namespace LC113

namespace LC129 {}  // namespace LC129

// TODO 96. 不同的二叉搜索树 （见 动态规划 部分）
namespace LC96 {}  // namespace LC96

// TODO 95. 不同的二叉搜索树 II （见 动态规划 部分）
namespace LC95 {}  // namespace LC95

//! 遍历序列相关问题

// TODO 1028. 从先序遍历还原二叉树
namespace LC1028 {}  // namespace LC1028

//! 与距离和路径相关的二叉树问题

// TODO 112. 路径总和
namespace LC112 {
bool hasPathSum(TreeNode* root, int sum) {
  if (!root) return false;
  if (sum == root->val && !root->left && !root->right) return true;
  return hasPathSum(root->left, sum - root->val) ||
         hasPathSum(root->right, sum - root->val);
}
}  // namespace LC112

// TODO 路径总和 II
namespace LC113 {
void pathSum(vector<vector<int>>& res, vector<int> path, TreeNode* root,
             int sum) {
  if (!root) return;
  path.push_back(root->val);
  if (sum == root->val && !root->left && !root->right) {
    res.push_back(path);
  }
  pathSum(res, path, root->left, sum - root->val);
  pathSum(res, path, root->right, sum - root->val);
}
vector<vector<int>> pathSum(TreeNode* root, int sum) {
  vector<vector<int>> res;
  pathSum(res, {}, root, sum);
  return res;
}
}  // namespace LC113

// TODO 437. 路径总和 III
namespace LC437 {
int rootSum(TreeNode* root, int sum) {
  if (!root) return 0;
  return (root->val == sum) + rootSum(root->left, sum - root->val) +
         rootSum(root->right, sum - root->val);
}
int pathSum(TreeNode* root, int sum) {
  if (!root) return 0;
  return rootSum(root, sum) + pathSum(root->left, sum) +
         pathSum(root->right, sum);
}
}  // namespace LC437

// TODO 666. 路径和 IV
namespace LC666 {
int pathSum(vector<int>& nums) {
  int res = 0;
  unordered_map<int, int> M;
  for (int i = int(nums.size()) - 1; i >= 0; i--) {
    int d = nums[i] / 100, p = (nums[i] % 100) / 10, v = nums[i] % 10;
    M[d * 10 + p] = max(M[d * 10 + p], 1);
    res += M[d * 10 + p] * v;
    // 如果一个节点会经过 n 次, 那么这 n 次也一定经过其父节点,
    // 因此将当前节点的次数加入其父节点中
    M[(d - 1) * 10 + (p - 1) / 2 + 1] += M[d * 10 + p];
  }
  return res;
}
}  // namespace LC666

// TODO 687. 最长同值路径
namespace LC687 {
int helper(TreeNode* root, int val) {
  if (!root || root->val != val) return 0;
  return 1 + max(helper(root->left, val), helper(root->right, val));
}
int longestUnivaluePath(TreeNode* root) {
  if (!root) return 0;
  int sub =
      max(longestUnivaluePath(root->left), longestUnivaluePath(root->right));
  return max(sub,
             helper(root->left, root->val) + helper(root->right, root->val));
}
}  // namespace LC687

// TODO 124. 二叉树中的最大路径和
namespace LC124 {}  // namespace LC124

// TODO 863. 二叉树中所有距离为 K 的结点
namespace LC863 {}  // namespace LC863

//! 二分搜索树
namespace LC235 {}  // namespace LC235

namespace LC98 {}  // namespace LC98

namespace LC450 {}  // namespace LC450

namespace LC108 {}  // namespace LC108

namespace LC230 {}  // namespace LC230

namespace LC236 {}  // namespace LC236