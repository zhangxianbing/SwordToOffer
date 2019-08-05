#pragma once
#include "../public.h"

//! ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ !//
//! 一遍遍历数组问题 && 多指针问题 && 滑动窗口
// 此类问题尽可能只遍历一遍数组以达到原地改变原数组
// 1.双指针之前后指针，遍历数组的指针在前，更新数组的指针在后。此方法适合情景：剔除原数组中不合要求的元素，留下符合要求的元素，如：LC26，LC27，LC283
// 2.双指针之对撞指针，LC167，LC125
// 3.三指针，遍历指针+两个对撞指针，实际是1，2的延伸，典型的如快排、归并排序的子过程操作，LC75，LC88，LC215
// 4.滑动窗口，也属于双指针，LC209

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//* 前后指针

// 26. 删除排序数组中的重复项
namespace LC26 {
int removeDuplicates(vector<int>& nums)
{
    if (nums.empty())
        return 0;
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != nums[j]) {
            nums[++j] = nums[i];
        }
    }
    return j + 1;
}
} // namespace LC26

namespace LC80 {
int removeDuplicates(vector<int>& nums)
{
    if (nums.size() <= 2)
        return nums.size();
    int index = 2;
    for (int i = 2; i < nums.size(); i++) {
        if (nums[i] != nums[index - 2])
            nums[index++] = nums[i];
    }
    return index;
}
} // namespace LC80

// 27. 移除元素
namespace LC27 {
int removeElement(vector<int>& nums, int val)
{
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[j++] = nums[i];
        }
    }

    return j;
}
} // namespace LC27

namespace LC283 {
void moveZeroes(vector<int>& nums)
{
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            if (j < i)
                nums[j] = nums[i]; // 优化1：减少不必要的赋值
            j++;
        }
    }
    for (; j < nums.size(); j++) {
        nums[j] = 0;
    }
}
} // namespace LC283

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//* 对撞指针

// 167. 两数之和 II - 输入有序数组 (对撞指针)
namespace LC167 {
vector<int> twoSum(vector<int>& nums, int target)
{
    int n = nums.size(), l = 0, r = n - 1;
    while (l < r) {
        int s = nums[l] + nums[r];
        if (s < target)
            l++;
        else if (s > target)
            r--;
        else
            break;
    }
    return { l + 1, r + 1 };
}
} // namespace LC167

// 125. 验证回文串 (对撞指针)
namespace LC125 {
bool isPalindrome(string s)
{
    int n = s.size(), l = 0, r = n - 1;
    while (l < r) {
        while (l < n && !isalnum(s[l]))
            l++;
        if (l == n)
            break;
        while (!isalnum(s[r]))
            r--;
        if ((s[l++] & 0xDF) != (s[r--] & 0xDF))
            return false;
    }
    return true;
}
} // namespace LC125

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//* 三指针

// 75. 颜色分类 （快排子过程）
namespace LC75 {
void sortColors(vector<int>& nums)
{
    int n = nums.size();
    if (n <= 1)
        return;
    int l = -1, r = n, i = 0;
    while (i < r) {
        if (nums[i] == 0)
            swap(nums[++l], nums[i++]);
        else if (nums[i] == 1)
            i++;
        else if (nums[i] == 2)
            swap(nums[--r], nums[i]);
    }
}
} // namespace LC75

