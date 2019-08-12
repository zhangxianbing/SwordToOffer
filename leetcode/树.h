/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 11:29:43
 * @LastEditTime: 2019-08-12 18:38:27
 * @LastEditors: zhangxianbing
 */
#pragma once
#include "../public.h"

//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 二叉树
//# 二叉树天然具有递归的结构，因此涉及很多问题都和遍历、递归有关，
//# dfs通式：
//#   void dfs(ResultType & res，AddtionalType ..., TreeNode* root){...}
//# 若结果形式比较简单，比如是bool,int这类的：
//#   int dfs(AddtionalType ..., TreeNode* root){...}
//# 其中AddtionalType为附加信息
//#
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 遍历基础（前序、中序、后序、层序，以及衍生的变种遍历）
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC144. 二叉树的前序遍历
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

// LC94. 二叉树的中序遍历
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

// LC145. 二叉树的后序遍历
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
// 思路2：根-右-左的遍历顺序遍历压入所有节点到栈
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

// LC102. 二叉树的层次遍历
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

// LC107. 二叉树的层次遍历 II
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

// LC103. 二叉树的锯齿形层次遍历
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

// LC589. N叉树的前序遍历
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

// LC429. N叉树的层序遍历
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

// LC590. N叉树的后序遍历
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

// LC314. 二叉树的垂直遍历
namespace LC314 {
// 思路：此题本质还是一个层序遍历，每个节点附加一个偏移量
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

// LC987. 二叉树的垂序遍历
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

// LC538. 把二叉搜索树转换为累加树
namespace LC538 {
// 思路2：直接进行逆中序操作
TreeNode* convertBST(TreeNode* root) {
  int sum = 0;
  function<void(TreeNode*)> dfs = [&](TreeNode* root) {
    if (!root) return;
    dfs(root->right);
    sum += root->val;
    root->val = sum;
    dfs(root->left);
  };
  dfs(root);
  return root;
}
// 思路1：需要右-根-左的遍历,则先中序遍历把节点存到stack中再访问即可
TreeNode* convertBST(TreeNode* root) {
  if (!root) return NULL;
  stack<TreeNode*> S;
  function<void(stack<TreeNode*>&, TreeNode*)> dfs = [&](stack<TreeNode*>& S,
                                                         TreeNode* root) {
    if (!root) return;
    dfs(S, root->left);
    S.push(root);
    dfs(S, root->right);
  };
  dfs(S, root);
  TreeNode* pre = NULL;
  while (!S.empty()) {
    auto cur = S.top();
    S.pop();
    if (pre) cur->val += pre->val;
    pre = cur;
  }
  return root;
}
}  // namespace LC538

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ bfs遍历 - 层序
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC637. 二叉树的层平均值
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

// LC515. 在每个树行中找最大值
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

// LC199. 二叉树的右视图
namespace LC199 {
// 思路：显然此题要用层序遍历,找最右边的数
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
// 思路2:
// 按根-右-左遍历，同时记录当前层数，每新到一层记录第一个节点的值，略显繁琐，在此略去
}  // namespace LC199

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 单层dfs遍历 - 中序
//$ dfs中序遍历问题一般结合二叉搜索树(BST)考察，
//$ 因为二叉搜索树有个特性：其中序遍历序列一定是有序的，由此可以衍生很多问题
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC98. 验证二叉搜索树
namespace LC98 {
// 思路：中序遍历，若出现逆序数，不为二叉搜索树
bool isValidBST(TreeNode* root) {
  stack<TreeNode*> s;
  TreeNode* pre = NULL;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      if (pre && pre->val >= root->val) return false;
      pre = root;  //! 这里经常忘！！！
      root = root->right;
    }
  }
  return true;
}
}  // namespace LC98

// LC230. 二叉搜索树中第K小的元素
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

