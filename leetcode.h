#include "public.h"
// 81 merge-SortArray
namespace LC81 {
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (k >= 0)
        nums1[k--] = (i >= 0 && nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];
}
void test()
{
    vector<int> nums1{ 1, 2, 3, 0, 0, 0 };
    vector<int> nums2{ 2, 5, 6 };
    merge(nums1, 3, nums2, 3);
    for (int n : nums1) {
        cout << n << " ";
    }
    cout << endl;
    cin.get();
}
} // namespace mergeSortArray

// 283-moveZeros
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
} // namespace moveZeros

// 215-Kth Largest Element in an Array
namespace LC251 {
void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
int findKthLargest(vector<int>& nums, int l, int r, int k)
{ // kth in [l,r]
    if (l >= r)
        return nums[l];

    int ref = nums[l];
    int lg = l, rg = r + 1, i = l + 1;
    for (; i < rg; i++) {
        if (nums[i] > ref) {
            swap(nums[i], nums[++lg]);
        }
        if (nums[i] < ref) {
            swap(nums[i], nums[--rg]);
            i--;
        }
    }
    swap(nums[l], nums[lg--]);

    if (k <= lg) // 注意！！！：这里用<=,主要是防止下面[l,lg] 越界
        return findKthLargest(nums, l, lg, k);
    if (k >= rg)
        return findKthLargest(nums, rg, r, k);
    return nums[lg + 1];
}
int findKthLargest(vector<int>& nums, int k)
{
    return findKthLargest(nums, 0, nums.size() - 1, k - 1);
}

// 此做法相比上面的快排要稍微快些
int quickSelect2(vector<int>& nums, int start, int end, int k)
{
    if (start == end) {
        return nums[start];
    }
    int left = start;
    int right = end;
    int pivot = nums[(left + right) / 2];
    while (left <= right) {
        while (left <= right && nums[left] > pivot) {
            left++;
        }
        while (left <= right && nums[right] < pivot) {
            right--;
        }
        if (left <= right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }

    if (k <= right) {
        return quickSelect2(nums, start, right, k);
    }
    if (k >= left) {
        return quickSelect2(nums, left, end, k);
    }
    return nums[k];
}
int findKthLargest2(vector<int>& nums, int k)
{
    if (k <= 0) {
        return -1;
    }
    return quickSelect2(nums, 0, nums.size() - 1, k - 1);
}
void test()
{
    vector<int> nums{ 3, 2, 1, 5, 6, 4 };
    int ret = findKthLargest(nums, 2);
    cout << ret << endl;
}

} // namespace KthLargestElement

// 167. Two Sum II - Input array is sorted
namespace LC167 {
vector<int> twoSum(vector<int>& numbers, int target)
{
    int n = numbers.size();
    int l = 0, r = n - 1;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target)
            return vector<int>{ l + 1, r + 1 };
        if (sum > target) {
            r--;
        } else {
            l++;
        }
    }
    return vector<int>{};
}

void test()
{
    vector<int> nums{ 12, 13, 23, 28, 43, 44, 59, 60, 61, 68, 70, 86, 88, 92, 124, 125, 136, 168, 173, 173, 180, 199, 212, 221, 227, 230, 277, 282, 306, 314, 316, 321, 325, 328, 336, 337, 363, 365, 368, 370, 370, 371, 375, 384, 387, 394, 400, 404, 414, 422, 422, 427, 430, 435, 457, 493, 506, 527, 531, 538, 541, 546, 568, 583, 585, 587, 650, 652, 677, 691, 730, 737, 740, 751, 755, 764, 778, 783, 785, 789, 794, 803, 809, 815, 847, 858, 863, 863, 874, 887, 896, 916, 920, 926, 927, 930, 933, 957, 981, 997 };
    vector<int> ret = twoSum(nums, 542);
    cout << ret[0] << " " << ret[1] << endl;
}

} // namespace LCwoSumII

// 125. Valid Palindrome
namespace LC125 {
bool isPalindrome(string s)
{

    for (int l = 0, r = s.size() - 1; l < r;) {
        while (!isalnum(s[l++])) {
            if (l > r)
                return true;
        }
        while (!isalnum(s[r--]))
            ;
        if (toupper(s[l - 1]) != toupper(s[r + 1]))
            return false;
    }
    return true;
}

void test()
{
    string s = "A man, a plan, a canal: Panama";
    cout << isPalindrome(s) << endl;
}
} // namespace ValidPalindrome

// 344. Reverse String
namespace LC344 {
void reverseString(vector<char>& s)
{
    for (int l = 0, r = s.size() - 1; l < r; l++, r--) {
        char temp = s[l];
        s[l] = s[r];
        s[r] = temp;
    }
}
} // namespace ReverseString

// 345. Reverse Vowels of a String
namespace LC345 {
bool isVowels(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
        || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
string reverseVowels(string s)
{
    for (int l = 0, r = s.size() - 1; l < r;) {
        if (!isVowels(s[l])) {
            l++;
            if (l >= r)
                break;
        } else if (!isVowels(s[r]))
            r--;
        else {
            char temp = s[l];
            s[l] = s[r];
            s[r] = temp;
            l++;
            r--;
        }
    }
    return s;
}
void test()
{
    string s = "hello";
    cout << reverseVowels(s) << endl;
}
} // namespace ReverseVowels

// 209. Minimum Size Subarray Sum
namespace LC209 {
int minSubArrayLen(int s, vector<int>& nums)
{
    int ret = INT16_MAX;
    for (int r = 0; r < nums.size(); r++) {
        int sum = 0;
        for (int l = r; l >= 0; l--) {
            sum += nums[l];
            if (sum >= s || ret > r - l + 1) {
                ret = r - l + 1;
                break;
            }
        }
    }
    return (ret != INT16_MAX) ? ret : 0;
}
int minSubArrayLen2(int s, vector<int>& nums)
{
    int l = 0, r = -1, sum = 0, ret = INT16_MAX;
    while (l < nums.size()) {
        if (r + 1 < nums.size() && sum < s)
            sum += nums[++r];
        else
            sum -= nums[l++];
        if (sum >= s)
            ret = min(ret, r - l + 1);
    }
    return (ret != INT16_MAX) ? ret : 0;
}
} // namespace MinimumSizeSubarraySum

// 3. Longest Substring Without Repeating Characters
namespace LC3 {
int lengthOfLongestSubstring2(string s)
{
    int l = 0, r = -1, len = 0; // 思考这r=-1：因为一开始窗口里不能有元素！
    while (l < s.size()) { //思考这为什么不能用r:因为r到边界后还得等l靠过来！
        if (r + 1 < s.size() && s.substr(l, r - l + 1).find(s[r + 1]) == string::npos) {
            r++;
            len = max(len, r - l + 1);
        } else {
            l++;
        }
    }
    return len;
}

// 改用hash表，查找字符串中是否存在某个字符复杂度降为O(1)!
int lengthOfLongestSubstring3(string s)
{
    unordered_map<char, int> str_win;
    int l = 0, r = 0, len = 0; // 窗口为[l,r)
    while (l < s.size()) {
        if (r < s.size() && str_win.find(s[r]) == str_win.end()) {
            str_win.insert(make_pair(s[r], 0));
            r++;
            len = max(len, r - l);

        } else {
            str_win.erase(s[l]);
            l++;
        }
    }
    return len;
}
// 可进一步改进：（PS:在leetcode上提示Runtime Error！）
int lengthOfLongestSubstring4(string s)
{
    unordered_map<char, int> str_win;
    int l = 0, r = 0, len = 0; // 窗口为[l,r)
    for (; r < s.size() && l < s.size(); r++) {
        auto search = str_win.find(s[r]);
        if (search == str_win.end()) {
            len = max(len, r - l + 1);
        } else {
            for (; l < search->second; l++) {
                str_win.erase(s[l]);
            }
            l++;
        }
        str_win.insert(make_pair(s[r], r));
    }
    return len;
}

int lengthOfLongestSubstring5(string s)
{
    int l = 0, r = 0, len = 0; // 窗口为[l,r)

    while (r < s.size()) {
        size_t pos = s.substr(l, r - l).find(s[r]);
        if (pos == string::npos) {
            r++;
            len = max(len, r - l);
        } else {
            l = pos + l + 1;
        }
    }
    return len;
}

// 思路其实和上述方法差不多，但上述的string切片操作substr太费时间了
int lengthOfLongestSubstring(string s)
{
    int len = 0;
    string str_win;
    for (auto ch : s) {
        auto pos = str_win.find_first_of(ch);
        if (pos != string::npos) {
            str_win.erase(0, pos + 1);
        }
        str_win.push_back(ch);
        if (str_win.size() > len) {
            len = str_win.size();
        }
    }

    return len;
}

void test()
{
    string s("");
    cout << lengthOfLongestSubstring(s) << endl;
    s = " ";
    cout << lengthOfLongestSubstring(s) << endl;
    s = "abcabcbb";
    cout << lengthOfLongestSubstring(s) << endl;
    s = "bbbbb";
    cout << lengthOfLongestSubstring(s) << endl;
    s = "pwwkew";
    cout << lengthOfLongestSubstring(s) << endl;
}
} // namespace LC3

namespace LC1 {
vector<int> twoSum2(vector<int>& nums, int target)
{
    for (int i = 0; i < nums.size() - 1; i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target)
                return vector<int>{ i, j };
        }
    }
    return vector<int>{};
}

