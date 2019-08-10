/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 11:29:43
 * @LastEditTime: 2019-08-10 17:41:34
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

//! 各种遍历的基础考察（基础的前序、中序、后序、层序，以及衍生的变种遍历）
// TODO 144. 二叉树的前序遍历
namespace LC144 {
//* 递归写法：
void dfs(vector<int>& res, TreeNode* root) {
  if (!root) return;
  res.push_back(root->val);
  if (root->left) dfs(res, root->left);
  if (root->right) dfs(res, root->right);
}
vector<int> preorderTraversal1(TreeNode* root) {
  vector<int> res;
  dfs(res, root);
  return res;
}
//* 非递归写法：
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
//* 递归写法：
void dfs(vector<int>& res, TreeNode* root) {
  if (!root) return;
  if (root->left) dfs(res, root->left);
  res.push_back(root->val);
  if (root->right) dfs(res, root->right);
}
vector<int> inorderTraversal1(TreeNode* root) {
  vector<int> res;
  dfs(res, root);
  return res;
}
//* 非递归写法：
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
namespace LC145 {
//* 递归写法：
void dfs(vector<int>& res, TreeNode* root) {
  if (!root) return;
  if (root->left) dfs(res, root->left);
  if (root->right) dfs(res, root->right);
  res.push_back(root->val);
}
vector<int> postorderTraversal1(TreeNode* root) {
  vector<int> res;
  dfs(res, root);
  return res;
}
//* 非递归写法：
vector<int> postorderTraversal2(TreeNode* root) {
  if (!root) return {};
  vector<int> res;
  stack<TreeNode*> s;
  s.push(root);
  TreeNode* pre = NULL;
  while (!s.empty()) {
    root = s.top();
    // 若
    if ((!root->left && !root->right) ||
        (pre && (pre == root->left || pre == root->right))) {
      res.push_back(root->val);
      s.pop();
      pre = root;
    } else {
      if (root->right) s.push(root->right);
      if (root->left) s.push(root->left);
    }
  }
  return res;
}
//* 思路2：根-右-左的遍历顺序遍历压入所有节点到栈
//* 从栈里弹出的顺序便是左-右-根了
vector<int> postorderTraversal(TreeNode* root) {
  if (!root) return {};
  vector<int> res;
  stack<TreeNode*> s, t;
  s.push(root);
  while (!s.empty()) {
    root = s.top();
    s.pop();
    t.push(root);
    if (root->left) s.push(root->left);
    if (root->right) s.push(root->right);
  }
  while (!t.empty()) {
    res.push_back(t.top()->val);
    t.pop();
  }
  return res;
}
}  // namespace LC145

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
namespace LC590 {
vector<int> postorder(Node* root) {
  if (!root) return {};
  vector<int> res;
  stack<Node*> s;
  s.push(root);
  Node* pre = NULL;
  while (!s.empty()) {
    root = s.top();
    bool visit = false;
    if (pre)
      for (auto item : root->children)
        if (pre == item) {
          visit = true;
          break;
        }

    if ((root->children.empty()) || visit) {
      res.push_back(root->val);
      s.pop();
      pre = root;
    } else {
      for (auto it = root->children.rbegin(); it != root->children.rend(); ++it)
        if (*it != NULL) s.push(*it);
    }
  }
  return res;
}
}  // namespace LC590

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

//! bfs遍历(层序)相关问题
// TODO 637. 二叉树的层平均值
namespace LC637 {
vector<double> averageOfLevels(TreeNode* root) {
  if (!root) return {};
  vector<double> res;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    double sum = 0;
    int n = q.size();
    for (int i = 0; i < n; i++) {
      root = q.front();
      sum += root->val;
      q.pop();
      if (root->left) q.push(root->left);
      if (root->right) q.push(root->right);
    }
    res.push_back(sum / n);
  }
  return res;
}
}  // namespace LC637

