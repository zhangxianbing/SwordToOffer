/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:46
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-12 21:05:57
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 链表
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

// LC206. 反转链表
namespace LC206 {
ListNode* reverseList(ListNode* head) {
  ListNode *rhead = NULL, *curr = head;
  while (curr) {
    ListNode* temp = curr->next;
    curr->next = rhead;
    rhead = curr;
    curr = temp;
  }
  return rhead;
}
}  // namespace LC206

// LC92. 反转链表 II
namespace LC92 {
ListNode* reverseBetween(ListNode* head, int m, int n) {
  ListNode *root = new ListNode(-1), *pre = root;
  root->next = head;
  for (int i = 0; i < m - 1; ++i) pre = pre->next;
  ListNode* cur = pre->next;
  for (int i = m; i < n; ++i) {
    ListNode* next = cur->next;
    cur->next = next->next;
    next->next = pre->next;
    pre->next = next;
  }
  return root->next;
}
}  // namespace LC92

// LC86. 分隔链表
namespace LC86 {
ListNode* partition(ListNode* head, int x) {
  ListNode node1(0), node2(0);
  ListNode *p1 = &node1, *p2 = &node2;
  while (head) {
    if (head->val < x)
      p1 = p1->next = head;
    else
      p2 = p2->next = head;
    head = head->next;
  }
  p2->next = NULL;
  p1->next = node2.next;
  return node1.next;
}
}  // namespace LC86

// LC2. 两数相加
namespace LC2 {
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  ListNode *ret = new ListNode(-1), *cur = ret;
  int carry = 0;
  while (l1 || l2 || carry) {
    int s = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
    carry = s / 10;
    cur = cur->next = new ListNode(s % 10);
    l1 = l1 ? l1->next : l1;
    l2 = l2 ? l2->next : l2;
  }
  return ret->next;
}
}  // namespace LC2

// LC445. 两数相加 II
namespace LC445 {
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  stack<int> s1, s2;
  while (l1) {
    s1.push(l1->val);
    l1 = l1->next;
  }
  while (l2) {
    s2.push(l2->val);
    l2 = l2->next;
  }
  int c = 0;
  ListNode *res, *pre = NULL;
  while (!s1.empty() || !s2.empty() || c) {
    int s = c;
    if (!s1.empty()) {
      s += s1.top();
      s1.pop();
    }
    if (!s2.empty()) {
      s += s2.top();
      s2.pop();
    }
    c = s / 10;
    res = new ListNode(s % 10);
    res->next = pre;
    pre = res;
  }
  return res;
}
}  // namespace LC445
// namespace LC445

// LC203. 移除链表元素
namespace LC203 {
ListNode* removeElements(ListNode* head, int val) {
  ListNode* res = new ListNode(-1);
  res->next = head;
  ListNode *cur = res->next, *pre = res;
  while (cur) {
    while (cur && cur->val == val) {
      cur = cur->next;
    }
    pre->next = cur;
    pre = cur;
    if (!cur) break;
    cur = cur->next;
  }
  return res->next;
}
}  // namespace LC203

// LC83. 删除排序链表中的重复元素
namespace LC83 {
ListNode* deleteDuplicates(ListNode* head) {
  ListNode* res = new ListNode(-1);
  res->next = head;
  ListNode* pre = res;
  while (head) {
    while (head->next && head->val == head->next->val) head = head->next;
    pre = pre->next = head;
    head = head->next;
  }
  return res->next;
}
}  // namespace LC83

// LC82. 删除排序链表中的重复元素 II
namespace LC82 {
ListNode* deleteDuplicates1(ListNode* head) {
  ListNode* res = new ListNode(-1);
  res->next = head;
  ListNode *cur = head, *pre = res;
  while (cur) {
    if (cur->next && cur->val == cur->next->val) {
      while (cur->next && cur->val == cur->next->val) cur = cur->next;
      cur = cur->next;
      pre->next = cur;
      continue;
    }
    pre = pre->next;
    cur = cur->next;
  }
  return res->next;
}
ListNode* deleteDuplicates(ListNode* head) {
  if (!head) return NULL;
  ListNode *p = new ListNode(head->val - 1), *ptr = p, *pre = p;
  while (head) {
    if (pre->val != head->val &&
        (!head->next || head->next->val != head->val)) {
      ptr->next = head;
      ptr = ptr->next;
    }
    pre = head;
    head = head->next;
  }
  ptr->next = NULL;
  return p->next;
}
}  // namespace LC82

// LC21. 合并两个有序链表
namespace LC21 {
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  ListNode *ret = new ListNode(-1), *cur = ret;
  while (l1 || l2) {
    if (!l2 || l1 && l1->val < l2->val) {
      cur->next = l1;
      l1 = l1->next;
    } else {
      cur->next = l2;
      l2 = l2->next;
    }
    cur = cur->next;
  }
  return ret->next;
}
}  // namespace LC21