// 内层循环采用更高效的find
vector<int> twoSum3(vector<int>& nums, int target)
{
    for (int i = 0; i < nums.size() - 1; i++) {
        auto j = find(nums.begin() + i + 1, nums.end(), target - nums[i]);
        if (j != nums.end())
            return vector<int>{ i, int(distance(nums.begin(), j)) };
    }
    return vector<int>{};
}

// 内层循环采用更高效的哈希map
vector<int> twoSum(vector<int>& nums, int target)
{
    unordered_map<int, int> hash_map;
    for (int i = 0; i < nums.size(); i++) {
        if (hash_map.find(target - nums[i]) != hash_map.end())
            return vector<int>{ hash_map[target - nums[i]], i }; //hash_map[target - nums[i]]比j->second快！
        hash_map[nums[i]] = i;
    }
    return vector<int>{};
}

void test()
{
    vector<int> nums{ 3, 2, 4 };
    vector<int> ans = twoSum(nums, 6);
    cout << ans[0] << " " << ans[1] << endl;
    nums = { 2, 7, 11, 15 };
    ans = twoSum(nums, 9);
    cout << ans[0] << " " << ans[1] << endl;
}
} // namespace LC1

namespace LC4 {
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int m = nums1.size(), n = nums2.size(), mid1, mid2;
    mid1 = (m + n + 1) / 2;
    if ((m + n) % 2 == 0) {
        mid2 = mid1 + 1;
    } else {
        mid2 = mid1;
    }
    vector<int> nums(m + n);
    for (int i = 0, j = 0, k = 0; k < nums.size(); k++) {
        nums[k] = (j >= n || i < m && nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
    }
    return (nums[mid1 - 1] + nums[mid2 - 1]) / 2.0;
}

void test()
{
    vector<int> nums1{ 1, 3 }, nums2{ 2 };
    cout << findMedianSortedArrays(nums1, nums2) << endl;
}
} // namespace LC4

namespace LC15 {
vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> ret;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back() < 0 || nums.front() > 0)
        return {};
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        for (int j = i + 1, k = nums.size() - 1; j < k;) {
            if (nums[j] + nums[k] > -nums[i]) {
                k--;
            } else if (nums[j] + nums[k] < -nums[i]) {
                j++;
            } else {
                ret.push_back({ nums[i], nums[j], nums[k] }); //注意leetcode中不支持vector<int>{1,2,3}这种写法（至少在这个地方。。。）
                while (j < k && nums[j] == nums[j + 1])
                    j++;
                while (j < k && nums[k] == nums[k - 1])
                    k--;
                j++;
                k--;
            }
        }
    }

    return ret;
}
void test()
{
    vector<int> nums{ -1, 0, 1, 2, -1, -4 };
    threeSum(nums);
}
} // namespace LC15

namespace LC16 {
int threeSumClosest(vector<int>& nums, int target)
{
    sort(nums.begin(), nums.end());

    int del = INT32_MAX, i, j, k;
    for (i = 0; i < nums.size() - 2; i++) {
        j = i + 1;
        k = nums.size() - 1;
        while (j < k) { //! 双指针
            int temp = nums[i] + nums[j] + nums[k] - target;
            if (temp == 0)
                return target; //! 加上这句将节省很多时间！
            del = abs(del) < abs(temp) ? del : temp;
            if (temp < 0) {
                j++;
            } else {
                k--;
            }
        }
    }
    return del + target;
}

void test()
{
    vector<int> nums{ 1, 2, 4, 8, 16, 32, 64, 128 };
    cout << threeSumClosest(nums, 82) << endl;
}
} // namespace LC16

namespace LC18 {
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    vector<vector<int>> ret;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    if (n < 4 || nums.front() > 0 || nums.back() < 0)
        return {};
    for (int ia = 0; ia < n - 3; ia++) {
        if (ia - 1 >= 0 && nums[ia] == nums[ia - 1])
            continue;
        if (nums[ia] + nums[ia + 1] + nums[ia + 2] + nums[ia + 3] > target)
            break;
        if (nums[ia] + nums[n - 1] + nums[n - 2] + nums[n - 3] < target)
            continue;
        for (int ib = ia + 1; ib < n - 2; ib++) {
            if (ib - 1 >= ia + 1 && nums[ib] == nums[ib - 1])
                continue;
            if (nums[ia] + nums[ib] + nums[ib + 1] + nums[ib + 2] > target)
                break;
            if (nums[ia] + nums[ib] + nums[n - 1] + nums[n - 2] < target)
                continue;
            int ic = ib + 1;
            int id = n - 1;
            while (ic < id) {
                int sum = nums[ia] + nums[ib] + nums[ic] + nums[id];
                if (sum < target) {
                    ic++;
                } else if (sum > target) {
                    id--;
                } else {
                    ret.push_back({ nums[ia], nums[ib], nums[ic], nums[id] });

                    //! 注意do...while和while的区别，do...while至少会执行一次，while可能一次都不执行
                    do {
                        ic++;
                    } while (nums[ic] == nums[ic - 1] && ic < id);
                    do {
                        id--;
                    } while (nums[id] == nums[id + 1] && ic < id);

                    //! 下面的写法在leetcode上会报错！因为两个while有可能访问到数组外
                    //!（虽然所有实际测试用例测了都没问题，但这是clang检查出来的风险。。。）
                    // while (nums[ic + 1] == nums[ic])
                    //     ic++;
                    // ic++;
                    // while (nums[id - 1] == nums[id])
                    //     id--;
                    // id--;
                }
            }
        }
    }
    return ret;
}
void test()
{
    vector<int> nums{ 0, 0, 0, 0 };
    fourSum(nums, 0);
}
} // namespace LC18

