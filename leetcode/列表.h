#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 列表
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

namespace LC206 {
ListNode* reverseList(ListNode* head)
{
    ListNode *rhead = NULL, *curr = head;
    while (curr) {
        ListNode* temp = curr->next;
        curr->next = rhead;
        rhead = curr;
        curr = temp;
    }
    return rhead;
}
} // namespace LC206

namespace LC92 {
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    ListNode *root = new ListNode(-1), *pre = root;
    root->next = head;
    for (int i = 0; i < m - 1; ++i)
        pre = pre->next;
    ListNode* cur = pre->next;
    for (int i = m; i < n; ++i) {
        ListNode* next = cur->next;
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }
    return root->next;
}
} // namespace LC92

namespace LC86 {
ListNode* partition(ListNode* head, int x)
{
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
} // namespace LC86

namespace LC2 {
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
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
} // namespace LC2

namespace LC445 {
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
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
} // namespace LC445
// namespace LC445

namespace LC203 {
ListNode* removeElements(ListNode* head, int val)
{
    ListNode* res = new ListNode(-1);
    res->next = head;
    ListNode *cur = res->next, *pre = res;
    while (cur) {
        while (cur && cur->val == val) {
            cur = cur->next;
        }
        pre->next = cur;
        pre = cur;
        if (!cur)
            break;
        cur = cur->next;
    }
    return res->next;
}
} // namespace LC203

namespace LC82 {
ListNode* deleteDuplicates1(ListNode* head)
{
    ListNode* res = new ListNode(-1);
    res->next = head;
    ListNode *cur = head, *pre = res;
    while (cur) {
        if (cur->next && cur->val == cur->next->val) {
            while (cur->next && cur->val == cur->next->val)
                cur = cur->next;
            cur = cur->next;
            pre->next = cur;
            continue;
        }
        pre = pre->next;
        cur = cur->next;
    }
    return res->next;
}
ListNode* deleteDuplicates(ListNode* head)
{
    if (!head)
        return NULL;
    ListNode *p = new ListNode(head->val - 1), *ptr = p, *pre = p;
    while (head) {
        if (pre->val != head->val && (!head->next || head->next->val != head->val)) {
            ptr->next = head;
            ptr = ptr->next;
        }
        pre = head;
        head = head->next;
    }
    ptr->next = NULL;
    return p->next;
}
} // namespace LC82

namespace LC83 {
ListNode* deleteDuplicates(ListNode* head)
{
    ListNode* res = new ListNode(-1);
    res->next = head;
    ListNode* pre = res;
    while (head) {
        while (head->next && head->val == head->next->val)
            head = head->next;
        pre = pre->next = head;
        head = head->next;
    }
    return res->next;
}
} // namespace LC83

namespace LC21 {
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
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
} // namespace LC21

namespace LC328 {
ListNode* oddEvenList(ListNode* head)
{
    if (!head)
        return head;
    ListNode *odd = head, *evenhead = head->next, *even = evenhead;
    while (even && even->next) {
        odd = odd->next = odd->next->next;
        even = even->next = even->next->next;
    }
    odd->next = evenhead;
    return head;
}
void test()
{
    string line;
    while (getline(cin, line)) {
        ListNode* head = stringToListNode(line);

        ListNode* ret = oddEvenList(head);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
}
} // namespace LC328

namespace LC24 {
ListNode* swapPairs(ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode* next = head->next;
    head->next = swapPairs(next->next);
    next->next = head;
    return next;
}
ListNode* swapPairs1(ListNode* head)
{
    // if (!head || !head->next) return head;
    // 至此head至少两个节点
    ListNode* node = new ListNode(-1);
    node->next = head;
    ListNode *cur = node, *nxt, *nnnxt;
    while (cur) {
        nxt = cur->next;
        if (!nxt || !nxt->next)
            break;
        nnnxt = cur->next->next->next;

        cur->next = nxt->next;
        nxt->next->next = nxt;
        nxt->next = nnnxt;
        cur = nxt;
    }

    return node->next;
}
} // namespace LC24

namespace LC25 {
ListNode* reverseKGroup(ListNode* head, int k)
{
    ListNode* ret = new ListNode(-1);
    ret->next = head;

    ListNode *cur = ret, *nxt, *pre = NULL, *h, *t;

    // 先获得节点总数
    int n = 0;
    while (cur = cur->next)
        n++;

    // 每k个节点翻转一次
    cur = ret;
    while (n >= k) {
        h = cur; // 记录要翻转的起始节点
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
} // namespace LC25

namespace LC147 {

} // namespace LC147

namespace LC148 {

} // namespace LC148

namespace LC237 {

} // namespace LC237

//! 双指针在链表中的使用
namespace LC19 {
ListNode* removeNthFromEnd(ListNode* head, int n)
{
    ListNode *front = head, *back = head;
    for (int i = 0; i < n; i++) // 前指针先走n步
        front = front->next;
    if (!front)
        return head->next; // 重要的边界条件！！！若前指针已经走到NULL了，说明要删除的是第一个节点
    while (front->next) {
        front = front->next;
        back = back->next;
    } // 前指针到最后一个节点，后指针停在倒数第（n+1）个节点，即要删除的节点之前
    back->next = back->next->next;
    return head;
}
} // namespace LC19

namespace LC61 {

} // namespace LC61

namespace LC143 {

} // namespace LC143

namespace LC234 {

} // namespace LC234