// LC328. 奇偶链表
namespace LC328 {
ListNode* oddEvenList(ListNode* head) {
  if (!head) return head;
  ListNode *odd = head, *evenhead = head->next, *even = evenhead;
  while (even && even->next) {
    odd = odd->next = odd->next->next;
    even = even->next = even->next->next;
  }
  odd->next = evenhead;
  return head;
}
void test() {
  string line;
  while (getline(cin, line)) {
    ListNode* head = stringToListNode(line);

    ListNode* ret = oddEvenList(head);

    string out = listNodeToString(ret);
    cout << out << endl;
  }
}
}  // namespace LC328

// LC24. 两两交换链表中的节点
namespace LC24 {
ListNode* swapPairs(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return head;

  ListNode* next = head->next;
  head->next = swapPairs(next->next);
  next->next = head;
  return next;
}
ListNode* swapPairs1(ListNode* head) {
  // if (!head || !head->next) return head;
  // 至此head至少两个节点
  ListNode* node = new ListNode(-1);
  node->next = head;
  ListNode *cur = node, *nxt, *nnnxt;
  while (cur) {
    nxt = cur->next;
    if (!nxt || !nxt->next) break;
    nnnxt = cur->next->next->next;

    cur->next = nxt->next;
    nxt->next->next = nxt;
    nxt->next = nnnxt;
    cur = nxt;
  }

  return node->next;
}
}  // namespace LC24

// LC25. K 个一组翻转链表
namespace LC25 {
ListNode* reverseKGroup(ListNode* head, int k) {
  ListNode* ret = new ListNode(-1);
  ret->next = head;

  ListNode *cur = ret, *nxt, *pre = NULL, *h, *t;

  // 先获得节点总数
  int n = 0;
  while (cur = cur->next) n++;

  // 每k个节点翻转一次
  cur = ret;
  while (n >= k) {
    h = cur;  // 记录要翻转的起始节点
    t = cur->next;
    cur = cur->next;
    for (int i = 0; i < k; i++) {
      nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    h->next = pre;
    t->next = cur;
    n -= k;
    cur = t;
  }

  return ret->next;
}
}  // namespace LC25

// LC19. 删除链表的倒数第N个节点
namespace LC19 {
//* 思路：前后指针
ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode *front = head, *back = head;
  for (int i = 0; i < n; i++)  // 前指针先走n步
    front = front->next;
  if (!front)
    return head
        ->next;  // 重要的边界条件！！！若前指针已经走到NULL了，说明要删除的是第一个节点
  while (front->next) {
    front = front->next;
    back = back->next;
  }  // 前指针到最后一个节点，后指针停在倒数第（n+1）个节点，即要删除的节点之前
  back->next = back->next->next;
  return head;
}
}  // namespace LC19

// LC23. 合并K个排序链表
namespace LC23 {}  // namespace LC23

// LC148. 排序链表
namespace LC148 {}  // namespace LC148

// LC237. 删除链表中的节点
namespace LC237 {}  // namespace LC237

// LC143. 重排链表
namespace LC143 {}  // namespace LC143

// LC109. 有序链表转换二叉搜索树
namespace LC109 {}  // namespace LC109

// LC141. 环形链表
namespace LC141 {}  // namespace LC141

// LC234. 回文链表
namespace LC234 {}  // namespace LC234

// LC138. 复制带随机指针的链表
namespace LC138 {}  // namespace LC138

// LC147. 对链表进行插入排序
namespace LC147 {}  // namespace LC147

// LC876. 链表的中间结点
namespace LC876 {}  // namespace LC876

// LC426. 将二叉搜索树转化为排序的双向链表
namespace LC426 {}  // namespace LC426

// LC160. 相交链表
namespace LC160 {}  // namespace LC160

// LC61. 旋转链表
namespace LC61 {}  // namespace LC61

// LC142. 环形链表 II
namespace LC142 {}  // namespace LC142

// LC1019. 链表中的下一个更大节点
namespace LC1019 {}  // namespace LC1019

// LC725. 分隔链表
namespace LC725 {}  // namespace LC725

// LC379. 电话目录管理系统
namespace LC379 {}  // namespace LC379

// LC430. 扁平化多级双向链表
namespace LC430 {}  // namespace LC430

// LC817. 链表组件
namespace LC817 {}  // namespace LC817

// LC708. 循环有序列表的插入
namespace LC708 {}  // namespace LC708

// LC707. 设计链表
namespace LC707 {}  // namespace LC707

// LC369. 给单链表加一
namespace LC369 {}  // namespace LC369