namespace LC31 {
void nextPermutation(vector<int>& nums)
{
    int n = nums.size();
    if (n <= 1)
        return;
    int i = n - 1;
    while (i - 1 >= 0 && nums[i - 1] >= nums[i]) {
        i--;
    }
    reverse(nums.begin() + i, nums.end());
    if (i == 0)
        return;
    // nums[i-1]与nums中[i,n-1]大于nums[i-1]且最接近的数交换
    int j = n - 1;
    while (j >= i && nums[i - 1] < nums[j]) {
        j--;
    }
    // 注意若nums[i,n-1]中全等于nums[i-1]，则不会进入此循环，则下面j+1会越界
    j = min(j + 1, n - 1);
    swap(nums[i - 1], nums[j]);
}
void test()
{
    vector<int> nums{ 5, 1, 1 };
    while (1) {
        nextPermutation(nums);
    }
}
} // namespace LC31

namespace LC33 {

int search(vector<int>& nums, int target)
{
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (nums[m] == target)
            return m;
        if (nums[0] <= nums[m]) {
            if (nums[0] <= target && target < nums[m])
                r = m - 1;
            else
                l = m + 1;
        } else {
            if (nums[m] < target && target < nums[0])
                l = m + 1;
            else
                r = m - 1;
        }
    }
    return -1;
}
void test()
{
    vector<int> nums{ 4, 5, 6, 7, 0, 1, 2 };
    cout << search(nums, 0) << endl;
}
} // namespace LC33
namespace LC34 {
vector<int> searchRange(vector<int>& nums, int target)
{
    if (nums.empty() || target < nums.front() || target > nums.back())
        return { -1, -1 };
    vector<int> ret;
    int l = 0, r = nums.size() - 1, m;
    // 二分法更新l和r
    while (l <= r) {
        m = l + (r - l) / 2;
        if (nums[m] > target) {
            r = m - 1;
        } else if (nums[m] < target) {
            l = m + 1;
        } else {
            // 确定范围[l,m]、[m,r]
            int lr = m, rl = m;
            while (l <= lr) {
                m = l + (lr - l) / 2;
                if (nums[m] < target) {
                    l = m + 1;
                } else {
                    if (m == 0 || (m >= 1 && nums[m - 1] < nums[m])) {
                        ret.push_back(m);
                        break;
                    } else
                        lr = m - 1;
                }
            }
            while (rl <= r) {
                m = rl + (r - rl) / 2;
                if (nums[m] > target) {
                    r = m - 1;
                } else {
                    if (m == nums.size() - 1 || (m < nums.size() && nums[m] < nums[m + 1])) {
                        ret.push_back(m);
                        break;
                    } else
                        rl = m + 1;
                }
            }
            break;
        }
    }
    if (l > r)
        return { -1, -1 };
    return ret;
}
void test()
{
    vector<int> nums{};
    vector<int> ret = searchRange(nums, 6);
    cout << ret[0] << " " << ret[1] << endl;
}
} // namespace LC34
namespace LC35 {
int searchInsert(vector<int>& nums, int target)
{
    if (nums.empty() || nums[0] >= target)
        return 0;
    if (nums.back() < target)
        return nums.size();

    int l = 0, r = nums.size() - 1, m;

    while (l < r) {
        m = l + (r - l) / 2;
        if (nums[m] > target) {
            r = m; // target位于(l,r)区间
        } else if (nums[m] < target) {
            l = m + 1; // target位于(l-1,r)区间
        } else
            return m;
    }
    // 此时target应位于 (nums[l],nums[r])之间
    return l;
}
void test()
{
    vector<int> nums{ 1, 4, 5, 6 };
    cout << searchInsert(nums, 3) << endl;
}
} // namespace LC35

namespace LC39 {
//  要求列举所有情况，或者说所有情况都要探讨一下，一般可以考虑回溯法
void dfs(int index, int sum, vector<vector<int>>& ret, vector<int>& ans, vector<int>& candidates, int target)
{ // 深度优先搜索
    if (index >= candidates.size())
        return;
    if (sum == target)
        ret.push_back(ans);
    for (int i = index; i < candidates.size(); i++) {
        if (i == index && (candidates[i] > 0 && sum > target || candidates[i] < 0 && sum < target))
            return;
        ans.push_back(candidates[i]);
        dfs(i, sum + candidates[i], ret, ans, candidates, target);
        ans.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    vector<vector<int>> ret;
    vector<int> ans;

    dfs(0, 0, ret, ans, candidates, target);

    return ret;
}

// 优化改进
void dfs2(int next, int vacancy, vector<vector<int>>& ret, vector<int>& ans, vector<int>& candidates)
{
    // 如果当前空缺(vacancy = target - 当前ans数组之和)为0，则说明找到一组符合要求的ans，终止探索
    if (vacancy == 0) {
        ret.push_back(ans);
        return;
    }
    //如果元素遍历到尽头或当前元素比当前“空缺”大，则终止探索
    if (next == candidates.size() || vacancy - candidates[next] < 0)
        return;
    // 否则，将当前元素压如ans
    ans.push_back(candidates[next]);
    // 更新空缺，进一步尝试添加当前元素
    dfs2(next, vacancy - candidates[next], ret, ans, candidates);
    // 当前元素已经充分考虑了，或满足了要求，或略低于target，这时需要回退刚刚压入的元素，尝试添加下一个元素
    ans.pop_back();
    dfs2(next + 1, vacancy, ret, ans, candidates);
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    vector<vector<int>> ret;
    vector<int> ans;
    sort(candidates.begin(), candidates.end());
    dfs2(0, target, ret, ans, candidates);
    return ret;
}
void test()
{
    vector<int> candidates{ 2, 3, 5 };
    combinationSum2(candidates, 8);
}
} // namespace LC39
namespace LC40 {
void dfs(int next, int vacancy, vector<vector<int>>& ret, vector<int>& ans, vector<int>& candidates)
{

    if (vacancy == 0) {
        ret.push_back(ans);
        return;
    }
    if (next == candidates.size() || vacancy < candidates[next]) {
        return;
    }

    ans.push_back(candidates[next]);
    dfs(next + 1, vacancy - candidates[next], ret, ans, candidates);
    ans.pop_back();
    // 应该在这处理重复数字！
    // 对于重复了前面的数字，选择忽略
    while (next + 1 < candidates.size() && candidates[next + 1] == candidates[next]) { // 后一个存在且后一个与当前元素相同，考虑下一个
        next++;
    } // 此时next应为最后一个或重复数字中的最后一个
    dfs(next + 1, vacancy, ret, ans, candidates);
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    vector<vector<int>> ret;
    vector<int> ans;
    sort(candidates.begin(), candidates.end());
    dfs(0, target, ret, ans, candidates);
    return ret;
}
void test()
{
    vector<int> candidates{ 1, 1, 2, 2 };
    combinationSum2(candidates, 3);
}
} // namespace LC40
namespace LC41 {
int firstMissingPositive(vector<int>& nums)
{
    for (int i = 0; i < nums.size(); i++) {
        // 不处理非负数
        if (nums[i] <= 0)
            continue;
        // 在符合条件：值为[1,n]之间且不处在正确位置(nums[i]!=i+1)的元素间循环
        int index = nums[i] - 1;
        while (index >= 0 && index < nums.size() && index + 1 != nums[index]) {
            // 下一个要访问的序号
            int next_index = nums[index] - 1;
            // 对当前访问的序号“归位”
            nums[index] = index + 1;
            if (nums[index] <= 0)
                break;
            index = next_index;
        }
    }
    //! 总结：这里实际用到了1~n无序数组的O(n)排序方法的思想：
    //! 设原数组为a,排好序的数组为b，则两者关系为b[a[i]-1]=a[i]
    for (int i = 0; i < nums.size(); i++) {
        if (i + 1 != nums[i])
            return i + 1;
    }
    return nums.size() + 1;
}
void test()
{
    vector<int> nums{ 1, 2, 4, 4, 5, 8, 7, 5 };
    cout << firstMissingPositive(nums);
}
} // namespace LC41

namespace LC268 {
int missingNumber2(vector<int>& nums)
{
    int n = nums.size();
    vector<int> flgs(n + 1, 0);
    for (int i = 0; i < n; i++) {
        flgs[nums[i]] = 1;
    }
    for (int i = 0; i < n + 1; i++) {
        if (flgs[i] == 0)
            return i;
    }
    return -1;
}
int missingNumber3(vector<int>& nums)
{
    int mis = nums.size();
    for (int i = 0; i < nums.size(); i++) {
        mis ^= i ^ nums[i];
    }
    return mis;
}
int missingNumber(vector<int>& nums)
{
    int n = nums.size();
    return (n + 1) * n / 2 - accumulate(nums.begin(), nums.end(), 0);
}
void test()
{
    vector<int> nums{ 0 };
    cout << missingNumber(nums);
}
} // namespace LC268

namespace LC141 {
bool hasCycle(ListNode* head)
{
    if (head == NULL || head->next == NULL)
        return false;
    ListNode* slow = head;
    ListNode* fast = head;

    // 采用do...while()结果可能会更清晰
    do {
        slow = slow->next;
        fast = fast->next;
        if (fast == NULL)
            return false;
        fast = fast->next;
        if (fast == NULL)
            return false;
    } while (slow != fast);
    return true;
}

// 上述写法不太直观,且容易出错
bool hasCycle1(ListNode* head)
{
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

void test()
{
    vector<ListNode*> nodes;
    for (int i = 0; i < 3; i++) {
        nodes.push_back(new ListNode(i));
    }
    for (int i = 0; i + 1 < 3; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    cout << hasCycle(nodes[0]);
}
} // namespace LC141

namespace LC142 {
ListNode* detectCycle1(ListNode* head)
{

    ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            break;
    }
    if (!fast || !fast->next)
        return NULL;

    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}
// 改进
ListNode* detectCycle(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    do {
        if (slow && slow->next)
            slow = slow->next;
        else
            return NULL;

        if (fast && fast->next && fast->next->next)
            fast = fast->next->next;
        else
            return NULL;
    } while (slow != fast);
    fast = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
void test()
{
    vector<ListNode*> nodes;
    int n = 4, l = 2;
    for (int i = 0; i < n; i++) {
        nodes.push_back(new ListNode(i));
    }
    for (int i = 0; i + 1 < n; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[n - 1]->next = nodes[l];
    ListNode* ret = detectCycle(nodes[0]);
}
} // namespace nameT142

namespace LC287 {
int findDuplicate(vector<int>& nums)
{
    int slow = nums[0], fast = nums[0];
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    fast = nums[0];
    while (fast != slow) {
        fast = nums[fast];
        slow = nums[slow];
    }
    return slow;
}
void test()
{
    vector<int> nums{ 3, 1, 3, 4, 2 };
    cout << findDuplicate(nums);
}
} // namespace LC287

namespace LC448 {
vector<int> findDisappearedNumbers1(vector<int>& nums)
{
    vector<int> ret;
    for (auto& n : nums) {
        if (nums[abs(n) - 1] > 0)
            nums[abs(n) - 1] = -nums[abs(n) - 1];
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0)
            ret.push_back(i + 1);
    }
    return ret;
}
vector<int> findDisappearedNumbers(vector<int>& nums)
{
    std::ios::sync_with_stdio(false);
    // 找到环上的数置为0，不在环上的数即为缺失的数
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 0)
            continue;

        int next = nums[i] - 1;
        while (nums[next] != 0) {
            int _next = nums[next] - 1;
            nums[next] = 0;
            next = _next;
        }
    }

    vector<int> ret;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            ret.push_back(i + 1);
        }
    }