// 215. 数组中的第K个最大元素 (利用快排)
namespace LC215 {
int findKthLargest(vector<int>& nums, int l, int r, int K)
{
    int i = l - 1, j = r + 1, k = l;
    int ref = nums[l];
    while (k < j) {
        if (nums[k] < ref)
            swap(nums[++i], nums[k++]);
        else if (nums[k] > ref)
            swap(nums[--j], nums[k]);
        else
            k++;
    }
    if (K <= i)
        return findKthLargest(nums, l, i, K);
    if (K >= j)
        return findKthLargest(nums, j, r, K);
    return nums[i + 1];
}
int findKthLargest(vector<int>& nums, int K)
{
    return findKthLargest(nums, 0, nums.size() - 1, nums.size() - K);
}
} // namespace LC215

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//* 滑动窗口
//! 注 LC3(2), LC159,LC340, LC76，LC438异曲同工
namespace LC3 {
// 思路1：哈希表记录每个元素最新出现的位置（序号）
int lengthOfLongestSubstring1(string s)
{
    unordered_map<char, int> m;
    int start = 0, ret = 0;
    for (int i = 0; i < s.size(); i++) {
        if (m.find(s[i]) != m.end()) {
            start = max(start, m[s[i]] + 1);
        }
        m[s[i]] = i;
        ret = max(ret, i - start + 1);
    }
    return ret;
}
// 思路2：
int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> m;
    int i = 0, j = 0, res = 0, n = 0;
    while (j < s.size()) {
        if (m[s[j++]]++ > 0)
            n++;
        while (n > 0)
            if (m[s[i++]]-- > 1)
                n--;
        res = max(res, j - i);
    }
    return res;
}
} // namespace LC3

namespace LC159 {
int lengthOfLongestSubstringTwoDistinct(string s)
{
    unordered_map<char, int> m;
    int i = 0, j = 0, res = 0, n = 0;
    while (j < s.size()) {
        if (m[s[j++]]++ == 0)
            n++;
        while (n > 2)
            if (m[s[i++]]-- == 1)
                n--;
        res = max(res, j - i);
    }
    return res;
}
} // namespace LC159

namespace LC340 {
int lengthOfLongestSubstringKDistinct(string s, int k)
{
    unordered_map<char, int> m;
    int i = 0, j = 0, res = 0, n = 0;
    while (j < s.size()) {
        if (m[s[j++]]++ == 0)
            n++;
        while (n > k)
            if (m[s[i++]]-- == 1)
                n--;
        res = max(res, j - i);
    }
    return res;
}
} // namespace LC340

namespace LC30 {

} // namespace LC30

// 76. 最小覆盖子串
namespace LC76 {
string minWindow(string s, string t)
{
    unordered_map<char, int> m;
    for (auto c : t)
        ++m[c];
    int i = 0, j = 0, n = t.size(), h = 0, d = INT32_MAX;
    while (j < s.size()) {
        if (m[s[j++]]-- > 0)
            n--;
        while (n == 0) {
            if (j - i < d)
                d = j - (h = i);
            if (m[s[i++]]++ == 0)
                n++;
        }
    }
    return d == INT32_MAX ? "" : s.substr(h, d);
}
} // namespace LC76

namespace LC159 {

} // namespace LC159

// 209. 长度最小的子数组
namespace LC209 {
int minSubArrayLen(int s, vector<int>& nums)
{
    int n = nums.size(), i = 0, j = 0, t = 0, res = INT32_MAX;
    for (; j < n; j++) {
        t += nums[j];
        while (t >= s) {
            res = min(res, j - i + 1);
            t -= nums[i++];
        }
    }
    return res == INT32_MAX ? 0 : res;
}
} // namespace LC209

namespace LC239 {

} // namespace LC239

// 438. 找到字符串中所有字母异位词
namespace LC438 {
vector<int> findAnagrams(string s, string p)
{
    vector<int> ret;
    unordered_map<char, int> m;
    for (auto c : p)
        ++m[c];
    int i = 0, j = 0, c = p.size();
    while (j < s.size()) {
        if (m[s[j++]]-- > 0)
            c--;
        while (c == 0) {
            if (j - i == p.size())
                ret.push_back(i);
            if (m[s[i++]]++ == 0)
                c++;
        }
    }
    return ret;
}
} // namespace LC438

namespace LC567 {

} // namespace LC567

namespace LC632 {

} // namespace LC632

namespace LC727 {

} // namespace LC727

//! ///////////////////////////////////////////// !//