// TODO 515. 在每个树行中找最大值
namespace LC515 {
vector<int> largestValues(TreeNode* root) {
  if (!root) return {};
  vector<int> res;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size(), maxV = INT32_MIN;
    for (int i = 0; i < n; i++) {
      root = q.front();
      maxV = max(maxV, root->val);
      q.pop();
      if (root->left) q.push(root->left);
      if (root->right) q.push(root->right);
    }
    res.push_back(maxV);
  }
  return res;
}
}  // namespace LC515

// TODO 199. 二叉树的右视图
namespace LC199 {
//* 思路：显然此题要用层序遍历,找最右边的数
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
//* 思路2:
// 按根-右-左遍历，同时记录当前层数，每新到一层记录第一个节点的值，略显繁琐
}  // namespace LC199

//! dfs遍历 - 中序遍历相关问题
//! dfs中序遍历问题一般结合二叉搜索树(BST)考察，因为二叉搜索树有个特性：其中序遍历序列一定是有序的，由此可以衍生很多问题
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

// TODO 783. 二叉搜索树结点最小距离
namespace LC783 {
//* 思路：中序遍历，记录相邻两节点之间最小差值
// 非递归写法
int minDiffInBST(TreeNode* root) {
  stack<TreeNode*> s;
  int res = INT32_MAX;
  TreeNode* pre = NULL;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      if (pre) res = min(res, root->val - pre->val);
      pre = root;
      root = root->right;
    }
  }
  return res;
}
// 递归写法 (此处pre一定要是全局的)
// void dfs(int& res, TreeNode*& pre, TreeNode* root) {
//   if (!root) return;
//   dfs(res, pre, root->left);
//   if (pre) res = min(res, root->val - pre->val);
//   pre = root;
//   dfs(res, pre, root->right);
// }
// int minDiffInBST(TreeNode* root) {
//   int res = INT32_MAX;
//   TreeNode* pre = NULL;
//   dfs(res, pre, root);
//   return res;
// }
}  // namespace LC783

// TODO 530. 二叉搜索树的最小绝对差
namespace LC530 {
int getMinimumDifference(TreeNode* root) {
  stack<TreeNode*> s;
  int res = INT32_MAX;
  TreeNode* pre = NULL;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      if (pre) res = min(res, root->val - pre->val);
      pre = root;
      root = root->right;
    }
  }
  return res;
}
}  // namespace LC530

// TODO 270. 最接近的二叉搜索树值
namespace LC270 {
//* 思路1：利用中序遍历
// int closestValue(TreeNode* root, double target) {
//   stack<TreeNode*> s;
//   TreeNode* pre = NULL;
//   int res = root->val;
//   while (root || !s.empty()) {
//     if (root) {
//       s.push(root);
//       root = root->left;
//     } else {
//       root = s.top();
//       s.pop();

//       if (double(root->val) >= target) break;
//       pre = root;
//       root = root->right;
//     }
//   }
//   if (!root) return pre->val;
//   if (!pre) return root->val;
//   return (pre->val + root->val < 2 * target) ? root->val : pre->val;
// }

//* 思路2：利用二叉搜索树的性质,二分查找
int closestValue(TreeNode* root, double target) {
  int left = -1;
  int right = -1;
  auto head = root;
  while (head != nullptr) {
    if (target > head->val) {
      left = head->val;
      head = head->right;
    } else {
      right = head->val;
      head = head->left;
    }
  }

  if (left == -1) {
    return right;
  } else if (right == -1) {
    return left;
  }
  if (target - left < right - target) {
    return left;
  } else {
    return right;
  }
}

}  // namespace LC270
// TODO 272. 最接近的二叉搜索树值 II
namespace LC272 {}  // namespace LC272