    return ret;
}
} // namespace LC448

/***********************************************************************/
//! 双指针问题

// 11. Container With Most Water
namespace LC11 {
int maxArea(vector<int>& h)
{
    int ret = 0;
    for (int l = 0, r = h.size() - 1; l < r;) {
        int min_h = h[l] < h[r] ? h[l++] : h[r--];
        ret = max(ret, (r - l + 1) * min_h);
    }
    return ret;
}
} // namespace ContainerWithMostWater

// 42. Trapping Rain Water
namespace LC42 {
int trap(vector<int>& h)
{
    if (h.size() < 3)
        return 0;
    int ret = 0, l = 0, r = h.size() - 1;
    int l_max = 0, r_max = 0;
    while (l <= r) {
        if (l_max < r_max) {
            if (l_max < h[l]) {
                l_max = h[l];
            } else {
                ret += l_max - h[l];
            }
            l++;
        } else {
            if (r_max < h[r]) {
                r_max = h[r];
            } else {
                ret += r_max - h[r];
            }
            r--;
        }
    }
    return ret;
}

void test()
{
    vector<int> h{ 5, 2, 1, 2, 1, 5 };
    cout << trap(h) << endl;
}
} // namespace LC42

// 19. Remove Nth Node From End of List
namespace LC19 {
ListNode* removeNthFromEnd(ListNode* head, int n)
{
    if (!head)
        return NULL;
    // 前后指针，后指针滞后前指针n步
    ListNode *f = head, *b = head;
    int i = 0; //总结点个数为i+1
    while (f->next) {
        f = f->next;
        i++;
        if (i > n)
            b = b->next;
    }
    // 若要删除的是最前面的节点
    if (i + 1 == n)
        return head->next;

    // 至此，b为倒数第i个节点（i=1,2,3，...）前面的那个节点
    b->next = b->next->next;

    return head;
}
} // namespace LC19

// 28. Implement strStr()
namespace LC28 {
int strStr(string haystack, string needle)
{
    if (needle.empty())
        return 0;
    int ph = 0, pn = 0;
    while (ph < haystack.size()) {
        if (haystack[ph] == needle[pn]) {
            ph++;
            pn++;
        } else {
            // 如果前pn个都匹配，第pn+1个不匹配，则ph回退pn-1步
            ph -= pn;
            pn = 0;
        }
        if (pn >= needle.size())
            return ph - needle.size();
    }
    return -1;
}
} // namespace LC28

// 30. Substring with Concatenation of All Words
namespace LC30 {
vector<int> findSubstring(string s, vector<string>& words)
{
}
} // namespace LC30

// 76. Minimum Window Substring
namespace LC76 {
string minWindow(string s, string t)
{
}
} // namespace LC76

// 61. Rotate List
namespace LC61 {

ListNode* rotateRight(ListNode* head, int k)
{

    if (k == 0 || head == NULL)
        return head;
    int n = 0;
    ListNode* p = head;
    vector<ListNode*> nodes;
    while (p) {
        n++; // n为链表中非空节点数
        nodes.push_back(p);
        p = p->next;
    }
    int r = k % n;
    if (r == 0)
        return head;
    // 将nodes[n-r,n-1]移到前面
    nodes[n - r - 1]->next = NULL;
    nodes[n - 1]->next = head;
    return nodes[n - r];
}

} // namespace LC61

namespace LC86 {
ListNode* partition(ListNode* head, int x)
{
    ListNode* before = new ListNode(0);
    ListNode* after = new ListNode(0);
    ListNode *tb = before, *ta = after;

    while (head) {
        if (head->val < x) {
            tb->next = head;
            head = head->next;
            tb->next->next = NULL;
            tb = tb->next;
        } else {
            ta->next = head;
            head = head->next;
            ta->next->next = NULL;
            ta = ta->next;
        }
    }
    ListNode* ret = before->next;
    if (before->next) {
        tb->next = after->next;
    } else {
        ret = after->next;
    }
    delete before, after;
    return ret;
}
} // namespace LC86

