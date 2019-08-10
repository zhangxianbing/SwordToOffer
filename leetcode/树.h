/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 11:29:43
 * @LastEditTime: 2019-08-10 08:28:37
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
//!     路径相关问题：路径、距离以及衍生的路径和、路径数字、路径字符等等
//!     遍历序列相关问题
//!     深度优先遍历（前中后序遍历）和广度优先遍历（层序遍历）
//!     动态规划问题(本质也是遍历问题,详见动态规划部分)
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

// TODO 145. 二叉树的后序遍历
namespace LC145 {}  // namespace LC145

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

// TODO 590. N叉树的后序遍历
namespace LC590 {}  // namespace LC590

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

// TODO 404. 左叶子之和
namespace LC404 {
//* 思路：自底向上的dfs,考虑后序遍历
int sumOfLeftLeaves(TreeNode* root) {
  if (!root) return 0;
  int res = 0;
  if (root->left && !root->left->left && !root->left->right)
    res = root->left->val;
  return res + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}
}  // namespace LC404

//! 与路径相关问题：路径和、路径数字、路径字符、路径序列等等
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
//* 思路：自顶向下的dfs，考虑前序遍历
void dfs(vector<vector<int>>& res, vector<int> path, TreeNode* root, int sum) {
  if (!root) return;
  path.push_back(root->val);
  if (sum == root->val && !root->left && !root->right) {
    res.push_back(path);
  }
  dfs(res, path, root->left, sum - root->val);
  dfs(res, path, root->right, sum - root->val);
}
vector<vector<int>> pathSum(TreeNode* root, int sum) {
  vector<vector<int>> res;
  dfs(res, {}, root, sum);
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

// TODO 257. 二叉树的所有路径
namespace LC257 {
//* 思路：从根出发的dfs，考虑前序遍历
void dfs(vector<string>& res, string path, TreeNode* root) {
  if (!root) return;
  path += to_string(root->val);
  if (!root->left && !root->right) {
    res.push_back(path);
  } else {
    path += "->";
    dfs(res, path, root->left);
    dfs(res, path, root->right);
  }
}
vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> res;
  dfs(res, {}, root);
  return res;
}
}  // namespace LC257

// TODO 129. 求根到叶子节点数字之和
namespace LC129 {
//* 思路：自顶向下的dfs，考虑前序遍历
void dfs(vector<int>& nums, int tmp, TreeNode* root) {
  if (!root) return;
  tmp = tmp * 10 + root->val;
  if (!root->left && !root->right) nums.push_back(tmp);
  dfs(nums, tmp, root->left);
  dfs(nums, tmp, root->right);
}
int sumNumbers(TreeNode* root) {
  vector<int> nums;
  dfs(nums, 0, root);
  return accumulate(nums.begin(), nums.end(), 0);
}
}  // namespace LC129

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
namespace LC124 {
//* 思路：此题其实就两个点：
//* 1.分解问题：求从root出发的解+左右子树的完整解
//* 2.用dfs求从root出发的解,最好自底向上，先求从底层节点出发的最大路径和，再往上推算，故采用后序遍历
int dfs(int& res, TreeNode* root) {
  if (!root) return 0;
  int left_max = dfs(res, root->left);
  int right_max = dfs(res, root->right);
  int mid_max = (left_max > 0 ? left_max : 0) +
                (right_max > 0 ? right_max : 0) + root->val;
  res = max(res, mid_max);
  return max(max(left_max, right_max) + root->val, root->val);
}
int maxPathSum(TreeNode* root) {
  int res = INT32_MIN;
  dfs(res, root);
  return res;
}
}  // namespace LC124

// TODO 988. 从叶结点开始的最小字符串
namespace LC988 {
//* 思路：需要从根开始dfs,考虑前序遍历；结果存入map中
void dfs(map<string, int>& M, string s, TreeNode* root) {
  if (!root) return;
  s += root->val + 'a';
  if (!root->left && !root->right) {
    reverse(s.begin(), s.end());
    M[s]++;
  }
  dfs(M, s, root->left);
  dfs(M, s, root->right);
}
string smallestFromLeaf(TreeNode* root) {
  map<string, int> M;
  dfs(M, {}, root);
  return M.begin()->first;
}
}  // namespace LC988

// TODO 783. 二叉搜索树结点最小距离
namespace LC783 {}  // namespace LC783

// TODO 298. 二叉树最长连续序列
namespace LC298 {}  // namespace LC298

// TODO 549. 二叉树中最长的连续序列
namespace LC549 {}  // namespace LC549

