#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 查找表：包括map,set,unordered_map,unordered_set
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
// TODO 349. 两个数组的交集
namespace LC349 {
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
  vector<int> res;
  unordered_map<int, int> m;
  for (auto num : nums1) m[num] = 1;
  for (auto num : nums2)
    if (m[num]-- == 1) res.push_back(num);
  return res;
}
}  // namespace LC349

// TODO 350. 两个数组的交集 II
namespace LC350 {
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
  unordered_map<int, int> m;
  vector<int> res;
  for (auto num : nums1) ++m[num];
  for (auto num : nums2)
    if (m[num]-- > 0) res.push_back(num);
  return res;
}
}  // namespace LC350

// TODO 202. 快乐数
namespace LC202 {
bool isHappy(int n) {
  unordered_map<int, int> m;

  while (true) {
    int s = 0, i;
    while (n) {
      i = n % 10;
      s += i * i;
      n /= 10;
    }
    n = s;
    if (m.find(s) != m.end()) {
      if (s == 1) return true;
      return false;
    }
    m[s]++;
  }
  return false;
}
}  // namespace LC202

// TODO 205. 同构字符串
namespace LC205 {
bool isIsomorphic(string s, string t) {
  if (s.size() != t.size()) return false;
  unordered_map<char, int> m, n;
  for (int i = 0; i < s.size(); i++) {
    if (m[s[i]] != n[t[i]]) return false;
    m[s[i]] = n[t[i]] =
        i + 1;  // 注意这里不能从零开始，因为哈希表的value默认为0
  }
  return true;
}
}  // namespace LC205

// TODO 290. 单词规律
namespace LC290 {
bool wordPattern(string pattern, string str) {
  map<char, int> p2i;
  map<string, int> w2i;
  istringstream in(str);
  int i = 0, n = pattern.size();
  for (string word; in >> word; ++i) {
    if (i == n || p2i[pattern[i]] != w2i[word]) return false;
    p2i[pattern[i]] = w2i[word] = i + 1;
  }
  return i == n;
}
}  // namespace LC290

// TODO 451. 根据字符出现频率排序
namespace LC451 {
string frequencySort(string s) {
  unordered_map<char, int> m;
  for (auto c : s) ++m[c];
  sort(s.begin(), s.end(),
       [&](char a, char b) { return m[a] == m[b] ? a < b : m[a] > m[b]; });
  return s;
}
}  // namespace LC451

// TODO 1. 两数之和
namespace LC1 {
vector<int> twoSum(vector<int>& nums, int target) {
  unordered_map<int, int> m;
  for (int i = 0; i < nums.size(); i++) {
    if (m.find(target - nums[i]) != m.end()) return {m[target - nums[i]], i};
    m[nums[i]] = i;
  }
  return {};
}
}  // namespace LC1

// TODO 454. 四数相加 II
namespace LC454 {
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C,
                 vector<int>& D) {
  int res = 0;
  unordered_map<int, int> AB;
  for (auto a : A)
    for (auto b : B) ++AB[a + b];
  for (auto c : C)
    for (auto d : D)
      if (AB[-c - d]) res += AB[-c - d];
  return res;
}
}  // namespace LC454

// TODO 447. 回旋镖的数量
namespace LC447 {
int dist(vector<int>& p, vector<int>& q) {
  int dx = p[0] - q[0];
  int dy = p[1] - q[1];
  return dx * dx + dy * dy;
}
int numberOfBoomerangs(vector<vector<int>>& points) {
  int res = 0;
  for (auto& p : points) {
    unordered_map<int, int> m;
    for (auto& q : points) ++m[dist(p, q)];
    for (auto& it : m) res += it.second * (it.second - 1);
  }
  return res;
}
}  // namespace LC447

// TODO 149. 直线上最多的点数
namespace LC149 {}  // namespace LC149

// TODO 217. 存在重复元素
namespace LC217 {
bool containsDuplicate(vector<int>& nums) {
  unordered_map<int, int> m;
  for (auto num : nums)
    if (m[num]++ == 1) return true;
  return false;
}

// TODO 219. 存在重复元素 II
namespace LC219 {
// 思路1：维护一个size==k大小的set作为滑动窗口
bool containsNearbyDuplicate1(vector<int>& nums, int k) {
  if (nums.size() <= 1 || k <= 0) return false;

  unordered_set<int> record;
  for (int i = 0; i < nums.size(); i++) {
    if (record.find(nums[i]) != record.end()) return true;
    record.insert(nums[i]);
    if (record.size() == k + 1) record.erase(nums[i - k]);
  }

  return false;
}

bool containsNearbyDuplicate(vector<int>& nums, int k) {
  unordered_map<int, int> m;
  for (int i = 0; i < nums.size(); i++) {
    if (m.find(nums[i]) != m.end())
      if (i - m[nums[i]] <= k) return true;
    m[nums[i]] = i;
  }
  return false;
}
}  // namespace LC219

// TODO 220. 存在重复元素 III
namespace LC220 {
//* 思路1：类似LC219（1）
bool containsNearbyAlmostDuplicate1(vector<int>& nums, int k, int t) {
  set<long long> record;
  for (int i = 0; i < nums.size(); i++) {
    auto lb = record.lower_bound(nums[i] - t);
    if (lb != record.end() && *lb <= long(nums[i] + t)) return true;
    record.insert(nums[i]);
    if (record.size() == k + 1) record.erase(nums[i - k]);
  }
  return false;
}
//* 暴力解法
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
  if (k == 10000) return false;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j <= i + k && j < nums.size(); j++) {
      if (abs(long(nums[j]) - long(nums[i])) <= t) {
        return true;
      }
    }
  }
  return false;
}
}  // namespace LC220
}  // namespace LC217