// 234. Palindrome Linked List
namespace LC234 {
bool isPalindrome1(ListNode* head)
{
    int n = 0;
    vector<ListNode*> nodes;
    while (head) {
        n++;
        nodes.push_back(head);
        head = head->next;
    }
    for (int i = 0; i < n / 2; i++) {
        if (nodes[i]->val != nodes[n - i - 1]->val)
            return false;
    }
    return true;
}
// 上述方法占用内存较多

bool isPalindrome(ListNode* head)
{
    ListNode *fast, *slow, *prev, *next;
    fast = head;
    slow = head;
    prev = nullptr;
    while (fast && fast->next) {
        fast = fast->next->next;
        next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }
    //! 注意这里的反向存储链表的步骤有点绕，应熟练 ！
    if (fast) {
        slow = slow->next;
    }

    while (slow && prev) {
        if (slow->val != prev->val)
            return false;
        slow = slow->next;
        prev = prev->next;
    }
    return true;
}
} // namespace LC234

// 349. Intersection of Two Arrays
// 就用并查集的思想，题目比较低端。。。
namespace LC349 {
vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
    unordered_map<int, int> m;
    vector<int> ret;
    for (auto& num : nums1) {
        m[num] = 1;
    }
    for (auto& num : nums2) {
        if (m.count(num) == 1 && m[num] == 1) {
            m[num] = 2;
            ret.push_back(num);
        }
    }
    return ret;
}
void test()
{
    vector<int> nums1{ 4, 9, 5 };
    vector<int> nums2{ 9, 4, 9, 8, 4 };
    intersection(nums1, nums2);
}
} // namespace LC349

// 350. Intersection of Two Arrays II
namespace LC350 {
vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
    // 思路：同349，只不过多维护一个val，表示数字出现的次数
    unordered_map<int, int> m;
    vector<int> ret;
    for (auto& num : nums1)
        ++m[num];
    for (auto& num : nums2) {
        if (m.count(num) == 1 && m[num] >= 1) {
            m[num] -= 1;
            ret.push_back(num);
        }
    }
    return ret;
}
void test()
{
    vector<int> nums1{ 4, 9, 5 };
    vector<int> nums2{ 9, 4, 9, 8, 4 };
    intersect(nums1, nums2);
}
} // namespace LC350

// 424. Longest Repeating Character Replacement
namespace LC424 {
int characterReplacement(string s, int k)
{
    // 思路：循环26个字母，每轮记录下非该字母的位置pos，并考虑边界条件，
    // 后面利用滑动窗口，左右指针相差k，均指向pos，计算最大值
    int ret = 0;
    vector<int> pos;

    for (int i = 0; i < 26; i++) {
        pos.clear();
        pos.push_back(-1);
        for (int j = 0; j < s.size(); j++) {
            if (s[j] != 'A' + i)
                pos.push_back(j);
        }
        pos.push_back(s.size());
        int l = 0, r = k + 1;
        if (k + 2 >= pos.size())
            return s.size();
        while (r < pos.size()) {
            ret = max(ret, pos[r] - pos[l] - 1);
            l++;
            r++;
        }
    }

    return ret;
}
// 上述性能不太好

void test()
{
    string s = "AABABBA";
    cout << characterReplacement(s, 1);
}
} // namespace LC424

// 2. Add Two Numbers
namespace LC2 {
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode *t1 = l1, *t2 = l2;
    vector<ListNode*> nodes;
    bool endl1 = false;
    int ci = 0;
    while (t1 || t2) {
        int a = 0, b = 0;
        if (t1)
            a = t1->val;
        if (t2)
            b = t2->val;
        int ca = a + b + ci;
        ci = ca / 10;
        nodes.push_back(new ListNode(ca % 10));
        if (t1)
            t1 = t1->next;
        if (t2)
            t2 = t2->next;
    }
    if (ci != 0)
        nodes.push_back(new ListNode(ci));
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes.back()->next = NULL;
    return nodes[0];
}
} // namespace LC2

// 5. Longest Palindromic Substring
namespace LC5 {
string longestPalindrome1(string s)
{
    int n = s.size(), start = 0, maxLen = 1;
    vector<vector<int>> d(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        d[i][i] = 1;
        if (i + 1 < n && s[i] == s[i + 1]) {
            d[i][i + 1] = 1;
            start = i;
            maxLen = 2;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 2; j < n; j++) {
            if (d[i + 1][j - 1] && s[i] == s[j]) {
                d[i][j] = 1;
                if (j - i + 1 > maxLen) {
                    start = i;
                    maxLen = j - i + 1;
                }
            }
        }
    }
    return s.substr(start, maxLen);
}

// 上述用时和内存均不理想
string longestPalindrome(string s)
{
    int n = s.size(), maxStart = 0, maxEnd = 0, maxLen = 1;
    for (int i = 0; i < n;) {
        int start = i, end = i;

        while (end + 1 < n && s[end + 1] == s[end])
            end++;
        i = end + 1;
        while (start - 1 >= 0 && end + 1 < n && s[start - 1] == s[end + 1]) {
            start--;
            end++;
        }
        if (end - start + 1 > maxLen) {
            maxLen = end - start + 1;
            maxStart = start;
            maxEnd = end;
        }
    }
    return s.substr(maxStart, maxEnd - maxStart + 1);
}
} // namespace LC5

// [7] Reverse Integer
namespace LC7 {
int reverse(int x)
{
    int ret = 0;
    while (x) {
        ret = ret * 10 + x % 10;
        x = x / 10;
    }
    return ret;
}
} // namespace LC7