// TODO 501. 二叉搜索树中的众数
namespace L501 {
//* 思路：中序遍历
void dfs(vector<int>& res, TreeNode*& pre, int& curTimes, int& maxTimes,
         TreeNode* root) {
  if (!root) return;
  dfs(res, pre, curTimes, maxTimes, root->left);
  if (pre) curTimes = (root->val == pre->val) ? curTimes + 1 : 1;
  if (curTimes == maxTimes)
    res.push_back(root->val);
  else if (curTimes > maxTimes) {
    res.clear();
    res.push_back(root->val);
    maxTimes = curTimes;
  }
  pre = root;
  dfs(res, pre, curTimes, maxTimes, root->right);
}
vector<int> findMode(TreeNode* root) {
  vector<int> res;
  TreeNode* pre = NULL;
  int curTimes = 1, maxTimes = 0;
  dfs(res, pre, curTimes, maxTimes, root);
  return res;
}
}  // namespace L501

// TODO 938. 二叉搜索树的范围和
namespace LC938 {
void dfs(int& res, int L, int R, TreeNode* root) {
  if (!root) return;
  dfs(res, L, R, root->left);
  if (root->val >= L && root->val <= R) res += root->val;
  dfs(res, L, R, root->right);
}
int rangeSumBST(TreeNode* root, int L, int R) {
  int res = 0;
  dfs(res, L, R, root);
  return res;
}
}  // namespace LC938

//! dfs遍历 - 前后序遍历相关问题
//! dfs通式：
//!   void dfs(ResultType & res，AddtionalType ..., TreeNode* root){...}
//! 若结果形式比较简单，比如是bool,int这类的：
//!   int dfs(AddtionalType ..., TreeNode* root){...}
//! 其中AddtionalType为附加信息
// TODO 104. 二叉树的最大深度
namespace LC104 {
//* 思路：自底向上，采用后序遍历
// 先计算出子树的最大深度，后续才好判定母树的最大深度
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  // 下句return本质是一个后序遍历，必须先得到子树的解，才能进一步得到母树的解
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
}  // namespace LC104

// TODO 111. 二叉树的最小深度
namespace LC111 {
//* 思路：同LC104
int minDepth(TreeNode* root) {
  if (!root) return 0;
  if (!root->left) return minDepth(root->right) + 1;
  if (!root->right) return minDepth(root->left) + 1;
  return min(minDepth(root->left), minDepth(root->right)) + 1;
}
}  // namespace LC111

// TODO 226.反转二叉树
namespace LC226 {
//* 思路：自底向上，考虑后序遍历
// 先反转左右两个子树，再反转母树
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
//* 思路：考虑到效率的话，应该首先比较根节点的值，故采用前序遍历
bool isSameTree(TreeNode* p, TreeNode* q) {
  if (!p && !q) return true;
  if (bool(p) != bool(q)) return false;
  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}
}  // namespace LC100

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
  return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right) + res;
}
}  // namespace LC404

// TODO 112. 路径总和
namespace LC112 {
//* 思路：需要从根出发，考虑前序遍历，附加信息为当前路径和与target的差值
bool hasPathSum(TreeNode* root, int sum) {
  if (!root) return false;
  if (sum == root->val && !root->left && !root->right) return true;
  return hasPathSum(root->left, sum - root->val) ||
         hasPathSum(root->right, sum - root->val);
}
}  // namespace LC112

