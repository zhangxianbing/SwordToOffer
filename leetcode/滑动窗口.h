/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:45
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-09 11:42:45
 * @Description: file content
 */

#pragma once
#include "../public.h"

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 滑动窗口本质也是双指针
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

//! 哈希表+滑动窗口

// TODO 3.无重复字符的最长子串
namespace LC3 {
//* 思路1：哈希表记录每个元素最新出现的位置（序号）
int lengthOfLongestSubstring1(string s) {
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
//* 思路2：哈希表+滑动窗口
int lengthOfLongestSubstring(string s) {
  unordered_map<char, int> m;
  int i = 0, j = 0, res = 0, n = 0;
  while (j < s.size()) {
    if (m[s[j++]]++ > 0) n++;
    while (n > 0)
      if (m[s[i++]]-- > 1) n--;
    res = max(res, j - i);
  }
  return res;
}
}  // namespace LC3

// TODO [ 159] 至多包含两个不同字符的最长子串
namespace LC159 {
//* 思路：哈希表+滑动窗口
int lengthOfLongestSubstringTwoDistinct(string s) {
  unordered_map<char, int> m;
  int i = 0, j = 0, res = 0, n = 0;
  while (j < s.size()) {
    if (m[s[j++]]++ == 0) n++;
    while (n > 2)
      if (m[s[i++]]-- == 1) n--;
    res = max(res, j - i);
  }
  return res;
}
}  // namespace LC159

// TODO [ 340] 至多包含 K 个不同字符的最长子串
namespace LC340 {
//* 思路：哈希表+滑动窗口
int lengthOfLongestSubstringKDistinct(string s, int k) {
  unordered_map<char, int> m;
  int i = 0, j = 0, res = 0, n = 0;
  while (j < s.size()) {
    if (m[s[j++]]++ == 0) n++;
    while (n > k)
      if (m[s[i++]]-- == 1) n--;
    res = max(res, j - i);
  }
  return res;
}
}  // namespace LC340

// TODO 30. 串联所有单词的子串
namespace LC30 {
//* 思路：哈希表+滑动窗口
vector<int> findSubstring(string s, vector<string>& words) {
  vector<int> res;
  if (words.empty()) return res;
  int m = words.size(), n = words[0].size(), l = s.size();
  for (int k = 0; k < n; k++) {
    unordered_map<string, int> M;
    for (auto& word : words) ++M[word];
    int i = k, j = k, c = m;
    while (j + n <= l) {
      if (M[s.substr(j, n)]-- > 0) c--;
      j += n;
      while (c == 0) {
        if (j - i == n * m) res.push_back(i);
        if (i + n <= l && M[s.substr(i, n)]++ == 0) c++;
        i += n;
      }
    }
  }
  return res;
}
void test() {
  string s = "a";
  vector<string> words = {"a"};
  findSubstring(s, words);
}
}  // namespace LC30

// TODO 76. 最小覆盖子串 （经典题☆☆☆☆☆）
namespace LC76 {
//* 思路：哈希表+滑动窗口 模板
string minWindow(string s, string t) {
  unordered_map<char, int> m;
  for (auto c : t) ++m[c];
  int i = 0, j = 0, n = t.size(), h = 0, d = INT32_MAX;
  while (j < s.size()) {
    if (m[s[j++]]-- > 0) n--;
    while (n == 0) {
      if (j - i < d) d = j - (h = i);
      if (m[s[i++]]++ == 0) n++;
    }
  }
  return d == INT32_MAX ? "" : s.substr(h, d);
}
}  // namespace LC76

// TODO 209. 长度最小的子数组
namespace LC209 {
int minSubArrayLen(int s, vector<int>& nums) {
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
}  // namespace LC209

// TODO 239. 滑动窗口最大值
namespace LC239 {
// 一开始的思路是建立一个最大堆，麻烦！而C++STL中的priority_queue不好删除元素
// 可以考虑使用双向队列
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  vector<int> res;
  deque<int> dq;
  for (int i = 0; i < nums.size(); i++) {
    while (!dq.empty() && nums[i] > nums[dq.back()]) dq.pop_back();
    dq.push_back(i);
    while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    if (i >= k - 1) res.push_back(nums[dq.front()]);
  }
  return res;
}
}  // namespace LC239

// TODO 438. 找到字符串中所有字母异位词
namespace LC438 {
vector<int> findAnagrams(string s, string p) {
  vector<int> ret;
  unordered_map<char, int> m;
  for (auto c : p) ++m[c];
  int i = 0, j = 0, c = p.size();
  while (j < s.size()) {
    if (m[s[j++]]-- > 0) c--;
    while (c == 0) {
      if (j - i == p.size()) ret.push_back(i);
      if (m[s[i++]]++ == 0) c++;
    }
  }
  return ret;
}
}  // namespace LC438

// TODO 567. 字符串的排列
namespace LC567 {
bool checkInclusion(string s1, string s2) {
  unordered_map<char, int> m;
  for (auto& c : s1) ++m[c];
  int i = 0, j = 0, c = s1.size();
  while (j < s2.size()) {
    if (m[s2[j++]]-- > 0) c--;
    while (c == 0) {
      if (j - i == s1.size()) return true;
      if (m[s2[i++]]++ == 0) c++;
    }
  }
  return false;
}
}  // namespace LC567

// TODO 632. 最小区间
namespace LC632 {}  // namespace LC632

// TODO 727. 最小窗口子序列
namespace LC727 {}  // namespace LC727

// TODO 1100. 长度为 K 的无重复字符子串
namespace LC1100 {}  // namespace LC1100

// TODO 995. K 连续位的最小翻转次数
namespace LC995 {}  // namespace LC995

// TODO 992. K 个不同整数的子数组 (待debug)
namespace LC992 {
int subarraysWithKDistinct(vector<int>& A, int K) {
  int res = 0;
  unordered_map<int, int> m;
  int n = A.size(), i = 0, j = 0, c = 0;
  while (j < n) {
    if (m[A[j++]]++ == 0) c++;
    if (c == K) {
      res++;
      // 先右边扩张，再左边缩放
      while (j < n && m[A[j++]]++ > 0) res++;
      while (i < n && m[A[i++]]-- != 1) res++;
      c--;
    }
  }
  return res;
}
void test() {
  string line;
  vector<int> A = {1, 2, 1, 2, 3};
  int ret = subarraysWithKDistinct(A, 2);
  string out = to_string(ret);
  cout << out << endl;
}
}  // namespace LC992

// TODO 674. 最长连续递增序列
namespace LC674 {
int findLengthOfLCIS(vector<int>& nums) {
  int res = 0;
  int i = 0, j = 0, n = nums.size();
  while (j < n) {
    while (j + 1 < n && nums[j + 1] > nums[j]) j++;
    res = max(res, j - i + 1);
    j++;
    i = j;
  }
  return res;
}
}  // namespace LC674