//! 子树问题
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
namespace LC508 {
//* 思路： 后序遍历求各子树的和,并存入一个map中
int dfs(unordered_map<int, int>& M, TreeNode* root) {
  if (!root) return 0;
  int left = dfs(M, root->left);
  int right = dfs(M, root->right);
  int sum = left + right + root->val;
  M[sum]++;
  return sum;
}
vector<int> findFrequentTreeSum(TreeNode* root) {
  if (!root) return {};
  vector<int> res;
  unordered_map<int, int> M;
  dfs(M, root);
  int maxTime = 0;
  for (auto item : M) maxTime = max(maxTime, item.second);
  for (auto item : M)
    if (item.second == maxTime) res.push_back(item.first);
  return res;
}
}  // namespace LC508

// TODO 333. 最大 BST 子树
namespace LC333 {}  // namespace LC333

// TODO 652. 寻找重复的子树
namespace LC652 {}  // namespace LC652

// TODO 1120. 子树的最大平均值
namespace LC1120 {}  // namespace LC1120

// TODO 865. 具有所有最深结点的最小子树
namespace LC865 {}  // namespace LC865

// TODO 663. 均匀树划分
namespace LC663 {}  // namespace LC663

//! 距离问题（本质还是路径问题）
// TODO 834. 树中距离之和
namespace LC834 {}  // namespace LC834

// TODO 783. 二叉搜索树结点最小距离
namespace LC783 {}  // namespace LC783

// TODO 863. 二叉树中所有距离为 K 的结点
namespace LC863 {}  // namespace LC863

// TODO 742. 二叉树最近的叶节点
namespace LC742 {}  // namespace LC742

// TODO 235. 二叉搜索树的最近公共祖先
namespace LC235 {}  // namespace LC235

// TODO 236. 二叉树的最近公共祖先
namespace LC236 {}  // namespace LC236

// TODO 1026. 节点与其祖先之间的最大差值
namespace LC1026 {}  // namespace LC1026

// TODO 1123. 最深叶节点的最近公共祖先
namespace LC1123 {}  // namespace LC1123

//! 遍历序列相关问题
// TODO 105. 从前序与中序遍历序列构造二叉树
namespace LC105 {}  // namespace LC105

// TODO 106. 从中序与后序遍历序列构造二叉树
namespace LC106 {}  // namespace LC106

// TODO 889. 根据前序和后序遍历构造二叉树
namespace LC889 {}  // namespace LC889

// TODO 1008. 先序遍历构造二叉树
namespace LC1008 {}  // namespace LC1008

// TODO 971. 翻转二叉树以匹配先序遍历
namespace LC971 {}  // namespace LC971

// TODO 255. 验证前序遍历序列二叉搜索树
namespace LC255 {}  // namespace LC255

// TODO 1028. 从先序遍历还原二叉树
namespace LC1028 {}  // namespace LC1028

//! 树的转换问题(将树结构转换为其他形式)
// TODO 449. 序列化和反序列化二叉搜索树
namespace LC449 {}  // namespace LC449

// TODO 428. 序列化和反序列化 N 叉树
namespace LC428 {}  // namespace LC428

// TODO 297. 二叉树的序列化与反序列化
namespace LC297 {}  // namespace LC297

// TODO 114. 二叉树展开为链表
namespace LC114 {}  // namespace LC114

// TODO 426. 将二叉搜索树转化为排序的双向链表
namespace LC426 {}  // namespace LC426

// TODO 536. 从字符串生成二叉树
namespace LC536 {}  // namespace LC536

// TODO 538. 把二叉搜索树转换为累加树
namespace LC538 {}  // namespace LC538

// TODO 655. 输出二叉树
namespace LC655 {}  // namespace LC655

// TODO 814. 二叉树剪枝
namespace LC814 {}  // namespace LC814

// TODO 108. 将有序数组转换为二叉搜索树
namespace LC108 {}  // namespace LC108

// TODO 431. 将 N 叉树编码为二叉树
namespace LC431 {}  // namespace LC431

//! 二分搜索树
// TODO 98. 验证二叉搜索树
namespace LC98 {}  // namespace LC98

//! 二叉树操作
// TODO 450. 删除二叉搜索树中的节点
namespace LC450 {}  // namespace LC450

// TODO 701. 二叉搜索树中的插入操作
namespace LC701 {}  // namespace LC701

// TODO 700. 二叉搜索树中的搜索
namespace LC700 {}  // namespace LC700

// TODO 669. 修剪二叉搜索树
namespace LC669 {}  // namespace LC669

// TODO 99. 恢复二叉搜索树
namespace LC99 {}  // namespace LC99