// TODO 路径总和 II
namespace LC113 {
//*
//思路：从根出发的dfs，考虑前序遍历，附加信息为当前路径及当前路径和与target的差值
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

// TODO 257. 二叉树的所有路径
namespace LC257 {
//* 思路：从根出发的dfs，考虑前序遍历，附带信息：当前路径
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
//* 思路：从根出发的dfs，考虑前序遍历
int dfs(int tmp, TreeNode* root) {
  if (!root) return 0;
  int res = 0;
  tmp = tmp * 10 + root->val;
  if (!root->left && !root->right) res += tmp;
  res += dfs(tmp, root->left);
  res += dfs(tmp, root->right);
  return res;
}
int sumNumbers(TreeNode* root) { return dfs(0, root); }
}  // namespace LC129

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

//! 双层dfs遍历问题：
//! 内层一般根据题目要求，可灵活选择前序或后序(中序不常见)
//! 外层一般选前、中、后序均可，效率和内存方面差别不是特别明显，不过最终也得根据题目要求而定
//! 注意：1)有时内层采用前序会产生许多不必要的遍历操作，可改进为后序遍历，参见LC110
//!      2)有些题目可简化为单层，(见LC110，LC124)，受这两题启发：凡是能在dfs过程中获得最终解的问题，都可以转换为单层dfs！
//!      3)内层dfs需要附加信息的，一般都是转化不了单层dfs的
//!
//! 典型问题如：
//!   路径问题（路径和、路径数字、路径字符、路径序列等）
//!
//! dfs通式：
//!   void dfs(ResultType & res，AddtionalType ..., TreeNode* root){...}
//! 若结果形式比较简单，比如是bool,int这类的：
//!   int dfs(AddtionalType ..., TreeNode* root){...}
//! 分解问题通式：
//!   根树的解 = func(左子树的解，右子树的解，dfs(root)的解)
//!

// TODO 101. 对称二叉树
namespace LC101 {
//* 思路：考虑到效率的话，应该首先比较根节点的值，故采用前序遍历
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

// TODO 110. 平衡二叉树
namespace LC110 {
//* 思路2：双层遍历转换为单层遍历
// 内层dfs：当左右子树不平衡时，直接向上传递-1，表示此树不为平衡树，这样就不用遍历所有其他节点求深度了，相当于提前截断此次内层遍历
// 这样实际是将两层遍历降为单层dfs遍历问题
int dfs(TreeNode* root) {
  if (!root) return 0;
  int left = dfs(root->left), right = dfs(root->right);
  if (left == -1 || right == -1) return -1;
  int res = abs(left - right);
  return res > 1 ? -1 : (max(left, right) + 1);
}
bool isBalanced(TreeNode* root) {
  if (!root) return true;
  // return isBalanced(root->left) && isBalanced(root->right) && dfs(root) !=
  // -1;
  return dfs(root) != -1;  // 改进此处可减少一般内存消耗
}
//* 思路1： 双层遍历
// 内层是求根树的最大深度，后续遍历
// 外层是从根出发，比较左右子树最大深度，采用的前序遍历，是自顶向下的，这没啥毛病，但问题出在求每个节点最大深度会产生很多冗余操作，会带来效率问题！
// int dfs(TreeNode* root) {
//   if (!root) return 0;
//   return max(dfs(root->left), dfs(root->right)) + 1;
// }
// bool isBalanced(TreeNode* root) {
//   if (!root) return true;
//   if (abs(dfs(root->left) - dfs(root->right)) > 1) return false;
//   return isBalanced(root->left) && isBalanced(root->right);
// }
}  // namespace LC110

// TODO 124. 二叉树中的最大路径和
namespace LC124 {
//* 思路3： 可优化为单层 耗时：40ms
// dfs返回从根节点出发的最大路径和
// 同时计算经过该节点的最大路径和，用全局变量res维护求得的最大值
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
// //* 思路2：内层前序遍历 + 外层后序遍历 leetcode耗时：800ms
// // dfs返回从根出发的最大路径和
// void dfs(int& maxSum, int cur, TreeNode* root) {
//   if (!root) return;
//   cur += root->val;
//   maxSum = max(maxSum, cur);
//   dfs(maxSum, cur, root->left);
//   dfs(maxSum, cur, root->right);
// }
// int maxPathSum(TreeNode* root) {
//   if (!root) return INT32_MIN;
//   int lmax = INT32_MIN, rmax = INT32_MIN;
//   dfs(lmax, 0, root->left);
//   dfs(rmax, 0, root->right);
//   int m = (lmax > 0 ? lmax : 0) + (rmax > 0 ? rmax : 0) + root->val;
//   int lr = max(maxPathSum(root->left), maxPathSum(root->right));
//   return max(m, lr);
// }

// //* 思路1： 内层后续，外层后续，leetcode耗时：1100ms
// // dfs返回从根出发的最大路径和
// int dfs(TreeNode* root) {
//   if (!root) return 0;
//   int l = dfs(root->left);
//   int r = dfs(root->right);
//   return max(max(l, r) + root->val, root->val);
// }
// int maxPathSum(TreeNode* root) {
//   if (!root) return INT32_MIN;
//   int lr = max(maxPathSum(root->left), maxPathSum(root->right));
//   int l = dfs(root->left);
//   int r = dfs(root->right);
//   int m = (l > 0 ? l : 0) + (r > 0 ? r : 0) + root->val;
//   return max(lr, m);
// }
}  // namespace LC124

// TODO 437. 路径总和 III
namespace LC437 {
//* 思路：双层遍历问题
// 内层：dfs，求从根出发的路径和等于target的路径数，前序遍历；
// 外层：分解问题：根树的解 =
// func(左子树的解，右子树的解，dfs(root)的解)，前中后序遍历均可
int dfs(int sum, TreeNode* root) {
  if (!root) return 0;
  return (root->val == sum) + dfs(sum - root->val, root->left) +
         dfs(sum - root->val, root->right);
}
int pathSum(TreeNode* root, int sum) {
  if (!root) return 0;
  return pathSum(root->left, sum) + pathSum(root->right, sum) + dfs(sum, root);
}
}  // namespace LC437

// TODO 687. 最长同值路径
namespace LC687 {
//* 两层：
//* 一层是求从根出发的最长同值路径，前序遍历
// 外层：分解问题：根树的解 =
// func(左子树的解，右子树的解，dfs(root)的解)，前中后序遍历均可
int dfs(int val, TreeNode* root) {
  if (!root || root->val != val) return 0;
  return 1 + max(dfs(val, root->left), dfs(val, root->right));
}
int longestUnivaluePath(TreeNode* root) {
  if (!root) return 0;
  int sub =
      max(longestUnivaluePath(root->left), longestUnivaluePath(root->right));
  return max(sub, dfs(root->val, root->left) + dfs(root->val, root->right));
}
}  // namespace LC687

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

// TODO 298. 二叉树最长连续序列
namespace LC298 {
//* 思路：内层后序遍历，求从根出发的最长连续序列长度
int dfs(int val, TreeNode* root) {
  if (!root || root->val != val) return 0;
  int l = dfs(val + 1, root->left);
  int r = dfs(val + 1, root->right);
  return max(l, r) + 1;
}
int longestConsecutive(TreeNode* root) {
  if (!root) return 0;
  int res = dfs(root->val, root);
  res = max(res, longestConsecutive(root->left));
  res = max(res, longestConsecutive(root->right));
  return res;
}
}  // namespace LC298

// TODO 549. 二叉树中最长的连续序列
namespace LC549 {}  // namespace LC549

// TODO 250. 统计同值子树
namespace LC250 {
// 这里实际是前序遍历了一遍树来判断是否root树为同值树
// 也可以用中序遍历，后序遍历，只要是深度优先遍历就行
int dfs(TreeNode* root, int val) {
  if (!root) return 0;
  if (root->val != val) return -1;
  int l = dfs(root->left, val);
  if (l == -1) return -1;
  int r = dfs(root->right, val);
  if (r == -1) return -1;
  return 1;
}
int countUnivalSubtrees(TreeNode* root) {
  if (!root) return 0;
  return countUnivalSubtrees(root->left) + countUnivalSubtrees(root->right) +
         (dfs(root, root->val) > 0);
}
}  // namespace LC250

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

//! 二叉搜索树
// TODO 98. 验证二叉搜索树
namespace LC98 {}  // namespace LC98

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

//! 特殊性较强（言外之意：参考性不强的）放这↓
// TODO 337. 打家劫舍 III
namespace LC337 {}  // namespace LC337

//! 待分类

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