// 9. Palindrome Number
namespace LC9 {
bool isPalindrome(int x)
{
    if (x < 0 || x && x % 10 == 0)
        return false;
    vector<int> nums;
    while (x) {
        nums.push_back(x % 10);
        x /= 10;
    }
    for (int i = 0; i < nums.size() / 2; i++) {
        if (nums[i] != nums[nums.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
} // namespace LC9

// 13. Roman to Integer
namespace LC13 {
int romanToInt(string s)
{
    // map<char, int> R = {
    //     { 'I', 1 },
    //     { 'V', 5 },
    //     { 'X', 10 },
    //     { 'L', 50 },
    //     { 'C', 100 },
    //     { 'D', 500 },
    //     { 'M', 1000 },
    // };
    int R['Z' + 1];
    R['I'] = 1;
    R['V'] = 5;
    R['X'] = 10;
    R['L'] = 50;
    R['C'] = 100;
    R['D'] = 500;
    R['M'] = 1000;
    int ret = 0;
    for (int i = 0; i < s.size(); i++) {
        if (i + 1 < s.size() && R[s[i + 1]] > R[s[i]])
            ret -= R[s[i]];
        else
            ret += R[s[i]];
    }
    return ret;
}
} // namespace LC13

// 14. Longest Common Prefix
namespace LC14 {
string longestCommonPrefix(vector<string>& strs)
{
    if (strs.empty())
        return {};
    string ret;
    for (int cur = 0;; cur++) {
        bool sav = false;
        for (auto& str : strs) {
            if (!sav) {
                sav = true;
                ret.push_back(str[cur]);
            }
            if (cur >= str.size() || ret.back() != str[cur]) {
                ret.pop_back();
                return ret;
            }
        }
    }
    return ret;
}
} // namespace LC14

// 20. Valid Parentheses
namespace LC20 {
bool isValid(string s)
{
    stack<char> p;
    for (auto& ch : s) {
        if (ch == '(' || ch == '[' || ch == '{')
            p.push(ch);
        else {
            if (ch == ')' && (p.empty() || p.top() != '(')
                || ch == ']' && (p.empty() || p.top() != '[')
                || ch == '}' && (p.empty() || p.top() != '{'))
                return false;
            else
                p.pop();
        }
    }
    if (p.empty())
        return true;
    else
        return false;
}

} // namespace LC20

// 21. Merge Two Sorted Lists
namespace LC21 {
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode *ret = new ListNode(0), *t1 = l1, *t2 = l2, *cur = ret;
    bool flag = false;
    while (t1 || t2) {
        if (!t2 || t1 && t1->val < t2->val) {
            cur->next = t1;
            t1 = t1->next;
        } else {
            cur->next = t2;
            t2 = t2->next;
        }
        cur = cur->next;
    }
    return ret->next;
}
} // namespace LC21

// 38. Count and Say
namespace LC38 {
string countAndSay(int n)
{
    string pre = "1", cur;
    if (n == 1)
        return pre;
    for (int i = 1; i < n; i++) {
        cur.clear();
        int start = 0, end = 0;
        while (end < pre.size()) {
            while (end + 1 < pre.size() && pre[end] == pre[end + 1]) {
                end++;
            }
            cur.push_back(end - start + '1');
            cur.push_back(pre[start]);
            end++;
            start = end;
        }
        pre = cur;
    }
    return cur;
}
void test()
{
    for (int i = 0; i < 10; i++) {
        cout << countAndSay(i + 1) << endl;
    }
}
} // namespace LC38

// [53] Maximum Subarray
namespace LC53 {
// O(n^2)
int maxSubArray1(vector<int>& nums)
{
    int maxSum = INT32_MIN, sum = 0, end = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            maxSum = max(maxSum, sum);
        }
    }
    return maxSum;
}

// DP 关键在于定义子问题
int maxSubArray(vector<int> nums)
{
    int n = nums.size();
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    int maxSub = dp[0];
    for (int i = 1; i < n; i++) {
        dp[i] = (dp[i - 1] > 0 ? dp[i - 1] : 0) + nums[i];
        maxSub = max(maxSub, dp[i]);
    }
    return maxSub;
}

void test()
{
    vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    cout << maxSubArray(nums);
}
} // namespace LC53
// [58] Length of Last Word
namespace LC58 {
int lengthOfLastWord1(string s)
{
    int ret = 0, cur = 0;
    while (cur < s.size()) {
        // 出现连续空格则跳到最后那个空格
        while (s[cur] == ' ' && cur + 1 < s.size() && s[cur + 1] == s[cur])
            cur++;
        // 不是末尾的空格
        if (s[cur] == ' ' && cur + 1 < s.size())
            ret = 0;
        if (isalpha(s[cur])) {
            ret++;
        }
        cur++;
    }
    return ret;
}
int lengthOfLastWord(string s)
{
    while (s.size() && s[s.size() - 1] == ' ')
        s.erase(s.size() - 1, 1);
    return s.size() - s.rfind(' ') - 1;
}
} // namespace LC58

// [66] Plus One
namespace LC66 {
vector<int> plusOne(vector<int>& digits)
{
    int ci = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        int ca = digits[i] + 1;
        digits[i] = ca % 10;
        ci = ca / 10;
        if (!ci)
            break;
    }
    if (ci)
        digits.insert(digits.begin(), ci);
    return digits;
}
} // namespace LC66

// [67] Add Binary
namespace LC67 {
string addBinary(string a, string b)
{
    string ret;
    int ci = 0, ca = 0;
    for (int na = a.size() - 1, nb = b.size() - 1; na >= 0 || nb >= 0; na--, nb--) {
        ca = (na >= 0 ? a[na] - '0' : 0) + (nb >= 0 ? b[nb] - '0' : 0) + ci;
        ci = ca / 2;
        ret = to_string(ca % 2) + ret;
    }
    if (ci) {
        ret = to_string(ci) + ret;
    }
    return ret;
}
} // namespace LC67

// [69] Sqrt(x)
namespace LC69 {
int mySqrt(int x)
{
    long l = 0, g = x, m = l + (g - l) / 2, m2;
    while (l <= g) {
        m = l + (g - l) / 2;
        m2 = (m * m);
        if (m2 > x)
            g = m - 1;
        else if (m2 < x)
            l = m + 1;
        else
            return m;
    }
    return int(l - 1);
}
} // namespace LC69

// [70] Climbing Stairs
namespace LC70 {
int climbStairs(int n)
{
    vector<int> ways(n + 1);
    ways[0] = 1;
    ways[1] = 1;
    for (int i = 2; i < n + 1; i++) {
        ways[i] = ways[i - 1] + ways[i - 2];
    }
    return ways[n];
}
} // namespace LC70

// [83] Remove Duplicates from Sorted List
namespace LC83 {
ListNode* deleteDuplicates(ListNode* head)
{
    ListNode *start = head, *end = head;
    while (end) {
        while (end->next && end->val == end->next->val)
            end = end->next;
        start->next = end->next;
        end = end->next;
        start = end;
    }
    return head;
}
} // namespace LC83

// [100] Same Tree
namespace LC100 {
bool isSameTree(TreeNode* p, TreeNode* q)
{
    if (!p && !q)
        return true;
    if (p && q && p->val == q->val) {
        if (!isSameTree(p->left, q->left))
            return false;
        if (!isSameTree(p->right, q->right))
            return false;
    } else {
        return false;
    }
    return false;
}
} // namespace LC100

// [101] Symmetric Tree
namespace LC101 {
// 递归写法 recursive
bool isMirror(TreeNode* p, TreeNode* q)
{
    if (!p && !q)
        return true;
    if (!p || !q)
        return false;
    return (p->val == q->val)
        && isMirror(p->left, q->right)
        && isMirror(q->left, p->right);
}
bool isSymmetric(TreeNode* root)
{
    if (!root)
        return true;
    return isMirror(root->left, root->right);
}

// 迭代写法 iterative (类似BFS)
bool isSymmetric2(TreeNode* root)
{
    TreeNode *l, *r;
    queue<TreeNode*> q;
    q.push(root);
    q.push(root);
    while (!q.empty()) {
        l = q.front();
        q.pop();
        r = q.front();
        q.pop();
        if (!l && !r)
            continue;
        if (!l || !r)
            return false;
        if (l->val != r->val)
            return false;
        q.push(l->left);
        q.push(r->right);
        q.push(l->right);
        q.push(r->left);
    }
    return true;
}
} // namespace LC101

