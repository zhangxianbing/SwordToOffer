/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:43:06
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-16 16:30:23
 * @Description: file content
 */
#pragma once

//! #FF0000 FATAL
//@ #FF8C00 ERROR
//# #BBBB23 WARNING
//$ #48BB31 INFO
//% #0070BB DEBUG
//^ #19CAAD VERBOSE
//& #8A2BE2 ASSERT
//* #98C379
/// #3D9140
//+ #191970
//- #872657
//? #F0E68C NOTE
//> #FFFF00 NOTE
//< #00FF00 NOTE
//| #FFC0CB NOTE
// 推荐度：★★★★☆
// 划重点

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
 public:
  int val;
  vector<Node*> children;
  Node() {}
  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

void trimLeftTrailingSpaces(string& input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(),
                                     [](int ch) { return !isspace(ch); }));
}

void trimRightTrailingSpaces(string& input) {
  input.erase(
      find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
          .base(),
      input.end());
}

//! 其他转string
string stringToString(string input) {
  assert(input.length() >= 2);
  string result;
  for (int i = 1; i < input.length() - 1; i++) {
    char currentChar = input[i];
    if (input[i] == '\\') {
      char nextChar = input[i + 1];
      switch (nextChar) {
        case '\"':
          result.push_back('\"');
          break;
        case '/':
          result.push_back('/');
          break;
        case '\\':
          result.push_back('\\');
          break;
        case 'b':
          result.push_back('\b');
          break;
        case 'f':
          result.push_back('\f');
          break;
        case 'r':
          result.push_back('\r');
          break;
        case 'n':
          result.push_back('\n');
          break;
        case 't':
          result.push_back('\t');
          break;
        default:
          break;
      }
      i++;
    } else {
      result.push_back(currentChar);
    }
  }
  return result;
}

int stringToInteger(string input) { return stoi(input); }

vector<int> stringToIntegerVector(string input) {
  vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

ListNode* stringToListNode(string input) {
  // Generate list from the input
  vector<int> list = stringToIntegerVector(input);

  // Now convert that list into linked list
  ListNode* dummyRoot = new ListNode(0);
  ListNode* ptr = dummyRoot;
  for (int item : list) {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
  }
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

string integerVectorToString(vector<int> list, int length = -1) {
  if (length == -1) {
    length = list.size();
  }

  if (length == 0) {
    return "[]";
  }

  string result;
  for (int index = 0; index < length; index++) {
    int number = list[index];
    result += to_string(number) + ", ";
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

string listNodeToString(ListNode* node) {
  if (node == nullptr) {
    return "[]";
  }

  string result;
  while (node) {
    result += to_string(node->val) + ", ";
    node = node->next;
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

void prettyPrintLinkedList(ListNode* node) {
  while (node && node->next) {
    cout << node->val << "->";
    node = node->next;
  }

  if (node) {
    cout << node->val << endl;
  } else {
    cout << "Empty LinkedList" << endl;
  }
}

string treeNodeToString(TreeNode* root) {
  if (root == nullptr) {
    return "[]";
  }

  string output = "";
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();

    if (node == nullptr) {
      output += "null, ";
      continue;
    }

    output += to_string(node->val) + ", ";
    q.push(node->left);
    q.push(node->right);
  }
  return "[" + output.substr(0, output.length() - 2) + "]";
}

TreeNode* stringToTreeNode(string input) {
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  if (!input.size()) {
    return nullptr;
  }

  string item;
  stringstream ss;
  ss.str(input);

  getline(ss, item, ',');
  TreeNode* root = new TreeNode(stoi(item));
  queue<TreeNode*> nodeQueue;
  nodeQueue.push(root);

  while (true) {
    TreeNode* node = nodeQueue.front();
    nodeQueue.pop();

    if (!getline(ss, item, ',')) {
      break;
    }

    trimLeftTrailingSpaces(item);
    if (item != "null") {
      int leftNumber = stoi(item);
      node->left = new TreeNode(leftNumber);
      nodeQueue.push(node->left);
    }

    if (!getline(ss, item, ',')) {
      break;
    }

    trimLeftTrailingSpaces(item);
    if (item != "null") {
      int rightNumber = stoi(item);
      node->right = new TreeNode(rightNumber);
      nodeQueue.push(node->right);
    }
  }
  return root;
}

void prettyPrintTree(TreeNode* node, string prefix = "", bool isLeft = true) {
  if (node == nullptr) {
    cout << "Empty tree";
    return;
  }

  if (node->right) {
    prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
  }

  cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

  if (node->left) {
    prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
  }
}

namespace util {
void test() {
  string line;
  while (getline(cin, line)) {
    ListNode* head = stringToListNode(line);
    prettyPrintLinkedList(head);
  }
}

void test2() {
  string line;
  while (getline(cin, line)) {
    TreeNode* root = stringToTreeNode(line);
    prettyPrintTree(root);
  }
}
}  // namespace util

void split(vector<string>& vs, const string& s, const char delim = ' ') {
  string temp;
  istringstream iss(s);
  while (getline(iss, temp, delim)) {
    vs.push_back(temp);
  }
}

namespace util {
void test3() {
  vector<string> res;
  split(res, "I am a student.");
  for (auto s : res) cout << s << endl;
}
}  // namespace util
