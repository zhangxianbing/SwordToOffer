#pragma once

// 记录各种常用，基础，漂亮的算法、解法

#include "public.h"

// 各种遍历非递归写法汇总
namespace OrderIter {
void func(TreeNode* node) { cout << node->val << " "; }
// 前序遍历
void preOrderIter(TreeNode* root) {
  stack<TreeNode*> s;
  s.push(root);
  while (!s.empty()) {
    TreeNode* node = s.top();
    s.pop();
    if (!node) continue;
    func(node);
    s.push(node->right);
    s.push(node->left);
  }
}

void preOrderIter2(TreeNode* root) {
  stack<TreeNode*> s;
  while (root || !s.empty()) {
    if (root) {
      func(root);
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      root = root->right;
    }
  }
}

// 中序遍历，思路和preOrder2相似
void inOrderIter(TreeNode* root) {
  stack<TreeNode*> s;
  while (root || !s.empty()) {
    if (root) {
      s.push(root);
      root = root->left;
    } else {
      root = s.top();
      s.pop();
      func(root);
      root = root->right;
    }
  }
}

// 后续遍历，本质是先按
// 根-右-左的遍历顺序遍历压入所有节点到栈，然后从栈里弹出的顺序便是左-右-根了
void postOrderIter(TreeNode* root) {
  if (!root) return;
  stack<TreeNode*> s, t;
  s.push(root);
  while (!s.empty()) {
    TreeNode* cur = s.top();
    s.pop();
    t.push(cur);
    if (cur->left) s.push(cur->left);
    if (cur->right) s.push(cur->right);
  }
  while (!t.empty()) {
    func(t.top());
    t.pop();
  }
}
// 要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
void postOrderIter2(TreeNode* root) {
  stack<TreeNode*> s;
  TreeNode* cur;         //当前结点
  TreeNode* pre = NULL;  //前一次访问的结点
  s.push(root);
  while (!s.empty()) {
    cur = s.top();
    if ((cur->left == NULL && cur->right == NULL) ||
        (pre != NULL && (pre == cur->left || pre == cur->right))) {
      func(cur);  //如果当前结点没有孩子结点或者孩子节点都已被访问过
      s.pop();
      pre = cur;
    } else {
      if (cur->right != NULL) s.push(cur->right);
      if (cur->left != NULL) s.push(cur->left);
    }
  }
}

void bfsIter(TreeNode* root) {
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* cur = q.front();
    q.pop();
    if (cur) {
      func(cur);
      q.push(cur->left);
      q.push(cur->right);
    }
  }
}
// 层序遍历（实际就是BFS）
void levelOrderIter(TreeNode* root) {
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int n = q.size();
    for (int i = 0; i < n; i++) {
      TreeNode* cur = q.front();
      q.pop();
      if (cur) {
        func(cur);
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    cout << endl;
  }
}
void test() {
  // string line;
  // getline(cin, line);
  // TreeNode* root = stringToTreeNode(line);
  TreeNode* root = stringToTreeNode("[1,2,3,4,5,6,7,8]");
  prettyPrintTree(root);
  cout << "前序：";
  preOrderIter(root);
  cout << endl;
  cout << "前序：";
  preOrderIter2(root);
  cout << endl;
  cout << "中序：";
  inOrderIter(root);
  cout << endl;
  cout << "后序：";
  postOrderIter(root);
  cout << endl;
  cout << "后序：";
  postOrderIter2(root);
  cout << endl;
  cout << "bfs：";
  bfsIter(root);
  cout << endl;
  cout << "层序：\n";
  levelOrderIter(root);
  cout << endl;
}
}  // namespace OrderIter