// LC783. 二叉搜索树结点最小距离
namespace LC783 {
// 思路：中序遍历，记录相邻两节点之间最小差值
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

// LC530. 二叉搜索树的最小绝对差
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

// LC270. 最接近的二叉搜索树值
namespace LC270 {
// 思路1：利用中序遍历
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

// 思路2：利用二叉搜索树的性质,二分查找
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
// LC272. 最接近的二叉搜索树值 II
namespace LC272 {}  // namespace LC272

// LC501. 二叉搜索树中的众数
namespace L501 {
// 思路：中序遍历
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

// LC938. 二叉搜索树的范围和
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

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 单层dfs遍历 - 前序
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC222. 完全二叉树的节点个数
namespace LC222 {
// 思路：前中后序区别不大
int countNodes(TreeNode* root) {
  if (!root) return 0;
  return countNodes(root->left) + countNodes(root->right) + 1;
}
}  // namespace LC222

// LC101. 对称二叉树
namespace LC101 {
// 思路：考虑到效率的话，应该首先比较根节点的值，故采用前序遍历
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

// LC100. 相同的树
namespace LC100 {
// 思路：考虑到效率的话，应该首先比较根节点的值，故采用前序遍历
bool isSameTree(TreeNode* p, TreeNode* q) {
  if (!p && !q) return true;
  if (bool(p) != bool(q)) return false;
  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}
}  // namespace LC100

// LC112. 路径总和
namespace LC112 {
// 思路：需要从根出发，考虑前序遍历，附加信息为当前路径和与target的差值
bool hasPathSum(TreeNode* root, int sum) {
  if (!root) return false;
  if (sum == root->val && !root->left && !root->right) return true;
  return hasPathSum(root->left, sum - root->val) ||
         hasPathSum(root->right, sum - root->val);
}
}  // namespace LC112

// LC路径总和 II
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

// LC257. 二叉树的所有路径
namespace LC257 {
// 思路：从根出发的dfs，考虑前序遍历，附带信息：当前路径
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

// LC129. 求根到叶子节点数字之和
namespace LC129 {
// 思路：从根出发的dfs，考虑前序遍历
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

// LC988. 从叶结点开始的最小字符串
namespace LC988 {
// 思路：需要从根开始dfs,考虑前序遍历；结果存入map中
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

// LC235. 二叉搜索树的最近公共祖先
namespace LC235 {
// 思路：利用二叉树的性质
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (p->val < root->val && q->val > root->val) return root;
  if (p->val > root->val && q->val < root->val) return root;
  if (p->val < root->val && q->val < root->val)
    return lowestCommonAncestor(root->left, p, q);
  if (p->val > root->val && q->val > root->val)
    return lowestCommonAncestor(root->right, p, q);
  return root;
}
}  // namespace LC235

// LC236. 二叉树的最近公共祖先
namespace LC236 {
// 思路：前序遍历
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (!root || root == p || root == q) return root;
  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);
  return !left ? right : !right ? left : root;
}
}  // namespace LC236

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 单层dfs遍历 - 后序
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC404. 左叶子之和
namespace LC404 {
// 思路：自底向上的dfs,考虑后序遍历
int sumOfLeftLeaves(TreeNode* root) {
  if (!root) return 0;
  int res = 0;
  if (root->left && !root->left->left && !root->left->right)
    res = root->left->val;
  return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right) + res;
}
}  // namespace LC404

// LC104. 二叉树的最大深度
namespace LC104 {
// 思路：自底向上，采用后序遍历
// 先计算出子树的最大深度，后续才好判定母树的最大深度
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  // 下句return本质是一个后序遍历，必须先得到子树的解，才能进一步得到母树的解
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
}  // namespace LC104

// LC111. 二叉树的最小深度
namespace LC111 {
// 思路：自底向上，采用后序遍历
int minDepth(TreeNode* root) {
  if (!root) return 0;
  if (!root->left) return minDepth(root->right) + 1;
  if (!root->right) return minDepth(root->left) + 1;
  return min(minDepth(root->left), minDepth(root->right)) + 1;
}
}  // namespace LC111

// LC226.反转二叉树
namespace LC226 {
// 思路：自底向上，考虑后序遍历
// 先反转左右两个子树，再反转母树
TreeNode* invertTree(TreeNode* root) {
  if (!root) return NULL;
  root->left = invertTree(root->left);
  root->right = invertTree(root->right);
  swap(root->left, root->right);
  return root;
}
}  // namespace LC226

// LC508. 出现次数最多的子树元素和
namespace LC508 {
// 思路： 后序遍历求各子树的和,并存入一个map中
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

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 双层dfs遍历问题：
//$ 内层一般根据题目要求，可灵活选择前序或后序(中序不常见)
//$ 外层一般选前中后序均可，差别不是特别明显，不过最终也得根据题目而定
//$
//$ 典型问题如：
//$   路径问题（路径和、路径数字、路径字符、路径序列等）
//$
//$ dfs通式：
//$   void dfs(ResultType & res，AddtionalType ..., TreeNode* root){...}
//$ 若结果形式比较简单，比如是bool,int这类的：
//$   int dfs(AddtionalType ..., TreeNode* root){...}
//$ 分解问题通式：
//$   根树的解 = func(左子树的解，右子树的解，dfs(root)的解)
//$
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC572. 另一个树的子树
namespace LC572 {
//* 需要从根开始验证，故选前序遍历，外层同样也选前序遍历
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

// LC437. 路径总和 III
namespace LC437 {
// 思路：双层遍历问题
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

// LC1120. 子树的最大平均值
namespace LC1120 {}  // namespace LC1120

// LC865. 具有所有最深结点的最小子树
namespace LC865 {}  // namespace LC865

// LC663. 均匀树划分
namespace LC663 {}  // namespace LC663

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 可以转化为单层后序遍历的双层dfs问题
//$ 自顶向上信息传递的逻辑是解决这类题的关键
//$
//$ 纵观(LC110，LC124,LC298)，受到的启发是：
//  $1)可以自底向上传递信息(即通过左右子树的结果能推导出根树的结果)的问题宜采用后序遍历，尤其注意的是从根节点出发的最大路径和，表面上看用前序遍历做很合理，但实际采用后序遍历更有效率，而有的信息很难自底向上传递，比如LC437的路径和，则需要通过内层前序遍历+外层dfs来做
//  $2)不要固化思维的认为一个递归函数一定仅仅完成一项工作
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC110. 平衡二叉树
// 推荐度：★★★★☆
namespace LC110 {
// 思路2：单层后序遍历
// 内层改进后序遍历，当左右子树不平衡时，直接向上传递-1，表示此树不为平衡树，这样就不用遍历所有其他节点求深度了，相当于提前截断此次内层遍历
// 这样实际是将两层遍历降为单层dfs遍历问题
int dfs(TreeNode* root) {
  if (!root) return 0;
  int left = dfs(root->left);
  if (left == -1) return -1;  // 提前截断
  int right = dfs(root->right);
  if (right == -1) return -1;  // 提前截断
  int res = abs(left - right);
  return res > 1 ? -1 : (max(left, right) + 1);
}
bool isBalanced(TreeNode* root) {
  if (!root) return true;
  return dfs(root) != -1;
}
// 思路1： 双层遍历
// 内层是求根树的最大深度，后续遍历
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

// LC250. 统计同值子树
namespace LC250 {
// 思路2：单层后序遍历
bool dfs(int& res, TreeNode* root) {
  if (!root) return true;
  bool L = dfs(res, root->left);
  if (root->left && root->left->val != root->val)
    L = false;  //! 注意不能在这提前截断，否则会遍历不全
  bool R = dfs(res, root->right);
  if (root->right && root->right->val != root->val)
    R = false;  //! 注意不能在这提前截断，否则会遍历不全
  res += L && R;
  return L && R;
}
int countUnivalSubtrees(TreeNode* root) {
  int res = 0;
  dfs(res, root);
  return res;
}

// 思路1：双层遍历
// 这里实际是前序遍历了一遍树来判断是否root树为同值树
// 也可以用中序遍历，后序遍历，只要是深度优先遍历就行
// int dfs(int val, TreeNode* root) {
//   if (!root) return 0;
//   if (root->val != val) return -1;
//   int l = dfs(val, root->left);
//   if (l == -1) return -1;
//   int r = dfs(val, root->right);
//   if (r == -1) return -1;
//   return 1;
// }
// int countUnivalSubtrees(TreeNode* root) {
//   if (!root) return 0;
//   return countUnivalSubtrees(root->left) + countUnivalSubtrees(root->right) +
//          (dfs(root->val, root) > 0);
// }
}  // namespace LC250

// LC124. 二叉树中的最大路径和
namespace LC124 {
// 思路3： 单层后序遍历 耗时：40ms
// dfs返回从根节点出发的最大路径和
int dfs(int& res, TreeNode* root) {
  if (!root) return 0;
  int left_max = dfs(res, root->left);
  int right_max = dfs(res, root->right);
  int mid_max = (left_max > 0 ? left_max : 0) +
                (right_max > 0 ? right_max : 0) + root->val;  //! 关键点
  // 计算经过该节点的最大路径和，用全局变量res维护求得的最大值
  res = max(res, mid_max);
  return max(max(left_max, right_max) + root->val, root->val);  //! 关键点
}
int maxPathSum(TreeNode* root) {
  int res = INT32_MIN;
  dfs(res, root);
  return res;
}
// // 思路2：内层前序遍历 + 外层后序遍历 leetcode耗时：800ms
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

// // 思路1： 内层后续，外层后续，leetcode耗时：1100ms
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

// LC687. 最长同值路径
namespace LC687 {
//* 单层后序遍历 耗时：170ms
// dfs返回的是从当前根节点出发的最长同值路径
int dfs(int& res, TreeNode* root) {
  if (!root) return 0;
  int L = dfs(res, root->left);
  int R = dfs(res, root->right);
  L = (root->left && root->left->val == root->val) ? L + 1 : 0;    //! 关键点
  R = (root->right && root->right->val == root->val) ? R + 1 : 0;  //! 关键点
  res = max(res, L + R);
  return max(L, R);  //! 关键点
}
int longestUnivaluePath(TreeNode* root) {
  int res = 0;
  dfs(res, root);
  return res;
}
//* 两层遍历：  耗时：200ms
// 内层：求从根出发的最长同值路径，前序遍历
// 外层：分解问题，前中后序遍历均可
// int dfs(int val, TreeNode* root) {
//   if (!root || root->val != val) return 0;
//   return 1 + max(dfs(val, root->left), dfs(val, root->right));
// }
// int longestUnivaluePath(TreeNode* root) {
//   if (!root) return 0;
//   int sub =
//       max(longestUnivaluePath(root->left), longestUnivaluePath(root->right));
//   return max(sub, dfs(root->val, root->left) + dfs(root->val, root->right));
// }
}  // namespace LC687

// LC298. 二叉树最长连续序列
namespace LC298 {
// 思路3：单层dfs后序遍历解决 耗时：44ms
// dfs返回的是从当前根节点出发的最长连续序列长
int dfs(int& res, TreeNode* root) {
  if (!root) return 0;
  int L = dfs(res, root->left) + 1;
  int R = dfs(res, root->right) + 1;
  if (root->left && root->left->val != root->val + 1) L = 1;    //! 关键点
  if (root->right && root->right->val != root->val + 1) R = 1;  //! 关键点
  int len = max(L, R);
  res = max(res, len);
  return len;  //! 关键点
}
int longestConsecutive(TreeNode* root) {
  int res = 0;
  dfs(res, root);
  return res;
}

// 思路2：单层dfs前序遍历解决 耗时：50ms
// void dfs(int& res, TreeNode* pre, int len, TreeNode* root) {
//   if (!root) return;
//   len = (pre && pre->val + 1 == root->val) ? len + 1 : 1;
//   res = max(res, len);
//   dfs(res, root, len, root->left);
//   dfs(res, root, len, root->right);
// }
// int longestConsecutive(TreeNode* root) {
//   int res = 0;
//   dfs(res, NULL, 0, root);
//   return res;
// }

// 思路1：内层后序遍历，求从根出发的最长连续序列长度 耗时：1100ms
// int dfs(int val, TreeNode* root) {
//   if (!root || root->val != val) return 0;
//   int l = dfs(val + 1, root->left);
//   int r = dfs(val + 1, root->right);
//   return max(l, r) + 1;
// }
// int longestConsecutive(TreeNode* root) {
//   if (!root) return 0;
//   int res = dfs(root->val, root);
//   res = max(res, longestConsecutive(root->left));
//   res = max(res, longestConsecutive(root->right));
//   return res;
// }
}  // namespace LC298

// LC549. 二叉树中最长的连续序列
namespace LC549 {}  // namespace LC549

// LC333. 最大 BST 子树
namespace LC333 {
// 思路：后序遍历
// dfs返回以该节点为根的二叉搜索树的节点个数，若本树不符合二叉搜索树，则返回-1,若为空则返回0
int dfs(int& res, int& minV, int& maxV, TreeNode* root) {
  if (!root) return 0;
  if (!root->left && !root->right) {
    minV = root->val;
    maxV = root->val;
    return 1;
  }
  int lmin, lmax, rmin, rmax;
  bool isBST = true;
  int L = dfs(res, lmin, lmax, root->left);
  int R = dfs(res, rmin, rmax, root->right);
  if (L == -1 || R == -1) return -1;  //! 提前截断
  if ((L != 0 && root->val <= lmax) || R != 0 && root->val >= rmin)
    return -1;  //! 提前截断
  // 若此时本树还符合二叉搜索树，则继续维护最大最小值
  minV = L ? lmin : root->val;  //! 关键在于如何维护最大最小值！！！
  maxV = R ? rmax : root->val;  //! 关键在于如何维护最大最小值！！！
  int N = L + R + 1;
  res = max(res, N);
  return N;
}
int largestBSTSubtree(TreeNode* root) {
  if (!root) return 0;
  int res = 1, minV, maxV;
  dfs(res, minV, maxV, root);
  return res;
}
// 思路2：双层遍历，因繁琐忽略
}  // namespace LC333

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 距离问题
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC834. 树中距离之和
namespace LC834 {}  // namespace LC834

// LC1026. 节点与其祖先之间的最大差值
namespace LC1026 {}  // namespace LC1026

// LC1123. 最深叶节点的最近公共祖先
namespace LC1123 {}  // namespace LC1123

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 二叉树的序列问题
//$ 此类题考察的就比较综合了
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC105. 从前序与中序遍历序列构造二叉树
// 推荐度：★★★★☆
namespace LC105 {
// 思路3：12ms 非递归
TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
  if (pre.empty()) return NULL;
  stack<TreeNode*> S;
  TreeNode* root = new TreeNode(pre[0]);
  S.push(root);
  // i-前序序号，j-中序序号
  for (int i = 1, j = 0; i < pre.size(); i++) {
    TreeNode *back = NULL, *cur = new TreeNode(pre[i]);
    while (!S.empty() && S.top()->val == in[j]) back = S.top(), S.pop(), j++;
    if (back)
      back->right = cur;
    else
      S.top()->left = cur;
    S.push(cur);
  }
  return root;
}

// 思路2：12ms
// 相比思路1，改进了在前序中找左右子树分界位置的处理，由于子树的前序和中序是等长的，而由中序很好求出左右子树的长度，因此改进如下：
// TreeNode* dfs(vector<int>& P, int pi, int pj, vector<int>& Q, int qi, int qj,
//               unordered_map<int, int>& M) {
//   if (pi >= pj || qi >= qj) return NULL;
//   int pos = M[P[pi]] - qi;  // 从中序序列获取左子树的长度
//   auto root = new TreeNode(P[pi]);
//   root->left = dfs(P, pi + 1, pi + pos + 1, Q, qi, qi + pos + 1, M);
//   root->right = dfs(P, pi + pos + 1, pj, Q, qi + pos + 1, qj, M);
//   return root;
// }
// TreeNode* buildTree(vector<int>& P, vector<int>& Q) {
//   unordered_map<int, int> M;  //记录各数在中序中的位置
//   for (int i = 0; i < Q.size(); ++i) M[Q[i]] = i;
//   return dfs(P, 0, P.size(), Q, 0, Q.size(), M);
// }

// 思路1：200ms
//前序的第一个元素肯定是根节点，中序中根节点左侧全是左子树，右侧全是右子树，由此可以确定根节点以及左右子树的前序和中序，由此可以写成递归
// TreeNode* dfs(vector<int>& P, int pi, int pj, vector<int>& Q, int qi, int qj,
//               unordered_map<int, int>& M) {
//   if (pi > pj) return NULL;
//   auto root = new TreeNode(P[pi]);
//   int pm = pi + 1, qm = M[P[pi]];
//   for (; pm <= pj; pm++)
//     if (M[P[pm]] >= qm) break;
//   pm--;
//   root->left = dfs(P, pi + 1, pm, Q, qi, qm - 1, M);
//   root->right = dfs(P, pm + 1, pj, Q, qm + 1, qj, M);
//   return root;
// }
// TreeNode* buildTree(vector<int>& P, vector<int>& Q) {
//   unordered_map<int, int> M;  //记录各数在中序中的位置
//   for (int i = 0; i < Q.size(); i++) M[Q[i]] = i;
//   return dfs(P, 0, P.size() - 1, Q, 0, Q.size() - 1, M);
// }
}  // namespace LC105

// LC106. 从中序与后序遍历序列构造二叉树
// 推荐度：★★★★☆
namespace LC106 {
//* 非递归版
TreeNode* buildTree(vector<int>& in, vector<int>& post) {
  if (in.empty()) return NULL;
  stack<TreeNode*> S;
  TreeNode *root = new TreeNode(post.back()), *cur = root;
  S.push(root);
  for (int i = post.size() - 2, j = in.size() - 1; i >= 0; i--) {
    TreeNode *back = NULL, *cur = new TreeNode(post[i]);
    while (!S.empty() && S.top()->val == in[j]) back = S.top(), S.pop(), j--;
    if (back)
      back->left = cur;
    else
      S.top()->right = cur;
    S.push(cur);
  }
  return root;
}
//* 递归版
// TreeNode* dfs(vector<int>& inorder, int i1, int j1, vector<int>& postorder,
//               int i2, int j2, unordered_map<int, int>& M) {
//   if (i1 >= j1 || i2 >= j2) return NULL;
//   auto root = new TreeNode(postorder[j2 - 1]);
//   int rlen = j1 - M[postorder[j2 - 1]] - 1;  // 从中序序列获取右子树的长度
//   root->right =
//       dfs(inorder, j1 - rlen, j1, postorder, j2 - 1 - rlen, j2 - 1, M);
//   root->left = dfs(inorder, i1, j1 - rlen - 1, postorder, i2, j2 - 1 - rlen,
//   M); return root;
// }
// TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//   unordered_map<int, int> M;
//   for (int i = 0; i < inorder.size(); i++) M[inorder[i]] = i;
//   return dfs(inorder, 0, inorder.size(), postorder, 0, postorder.size(), M);
// }
}  // namespace LC106

// LC889. 根据前序和后序遍历构造二叉树
// 推荐度：★★★★☆
namespace LC889 {
//* 非递归版2
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
  if (pre.empty()) return NULL;
  stack<TreeNode*> S;
  auto root = new TreeNode(pre[0]);
  S.push(root);
  for (int i = 1, j = 0; i < pre.size(); i++) {
    auto node = new TreeNode(pre[i]);
    while (S.top()->val == post[j]) S.pop(), j++;  // 回溯
    if (!S.top()->left)
      S.top()->left = node;
    else
      S.top()->right = node;
    S.push(node);
  }
  return root;
}
}  // namespace LC889

// LC1008. 先序遍历构造二叉搜索树
namespace LC1008 {
//* 非递归：
TreeNode* bstFromPreorder(vector<int>& pre) {
  if (pre.empty()) return NULL;
  stack<TreeNode*> S;
  auto root = new TreeNode(pre[0]);
  S.push(root);
  for (int i = 1; i < pre.size(); i++) {
    TreeNode* back = NULL;
    TreeNode* node = new TreeNode(pre[i]);
    while (!S.empty() && S.top()->val < pre[i])
      back = S.top(), S.pop();  // 若无法在当前位置插入该节点，则回溯父节点
    if (back)
      back->right = node;
    else
      S.top()->left = node;
    S.push(node);
  }
  return root;
}
//* 递归
// pre和i确定当前节点，(lower, upper) 表示当前位置可以插入的节点的值的上下界。
// 若pre[i]在该范围内，则说明可以在此创建节点
// TreeNode* dfs(vector<int>& pre, int& i, int lower, int upper) {
//   if (i >= pre.size()) return NULL;
//   int val = pre[i];
//   if (val < lower || val > upper) return NULL;
//   auto root = new TreeNode(val);
//   i++;
//   root->left = dfs(pre, i, lower, val);
//   root->right = dfs(pre, i, val, upper);
//   return root;
// }
// TreeNode* bstFromPreorder(vector<int>& pre) {
//   int i = 0;
//   return dfs(pre, i, INT32_MIN, INT32_MAX);
// }
}  // namespace LC1008

// LC255. 验证前序遍历序列二叉搜索树
// 推荐度：★★★★☆ 理由：复用原数组模拟栈，优化内存
namespace LC255 {
/*
思路：对于一个搜索二叉树的前序序列来说, 如果某段序列为一个递减序列,
说明这是一段沿着左子树的路径. 直到碰到一个比前一个大的值,
说明此时已经来到某个结点的右子树上了, 而此时可以得出一个此后序列的下界值,
^也就是此后序列的任意一个值必须要比这个结点的父结点的值大,
因为对于搜索二叉树来说根节点左边的都比根节点小, 而根节点右边的都比根节点大,
所以既然现在已经来到某个结点(设为A)的右子树上,
那么此后任何结点的值必然比A的值大. 
那么当我们碰到一个比之前结点大的值如何找到他的父结点呢? 可以借助一个栈,
即如果当前结点比栈顶元素小, 就入栈, 如果当前值大于栈顶值,
则让所有比当前结点小的值都出栈, 直到栈顶元素比当前结点大,
则最后一个出栈的比当前结点小的值就是当前结点的父结点,
我们只要在栈元素出栈的时候更新最小下界再将当前元素入栈即可.
另外这样的时间和空间复杂度都是O(n), 但是对于空间复杂度来说,
很容易复用原数组模拟栈来优化.
 */
bool verifyPreorder(vector<int>& pre) {
  int k = -1, Min = INT32_MIN;
  for (auto val : pre) {
    if (val < Min) return false;
    while (k >= 0 && pre[k] < val) Min = pre[k--];
    pre[++k] = val;  // 划重点：复用原数组模拟栈,以优化内存
  }
  return true;
}
}  // namespace LC255

// LC1028. 从先序遍历还原二叉树
namespace LC1028 {
//*
//思路：若'-'相比前面的增加，则为前个节点的左节点，若'-'相同，则为上个节点的右兄弟，否则，回溯
void readS(vector<pair<int, int>>& V, string str) {
  int n = str.size(), i = 0, j = 0, val, dep;
  while (j < n) {
    i = j;
    while (j < n && str[j] == '-') j++;
    dep = j - i;
    i = j;
    while (j < n && str[j] != '-') j++;
    val = stoi(str.substr(i, j - i));
    V.push_back(make_pair(val, dep));
  }
}
TreeNode* recoverFromPreorder(string str) {
  if (str.empty()) return NULL;
  vector<pair<int, int>> V;  //节点值和深度
  readS(V, str);
  auto root = new TreeNode(V[0].first);
  stack<pair<TreeNode*, int>> S;
  S.push(make_pair(root, 0));
  for (int i = 1; i < V.size(); i++) {
    TreeNode* cur = new TreeNode(V[i].first);
    while (S.top().second >= V[i].second) S.pop();
    if (S.top().first->left)
      S.top().first->right = cur;
    else
      S.top().first->left = cur;
    S.push(make_pair(cur, V[i].second));
  }
  return root;
}
void test() {
  string line;
  while (getline(cin, line)) {
    string S = stringToString(line);

    TreeNode* ret = recoverFromPreorder(S);

    string out = treeNodeToString(ret);
    cout << out << endl;
  }
}
}  // namespace LC1028

// LC971. 翻转二叉树以匹配先序遍历
namespace LC971 {}  // namespace LC971

// LC449. 序列化和反序列化二叉搜索树
// 推荐度：★★★★☆ 理由：存储数据方式
namespace LC449 {
void inorderDFS(TreeNode* root, string& order) {
  if (!root) return;
  char buf[4];
  // 划重点：题目要求以string形式存储，为此可以将int转为4字符存为string
  memcpy(buf, &(root->val), sizeof(int));
  for (int i = 0; i < sizeof(int); i++) order.push_back(buf[i]);
  inorderDFS(root->left, order);
  inorderDFS(root->right, order);
}
string serialize(TreeNode* root) {
  string order;
  inorderDFS(root, order);
  return order;
}

TreeNode* reconstruct(const string& buffer, int& pos, int minValue,
                      int maxValue) {
  if (pos >= buffer.size()) return NULL;
  int value;
  memcpy(&value, &buffer[pos], sizeof(int));
  if (value < minValue || value > maxValue) return NULL;

  TreeNode* node = new TreeNode(value);
  pos += sizeof(int);
  node->left = reconstruct(buffer, pos, minValue, value);
  node->right = reconstruct(buffer, pos, value, maxValue);
  return node;
}
TreeNode* deserialize(string data) {
  int pos = 0;
  return reconstruct(data, pos, INT32_MIN, INT32_MAX);
}
}  // namespace LC449

// LC297. 二叉树的序列化与反序列化
namespace LC297 {}  // namespace LC297

// LC428. 序列化和反序列化 N 叉树
namespace LC428 {}  // namespace LC428

// LC536. 从字符串生成二叉树
namespace LC536 {}  // namespace LC536

// LC652. 寻找重复的子树
namespace LC652 {
//? 待理解？
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
  // 树id，
  unordered_map<long, pair<int, int>> counts;
  vector<TreeNode*> ans;
  function<int(TreeNode*)> getId = [&](TreeNode* r) {
    if (!r) return 0;
    long key = (static_cast<long>(static_cast<unsigned>(r->val)) << 32) |
               (getId(r->left) << 16) | getId(r->right);
    auto& p = counts[key];
    if (p.second++ == 0)
      p.first = counts.size();
    else if (p.second == 2)
      ans.push_back(r);
    return p.first;
  };
  getId(root);
  return ans;
}
// 思路1：先将树序列化为string，再在string里找
}  // namespace LC652

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 树的节点操作问题
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC114. 二叉树展开为链表
//? 待理解
namespace LC114 {
// 思路，前序遍历
void flatten(TreeNode* root) {
  if (root == nullptr) return;
  flatten(root->left);
  flatten(root->right);
  if (root->left != nullptr) {
    auto pre = root->left;
    while (pre->right != nullptr) pre = pre->right;
    pre->right = root->right;
    root->right = root->left;
    root->left = nullptr;
  }
  root = root->right;
  return;
}
}  // namespace LC114

// LC426. 将二叉搜索树转化为排序的双向链表
namespace LC426 {}  // namespace LC426

// LC655. 输出二叉树
namespace LC655 {}  // namespace LC655

// LC814. 二叉树剪枝
namespace LC814 {}  // namespace LC814

// LC108. 将有序数组转换为二叉搜索树
namespace LC108 {}  // namespace LC108

// LC431. 将 N 叉树编码为二叉树
namespace LC431 {}  // namespace LC431

// LC450. 删除二叉搜索树中的节点
namespace LC450 {}  // namespace LC450

// LC701. 二叉搜索树中的插入操作
namespace LC701 {}  // namespace LC701

// LC700. 二叉搜索树中的搜索
namespace LC700 {}  // namespace LC700

// LC669. 修剪二叉搜索树
namespace LC669 {}  // namespace LC669

// LC99. 恢复二叉搜索树
namespace LC99 {}  // namespace LC99

// LC776. 拆分二叉搜索树
namespace LC776 {}  // namespace LC776

// LC623. 在二叉树中增加一行
namespace LC623 {}  // namespace LC623

// LC156. 上下翻转二叉树
namespace LC156 {}  // namespace LC156

// LC337. 打家劫舍 III
namespace LC337 {}  // namespace LC337

//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
//$ 待分类
//$ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ $//
// LC662. 二叉树最大宽度
namespace LC662 {}  // namespace LC662

// LC559. N叉树的最大深度
namespace LC559 {}  // namespace LC559

// LC654. 最大二叉树
namespace LC654 {}  // namespace LC654

// LC998. 最大二叉树 II
namespace LC998 {}  // namespace LC998

// LC606. 根据二叉树创建字符串
namespace LC606 {}  // namespace LC606

// LC968. 监控二叉树
namespace LC968 {}  // namespace LC968

// LC979. 在二叉树中分配硬币
namespace LC979 {}  // namespace LC979

// LC958. 二叉树的完全性检验
namespace LC958 {}  // namespace LC958

// LC894. 所有可能的满二叉树
namespace LC894 {}  // namespace LC894

// LC993. 二叉树的堂兄弟节点
namespace LC993 {}  // namespace LC993

// LC671. 二叉树中第二小的节点
namespace LC671 {}  // namespace LC671

// LC653. 两数之和 IV - 输入 BST
namespace LC653 {}  // namespace LC653

// LC116. 填充每个节点的下一个右侧节点指针
namespace LC116 {}  // namespace LC116

// LC117. 填充每个节点的下一个右侧节点指针 II
namespace LC117 {}  // namespace LC117

// LC173. 二叉搜索树迭代器
namespace LC173 {}  // namespace LC173

// LC872. 叶子相似的树
namespace LC872 {}  // namespace LC872

// LC513. 找树左下角的值
namespace LC513 {}  // namespace LC513

// LC617. 合并二叉树
namespace LC617 {}  // namespace LC617

// LC1145. 二叉树着色游戏
namespace LC1145 {}  // namespace LC1145

// LC1104. 二叉树寻路
namespace LC1104 {}  // namespace LC1104

// LC1022. 从根到叶的二进制数之和
namespace LC1022 {}  // namespace LC1022

// LC965. 单值二叉树
namespace LC965 {}  // namespace LC965

// LC951. 翻转等价二叉树
namespace LC951 {}  // namespace LC951

// LC919. 完全二叉树插入器
namespace LC919 {}  // namespace LC919

// LC897. 递增顺序查找树
namespace LC897 {}  // namespace LC897

// LC684. 冗余连接
namespace LC684 {}  // namespace LC684

// LC685. 冗余连接 II
namespace LC685 {}  // namespace LC685

// LC582. 杀死进程
namespace LC582 {}  // namespace LC582

// LC563. 二叉树的坡度
namespace LC563 {}  // namespace LC563

// LC545. 二叉树的边界
namespace LC545 {}  // namespace LC545

// LC285. 二叉搜索树中的顺序后继
namespace LC285 {}  // namespace LC285

// LC510. 二叉搜索树中的中序后继 II
namespace LC510 {}  // namespace LC510

// LC366. 寻找完全二叉树的叶子节点
namespace LC366 {}  // namespace LC366

// LC666. 路径和 IV
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