// [104] Maximum Depth of Binary Tree
namespace LC104 {
int maxDepth(TreeNode* root)
{
    if (!root)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
} // namespace LC10

// [107] Binary Tree Level Order Traversal II
namespace LC107 {
void unit(TreeNode* node, vector<vector<int>>& ret, int n)
{
    if (!node)
        return;
    if (ret.size() < n)
        ret.push_back(vector<int>());
    ret[n - 1].push_back(node->val);
    if (node->left)
        unit(node->left, ret, n + 1);
    if (node->right)
        unit(node->right, ret, n + 1);
}
vector<vector<int>> levelOrderBottom(TreeNode* root)
{
    vector<vector<int>> ret;
    unit(root, ret, 1);
    reverse(ret.begin(), ret.end());
    return ret;
}
} // namespace LC107

// [108] Convert Sorted Array to Binary Search Tree
namespace LC108 {
TreeNode* unit(vector<int>& nums, int l, int r)
{
    if (l > r)
        return NULL;
    int m = l + (r - l) / 2;
    TreeNode* node = new TreeNode(nums[m]);
    node->left = unit(nums, l, m - 1);
    node->right = unit(nums, m + 1, r);

    return node;
}
TreeNode* sortedArrayToBST(vector<int>& nums)
{
    return unit(nums, 0, nums.size() - 1);
}
} // namespace LC108

// [110] Balanced Binary Tree
namespace LC110 {
int getDepth(TreeNode* node)
{
    if (!node)
        return 0;
    return max(getDepth(node->left), getDepth(node->right)) + 1;
}

bool isBalanced(TreeNode* root)
{
    if (abs(getDepth(root->left) - getDepth(root->right)) <= 1
        && isBalanced(root->left)
        && isBalanced(root->right))
        return true;
    return false;
}
} // namespace LC110

// [111] Minimum Depth of Binary Tree
namespace LC111 {
int minDepth(TreeNode* root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    int minD = INT32_MAX;
    if (root->left)
        minD = min(minD, minDepth(root->left) + 1);
    if (root->right)
        minD = min(minD, minDepth(root->right) + 1);
    return minD;
}
} // namespace LC111

// [112] Path Sum
namespace LC112 {
bool hasPathSum(TreeNode* root, int sum)
{
    if (!root)
        return false;
    if (sum == root->val)
        return true;
    return hasPathSum(root->left, sum - root->val)
        || hasPathSum(root->right, sum - root->val);
}
} // namespace LC112

// [118] Pascal's Triangle
namespace LC118 {
vector<vector<int>> generate(int n)
{
    if (n == 0)
        return {};
    vector<vector<int>> ret;
    ret.push_back(vector<int>(1, 1));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (ret.size() < i + 1)
                ret.push_back(vector<int>());
            int l = j - 1 >= 0 ? ret[i - 1][j - 1] : 0;
            int r = j < i ? ret[i - 1][j] : 0;
            ret[i].push_back(l + r);
        }
    }
    return ret;
}
} // namespace LC118

// [119] Pascal's Triangle II
namespace LC119 {
vector<int> getRow(int n)
{
    vector<int> ret(n + 1, 0);
    ret[0] = 1;
    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j >= 1; j--) {
            ret[j] += ret[j - 1];
        }
    }
    return ret;
}
} // namespace LC119

// [121] Best Time to Buy and Sell Stock
namespace LC121 {
int maxProfit1(vector<int>& prices)
{
    int n = prices.size(), ret = 0, buy = 0;
    vector<int> dp(n, 0);
    for (int buy = n - 2; buy >= 0; buy--) {
        int p = dp[buy + 1] + prices[buy + 1] - prices[buy];
        dp[buy] = p > 0 ? p : 0;
        ret = max(ret, dp[buy]);
    }
    return ret;
}

// 非dp方法
int maxProfit(vector<int>& prices)
{
    if (prices.empty())
        return 0;
    int pro = 0, low = prices[0];
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] < low)
            low = prices[i];
        else
            pro = max(prices[i] - low, pro);
    }
    return pro;
}
} // namespace LC121

// [122] Best Time to Buy and Sell Stock II
namespace LC122 {
int maxProfit(vector<int>& prices)
{
    int n = prices.size(), buy = 0, sell = 0, profit = 0;
    while (sell < n) {
        while (buy + 1 < n && prices[buy] >= prices[buy + 1])
            buy++;
        // 目前buy为当前最低
        sell = buy;
        while (sell + 1 < n && prices[sell] <= prices[sell + 1])
            sell++;
        // 目前sell为当前最高
        profit += prices[sell] - prices[buy];
        sell++;
        buy = sell;
    }
    return profit;
}
} // namespace LC122

// [136] Single Number
namespace LC136 {
int singleNumber(vector<int>& nums)
{
    int ret = 0;
    for (auto& num : nums) {
        ret ^= num;
    }
    return ret;
}
} // namespace LC136

// [155] Min Stack
namespace LC155 {
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> s;
    stack<int> m;

    MinStack()
    {
    }

    void push(int x)
    {
        s.push(x);
        if (m.empty() || x <= getMin())
            m.push(x);
    }

    void pop()
    {
        if (s.top() == m.top())
            m.pop();
        s.pop();
    }

    int top()
    {
        return s.top();
    }

    int getMin()
    {
        return m.top();
    }
};
} // namespace LC155

// [160] Intersection of Two Linked Lists
namespace LC160 {
// 暴力解法
ListNode* getIntersectionNode1(ListNode* headA, ListNode* headB)
{
    ListNode *ta = headA, *tb = headB;
    while (ta) {
        tb = headB;
        while (tb) {
            if (ta == tb)
                return ta;
            tb = tb->next;
        }
        ta = ta->next;
    }
    return NULL;
}
// 使用哈希表
ListNode* getIntersectionNode2(ListNode* headA, ListNode* headB)
{
    unordered_map<ListNode*, int> m;
    ListNode *ta = headA, *tb = headB;
    while (ta) {
        m[ta] = 1;
        ta = ta->next;
    }
    while (tb) {
        if (m.count(tb) == 1)
            return tb;
        tb = tb->next;
    }
    return NULL;
}
// 双指针
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
    ListNode *ta = headA, *tb = headB;
    bool ca = false, cb = false;
    do {
        ta = ta->next;
        tb = tb->next;
        if (!ta) {
            if (!ca) {
                ca = true;
                ta = headB;
            }
        }
        if (!tb) {
            if (!cb) {
                cb = true;
                tb = headA;
            }
        }
    } while (ta != tb);
    return ta;
}
} // namespace LC160

// [168] Excel Sheet Column Title
namespace LC168 {
string convertToTitle(int n)
{
    string ret;
    while (n) {
        int ch = n % 26;
        ret += char(ch ? (ch + 'A' - 1) : 'Z');
        n /= 26;
    }
    return ret;
}
} // namespace LC168

// [169] Majority Element
namespace LC169 {
// 哈希表 时间复杂度O(n),空间复杂度O(n)
int majorityElement1(vector<int>& nums)
{
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        ++map[nums[i]];
        if (map[nums[i]] > nums.size() / 2)
            return nums[i];
    }
    return 0;
}
// 时间复杂度O(n),空间复杂度O(1)
int majorityElement(vector<int>& nums)
{
    int maj, count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (count == 0)
            maj = nums[i];
        if (nums[i] != maj)
            count--;
        else
            count++;
    }
    return maj;
}
} // namespace LC169

// [171] Excel Sheet Column Number
namespace LC171 {
int titleToNumber(string s)
{
    long long ret = 0;
    for (auto& c : s) {
        ret = ret * 26 + c - 'A' + 1;
    }
    return int(ret);
}
} // namespace LC171

// [172] Factorial Trailing Zeroes
namespace LC172 {
int trailingZeroes(int n)
{
    int ret = 0;
    for (long long i = 5; n / i > 0; i *= 5)
        ret += (n / i);

    return ret;
}
void test()
{
    cout << trailingZeroes(10);
}
} // namespace LC172

// [189] Rotate Array
namespace LC189 {
void rotate(vector<int>& nums, int k)
{
    int n = nums.size();
    k = k % n;
    vector<int> ret(n);
    int i = 0;
    for (; i < k; i++) {
        ret[i] = nums[n - k + i];
    }
    for (; i < n; i++) {
        ret[i] = nums[i - k];
    }
    nums = ret;
}
} // namespace LC189

// [190] Reverse Bits
namespace LC190 {
uint32_t reverseBits(uint32_t n)
{
    uint32_t ret = 0;
    for (int i = 0; i < 32; i++) {
        ret = ret * 2 + n % 2;
        n /= 2;
    }
    return ret;
}
} // namespace LC190

// [191] Number of 1 Bits
namespace LC191 {
int hammingWeight(uint32_t n)
{
    int ret = 0;
    for (int i = 0; i < 32; i++) {
        ret += n % 2;
        n /= 2;
    }
    return ret;
}
} // namespace LC191

