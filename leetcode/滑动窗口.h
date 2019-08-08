
#pragma once
#include "../public.h"

//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 滑动窗口本质也是双指针
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

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

// 30. 串联所有单词的子串
namespace LC30 {
vector<int> findSubstring(string s, vector<string>& words)
{
    vector<int> res;
    unordered_map<string, int> M;
    for (auto& word : words)
        ++M[word];
    int i = 0, j = 0, m = words.size(), n = words[0].size(), c = m;
    while (j + n <= s.size()) {
        if (M[s.substr(j++, n)]-- > 0)
            c--;
        while (c == 0) {
            if (j - i == n * (m - 1))
                res.push_back(i);
            while (M[s.substr(i++, n)]++ == 0)
                c++;
        }
    }
    return res;
}
void test()
{
    string s = "barfoothefoobarman";
    vector<string> words = { "foo", "bar" };
    findSubstring(s, words);
}
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