#pragma once
#include "public.h"

namespace ST1 {
void helper(vector<string>& res, string& str, int k)
{
    if (k == int(str.size()) - 1) {
        res.push_back(str);
        return;
    }
    for (int i = k; i < int(str.size()); i++) {
        if (i == k || str[i] != str[i - 1]) {
            swap(str[k], str[i]);
            helper(res, str, k + 1);
            swap(str[k], str[i]);
        }
    }
}

vector<string> Permutation1(string str)
{
    vector<string> res;
    sort(str.begin(), str.end());
    helper(res, str, 0);
    return res;
}

vector<string> Permutation(string str)
{
    vector<string> res;
    int n = str.size();
    sort(str.begin(), str.end());

    do {
        res.push_back(str);
        int j = n - 1;
        while (j - 1 >= 0 && str[j - 1] >= str[j])
            j--; // 注意>=
        if (j == 0)
            break;
        int i = j;
        while (str[i] > str[j - 1])
            i++;
        swap(str[i - 1], str[j - 1]);
        sort(str.begin() + j, str.end());
    } while (true);
    return res;
}

void test()
{
    string str = "abc";
    auto res = Permutation(str);
    for (auto s : res)
        cout << s << endl;
}
} // namespace T1

// 归并排序求逆数堆有两个要注意的地方：1、复制数组在‘分’之后；2、res += m-i+1
namespace ST2 {
long util(vector<int>& raw, vector<int>& data, int l, int r)
{
    if (l >= r)
        return 0;
    int m = l + (r - l) / 2, i = l, j = m + 1, k = l;
    long res = 0, res_l = util(raw, data, l, m), res_r = util(raw, data, m + 1, r);
    for (int i = l; i <= r; i++)
        raw[i] = data[i]; // 注意复制在调用util之后
    while (k <= r) {
        if (j > r || i <= m && raw[i] < raw[j]) {
            data[k++] = raw[i++];
        } else {
            data[k++] = raw[j++];
            res += m - i + 1;
        }
    }
    return res + res_l + res_r;
}
int InversePairs(vector<int>& data)
{
    if (data.empty())
        return 0;
    vector<int> raw(data.size());
    return util(raw, data, 0, data.size() - 1) % 1000000007;
}
void test()
{
    vector<int> data = { 1, 2, 8, 4, 6, 5 };
    cout << InversePairs(data);
    cout << endl;
}
} // namespace T2

namespace ST3 {
int GetNumberOfK(vector<int> data, int k)
{
    if (data.empty())
        return 0;
    int l = 0, r = data.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (data[m] > k)
            r = m - 1;
        else if (data[m] < k)
            l = m + 1;
        else {
            l = m, r = m;
            while (r < data.size() && data[r] == k)
                r++;
            while (l >= 0 && data[l] == k)
                l--;
            return r - l - 1;
        }
    }
    return 0;
}
void test()
{
    vector<int> data{ 3 };
    cout << GetNumberOfK(data, 3);
}
} // namespace T3

namespace ST4 {
bool match(char* str, char* pattern)
{
    if (pattern[0] == 0 && str[0] == 0) {
        return true;
    }

    if (pattern[0] != 0 && pattern[1] == '*') {
        if (match(str, pattern + 2))
            return true;
    }

    if ((pattern[0] == '.' && str[0]) || str[0] == pattern[0]) {
        if (match(str + 1, pattern + 1))
            return true;
        if (pattern[1] == '*' && match(str + 1, pattern)) {
            return true;
        }
    }

    return false;
}
} // namespace T4

namespace ST5 {
ListNode* deleteDuplication(ListNode* head)
{
    if (!head)
        return NULL;
    ListNode* root = new ListNode(-1);
    root->next = head;
    ListNode *cur = head, *pre = root;
    while (cur) {
        prettyPrintLinkedList(root);
        if (cur->next && cur->next->val == cur->val) {
            while (cur->next && cur->next->val == cur->val) {
                cur = cur->next;
            }
            pre->next = cur->next;
            cur = cur->next;
        } else {
            pre = pre->next;
            cur = cur->next;
        }
    }
    return root->next;
}

void test()
{
    string line;
    while (getline(cin, line)) {
        ListNode* head = stringToListNode(line);
        prettyPrintLinkedList(head);
        ListNode* res = deleteDuplication(head);
        prettyPrintLinkedList(res);
    }
}
} // namespace T5