// [198] House Robber
namespace LC198 {
int rob(vector<int>& nums)
{
    int ret = 0;
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];
    if (n == 2)
        return max(nums[0], nums[1]);
    if (n == 3)
        return max(nums[0] + nums[2], nums[1]);
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = nums[1];
    dp[2] = nums[0] + nums[2];
    for (int i = 3; i < n; i++) {
        dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i];
    }
    return max(dp[n - 1], dp[n - 2]);
}
void test()
{
    vector<int> nums = { 1, 2, 3, 1 };
    cout << rob(nums);
}
} // namespace LC198

// [202] Happy Number
namespace LC202 {
bool isHappy(int n)
{
    int m = n, s = n;
    unordered_map<int, int> h;
    h[n] = 1;
    while (m != 1) {
        s = 0;
        while (m) {
            s += pow(m % 10, 2);
            m /= 10;
        }
        m = s;
        if (h.count(m) == 1)
            break;
        h[m] = 1;
    }
    return m == 1;
}
void test()
{
    cout << isHappy(2);
}
} // namespace LC202

// [203] Remove Linked List Elements
namespace LC203 {
ListNode* removeElements(ListNode* head, int val)
{
    ListNode *ret = new ListNode(0), *r = ret;
    ListNode* cur = head;
    while (cur) {
        if (cur->val == val) {
            cur = cur->next;
            continue;
        }
        r->next = cur;
        cur = cur->next;
        r = r->next;
    }
    r->next = NULL;
    return ret->next;
}
} // namespace LC203

// [204] Count Primes
namespace LC204 {
bool isPrime(int n)
{
    if (n <= 2)
        return false;
    for (int i = 2; i < int(sqrt(n)); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
int countPrimes(int n)
{

    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (isPrime(i))
            ret++;
    }
    return ret;
}
} // namespace LC204

// [205] Isomorphic Strings
namespace LC205 {
bool isIsomorphic(string s, string t)
{
    int m1[256] = { 0 }, m2[256] = { 0 }, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (m1[s[i]] != m2[t[i]])
            return false;
        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}
} // namespace LC205

// [206] Reverse Linked List
namespace LC206 {
ListNode* reverseList(ListNode* head)
{
    ListNode *root = head, *cur = head, *pre = NULL;
    while (cur) {
        root = cur;
        cur = cur->next;
        root->next = pre;
        pre = root;
    }
    return root;
}
} // namespace LC206

// [217] Contains Duplicate
namespace LC217 {
bool containsDuplicate(vector<int>& nums)
{
    unordered_map<int, int> m;
    for (auto& num : nums) {
        if (m.find(num) != m.end())
            return true;
        m[num] = 1;
    }
    return false;
}
} // namespace LC217

// [219] Contains Duplicate II
namespace LC219 {
bool containsNearbyDuplicate(vector<int>& nums, int k)
{
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        if (m.find(nums[i]) != m.end() && i - m[nums[i]] <= k) {
            return true;
        }
        m[nums[i]] = i;
    }
    return false;
}
} // namespace LC219

// [235] Lowest Common Ancestor of a Binary Search Tree
namespace LC235 {
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (root->val < p->val && root->val < q->val)
        return lowestCommonAncestor(root->right, p, q);
    if (root->val > p->val && root->val > q->val)
        return lowestCommonAncestor(root->left, p, q);
    return root;
}
} // namespace LC235

// [237] Delete Node in a Linked List
namespace LC237 {
void deleteNode(ListNode* node)
{
    while (true) {
        node->val = node->next->val;
        if (!node->next->next) {
            node->next = NULL;
            break;
        }
        node = node->next;
    }
}
} // namespace LC237

// [242] Valid Anagram
namespace LC242 {
bool isAnagram(string s, string t)
{
    unordered_map<char, int> m, n;
    for (auto c : s)
        ++m[c];
    for (auto c : t)
        ++n[c];
    for (auto c : s) {
        if (m[c] != n[c])
            return false;
    }
    return true;
}
} // namespace LC242

// [257] Binary Tree Paths
namespace LC257 {
void unit(TreeNode* node, string curPath, vector<string>& ret)
{

    if (node->left || node->right)
        curPath += to_string(node->val) + "->";
    else {
        curPath += to_string(node->val);
        ret.push_back(curPath);
    }
    if (node->left)
        unit(node->left, curPath, ret);
    if (node->right)
        unit(node->right, curPath, ret);
}
vector<string> binaryTreePaths(TreeNode* root)
{
    if (!root)
        return {};
    vector<string> ret;
    string curPath = "";
    unit(root, curPath, ret);

    return ret;
}
} // namespace LC257

// [258] Add Digits
namespace LC258 {
int addDigits(int num)
{
    return 1 + (num - 1) % 9;
}
} // namespace LC258

// [263] Ugly Number
namespace LC263 {
bool isUgly(int num)
{
    for (int i = 2; i < 6 && num; i++)
        while (num % i == 0)
            num /= i;
    return num == 1;
}
} // namespace LC263

// [278] First Bad Version
namespace LC278 {
bool isBadVersion(int n) { return true; }
int firstBadVersion1(int n)
{
    int l = 1, r = n;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (isBadVersion(m)) {
            if (m == 1 || m > 1 && !isBadVersion(m - 1))
                return m;
            else
                r = m - 1;
        } else {
            if (m == n || m < n && isBadVersion(m + 1))
                return m;
            else
                l = m + 1;
        }
    }
    return l;
}
// 改进
int firstBadVersion(int n)
{
    int l(0), r(n);
    while (l < r) {
        int mid(l + (r - l) / 2);
        if (!isBadVersion(mid))
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
} // namespace LC278

// [292] Nim Game
namespace LC292 {
bool canWinNim(int n)
{
    return n % 4 != 0;
}
} // namespace LC292

// [326] Power of Three
namespace LC326 {
bool isPowerOfThree(int n)
{
    if (n > 1)
        while (n % 3 == 0)
            n /= 3;
    return n == 1;
}
} // namespace LC326

// [367] Valid Perfect Square
namespace LC367 {
bool isPerfectSquare(int n)
{
    int l = 0, r = n;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (m * m < n)
            l = m + 1;
        else if (m * m > n)
            r = m - 1;
        else
            return true;
    }

    return l * l == n;
}
} // namespace LC367

// [371] Sum of Two Integers
namespace LC371 {
// a+b
int getSum(int a, int b)
{
    return b == 0 ? a : getSum(a ^ b, (a & b & 0xffffffff) << 1);
}

// a-b
int getSubtract(int a, int b)
{
    return b == 0 ? a : getSubtract(a ^ b, (~a & b & 0xffffffff) << 1);
}

void test()
{
    cout << getSubtract(1, -1);
}
} // namespace LC371

// [383] Ransom Note
namespace LC383 {
bool canConstruct(string ransomNote, string magazine)
{
    int m['z' + 1] = { 0 };
    for (int i = 0; i < magazine.size(); ++i) {
        ++m[magazine[i]];
    }
    for (int i = 0; i < ransomNote.size(); ++i) {
        --m[ransomNote[i]];
        if (m[ransomNote[i]] < 0)
            return false;
    }
    return true;
}
} // namespace LC383

// [387] First Unique Character in a String
namespace LC387 {
int firstUniqChar(string s)
{
    unordered_map<char, int> m;
    for (int i = 0; i < s.size(); i++) {
        ++m[s[i]];
    }
    for (int i = 0; i < s.size(); i++) {
        if (m[s[i]] == 1)
            return i;
    }
    return -1;
}
} // namespace LC387

// [389] Find the Difference
namespace LC389 {
char findTheDifference(string s, string t)
{
    char16_t ret = t.back();
    for (int i = 0; i < s.size(); i++) {
        ret ^= s[i] ^ t[i];
    }
    return char(ret);
}
} // namespace LC389