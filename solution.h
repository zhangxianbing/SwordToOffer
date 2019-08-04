#include "public.h"

// 各种遍历非递归写法汇总
namespace OrderIter {
void func(TreeNode* node)
{
    cout << node->val << " ";
}
// 前序遍历
void preOrderIter(TreeNode* root)
{
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        if (!node)
            continue;
        func(node);
        s.push(node->right);
        s.push(node->left);
    }
}

void preOrderIter2(TreeNode* root)
{
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
void inOrderIter(TreeNode* root)
{
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

// 后续遍历，本质是先按 根-右-左的遍历顺序遍历压入所有节点到栈，然后从栈里弹出的顺序便是左-右-根了
void postOrderIter(TreeNode* root)
{
    if (!root)
        return;
    stack<TreeNode*> s, t;
    s.push(root);
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        t.push(cur);
        if (cur->left)
            s.push(cur->left);
        if (cur->right)
            s.push(cur->right);
    }
    while (!t.empty()) {
        func(t.top());
        t.pop();
    }
}
// 要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
void postOrderIter2(TreeNode* root)
{
    stack<TreeNode*> s;
    TreeNode* cur; //当前结点
    TreeNode* pre = NULL; //前一次访问的结点
    s.push(root);
    while (!s.empty()) {
        cur = s.top();
        if ((cur->left == NULL && cur->right == NULL) || (pre != NULL && (pre == cur->left || pre == cur->right))) {
            func(cur); //如果当前结点没有孩子结点或者孩子节点都已被访问过
            s.pop();
            pre = cur;
        } else {
            if (cur->right != NULL)
                s.push(cur->right);
            if (cur->left != NULL)
                s.push(cur->left);
        }
    }
}

void bfsIter(TreeNode* root)
{
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
void levelOrderIter(TreeNode* root)
{
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
void test()
{
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
}

namespace T1 {
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
namespace T2 {
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

namespace T3 {
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

namespace T4 {
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

namespace T5 {
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