// TODO 776. 拆分二叉搜索树
namespace LC776 {}  // namespace LC776

// TODO 623. 在二叉树中增加一行
namespace LC623 {}  // namespace LC623

// TODO 156. 上下翻转二叉树
namespace LC156 {}  // namespace LC156

//! 中序
// TODO 230. 二叉搜索树中第K小的元素
namespace LC230 {
int kthSmallest(TreeNode* root, int k) {
  stack<TreeNode*> s;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      k--;
      if (k == 0) break;
      root = root->right;
    }
  }
  return root->val;
}
}  // namespace LC230

//! 层序
// TODO 637. 二叉树的层平均值
namespace LC637 {}  // namespace LC637

// TODO 515. 在每个树行中找最大值
namespace LC515 {}  // namespace LC515

//! 特殊性较强（言外之意：参考性不强的）放这↓
// TODO 337. 打家劫舍 III
namespace LC337 {}  // namespace LC337

//! 待分类
// TODO 270. 最接近的二叉搜索树值
namespace LC270 {}  // namespace LC270

// TODO 272. 最接近的二叉搜索树值 II
namespace LC272 {}  // namespace LC272

// TODO 501. 二叉搜索树中的众数
namespace L501 {}  // namespace L501

// TODO 662. 二叉树最大宽度
namespace LC662 {}  // namespace LC662

// TODO 559. N叉树的最大深度
namespace LC559 {}  // namespace LC559

// TODO 654. 最大二叉树
namespace LC654 {}  // namespace LC654

// TODO 998. 最大二叉树 II
namespace LC998 {}  // namespace LC998

// TODO 606. 根据二叉树创建字符串
namespace LC606 {}  // namespace LC606

// TODO 968. 监控二叉树
namespace LC968 {}  // namespace LC968

// TODO 938. 二叉搜索树的范围和
namespace LC938 {}  // namespace LC938

// TODO 530. 二叉搜索树的最小绝对差
namespace LC530 {}  // namespace LC530

// TODO 979. 在二叉树中分配硬币
namespace LC979 {}  // namespace LC979

// TODO 958. 二叉树的完全性检验
namespace LC958 {}  // namespace LC958

// TODO 894. 所有可能的满二叉树
namespace LC894 {}  // namespace LC894

// TODO 993. 二叉树的堂兄弟节点
namespace LC993 {}  // namespace LC993

// TODO 671. 二叉树中第二小的节点
namespace LC671 {}  // namespace LC671

// TODO 653. 两数之和 IV - 输入 BST
namespace LC653 {}  // namespace LC653

// TODO 116. 填充每个节点的下一个右侧节点指针
namespace LC116 {}  // namespace LC116

// TODO 117. 填充每个节点的下一个右侧节点指针 II
namespace LC117 {}  // namespace LC117

// TODO 173. 二叉搜索树迭代器
namespace LC173 {}  // namespace LC173

// TODO 872. 叶子相似的树
namespace LC872 {}  // namespace LC872

// TODO 513. 找树左下角的值
namespace LC513 {}  // namespace LC513

// TODO 617. 合并二叉树
namespace LC617 {}  // namespace LC617

// TODO 1145. 二叉树着色游戏
namespace LC1145 {}  // namespace LC1145

// TODO 1104. 二叉树寻路
namespace LC1104 {}  // namespace LC1104

// TODO 1022. 从根到叶的二进制数之和
namespace LC1022 {}  // namespace LC1022

// TODO 965. 单值二叉树
namespace LC965 {}  // namespace LC965

// TODO 951. 翻转等价二叉树
namespace LC951 {}  // namespace LC951

// TODO 919. 完全二叉树插入器
namespace LC919 {}  // namespace LC919

// TODO 897. 递增顺序查找树
namespace LC897 {}  // namespace LC897

// TODO 684. 冗余连接
namespace LC684 {}  // namespace LC684

// TODO 685. 冗余连接 II
namespace LC685 {}  // namespace LC685

// TODO 582. 杀死进程
namespace LC582 {}  // namespace LC582

// TODO 563. 二叉树的坡度
namespace LC563 {}  // namespace LC563

// TODO 545. 二叉树的边界
namespace LC545 {}  // namespace LC545

// TODO 285. 二叉搜索树中的顺序后继
namespace LC285 {}  // namespace LC285

// TODO 510. 二叉搜索树中的中序后继 II
namespace LC510 {}  // namespace LC510

// TODO 366. 寻找完全二叉树的叶子节点
namespace LC366 {}  // namespace LC366
