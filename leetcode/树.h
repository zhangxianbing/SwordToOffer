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

// TODO 314. 二叉树的垂直遍历
namespace LC314 {
vector<vector<int>> verticalOrder(TreeNode* root) {}
}  // namespace LC314

// TODO 199. 二叉树的右视图
namespace LC199 {
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

// TODO 104. 二叉树的最大深度
namespace LC104 {
int maxDepth(TreeNode* root) {
  if (!root) return 0;
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
}  // namespace LC104

// TODO 96. 不同的二叉搜索树
namespace LC96 {}  // namespace LC96

// TODO 95. 不同的二叉搜索树 II
namespace LC95 {}  // namespace LC95

namespace LC111 {}  // namespace LC111

// 226.反转二叉树
namespace LC226 {}  // namespace LC226

namespace LC100 {}  // namespace LC100

namespace LC101 {}  // namespace LC101

namespace LC222 {}  // namespace LC222

namespace LC110 {}  // namespace LC110

namespace LC112 {}  // namespace LC112

namespace LC404 {}  // namespace LC404

namespace LC257 {}  // namespace LC257

namespace LC113 {}  // namespace LC113

namespace LC129 {}  // namespace LC129

namespace LC437 {}  // namespace LC437

//! 二分搜索树
namespace LC235 {}  // namespace LC235

namespace LC98 {}  // namespace LC98

namespace LC450 {}  // namespace LC450

namespace LC108 {}  // namespace LC108

namespace LC230 {}  // namespace LC230

namespace LC236 {}  // namespace LC236
