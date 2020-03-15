/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:34
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-18 15:12:15
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 查找表：包括map,set,unordered_map,unordered_set
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

// LC349. 两个数组的交集
namespace LC349 {
vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
  vector<int> res;
  unordered_map<int, int> m;
  for (auto num : nums1)
    m[num] = 1;
  for (auto num : nums2)
    if (m[num]-- == 1)
      res.push_back(num);
  return res;
}
} // namespace LC349

// LC350. 两个数组的交集 II
namespace LC350 {
vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
  unordered_map<int, int> m;
  vector<int> res;
  for (auto num : nums1)
    ++m[num];
  for (auto num : nums2)
    if (m[num]-- > 0)
      res.push_back(num);
  return res;
}
} // namespace LC350

// LC202. 快乐数
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
      if (s == 1)
        return true;
      return false;
    }
    m[s]++;
  }
  return false;
}
} // namespace LC202

// LC205. 同构字符串
namespace LC205 {
bool isIsomorphic(string s, string t) {
  if (s.size() != t.size())
    return false;
  unordered_map<char, int> m, n;
  for (int i = 0; i < s.size(); i++) {
    if (m[s[i]] != n[t[i]])
      return false;
    m[s[i]] = n[t[i]] = i + 1; // 注意这里不能从零开始，因为哈希表的value默认为0
  }
  return true;
}
} // namespace LC205

// LC290. 单词规律
namespace LC290 {
bool wordPattern(string pattern, string str) {
  map<char, int> p2i;
  map<string, int> w2i;
  istringstream in(str);
  int i = 0, n = pattern.size();
  for (string word; in >> word; ++i) {
    if (i == n || p2i[pattern[i]] != w2i[word])
      return false;
    p2i[pattern[i]] = w2i[word] = i + 1;
  }
  return i == n;
}
} // namespace LC290

// LC451. 根据字符出现频率排序
namespace LC451 {
string frequencySort(string s) {
  unordered_map<char, int> m;
  for (auto c : s)
    ++m[c];
  sort(s.begin(), s.end(),
       [&](char a, char b) { return m[a] == m[b] ? a < b : m[a] > m[b]; });
  return s;
}
} // namespace LC451

// LC1. 两数之和
namespace LC1 {
vector<int> twoSum(vector<int> &nums, int target) {
  unordered_map<int, int> m;
  for (int i = 0; i < nums.size(); i++) {
    if (m.find(target - nums[i]) != m.end())
      return {m[target - nums[i]], i};
    m[nums[i]] = i;
  }
  return {};
}
} // namespace LC1

// LC454. 四数相加 II
namespace LC454 {
int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C,
                 vector<int> &D) {
  int res = 0;
  unordered_map<int, int> AB;
  for (auto a : A)
    for (auto b : B)
      ++AB[a + b];
  for (auto c : C)
    for (auto d : D)
      if (AB[-c - d])
        res += AB[-c - d];
  return res;
}
} // namespace LC454

// LC447. 回旋镖的数量
namespace LC447 {
int dist(vector<int> &p, vector<int> &q) {
  int dx = p[0] - q[0];
  int dy = p[1] - q[1];
  return dx * dx + dy * dy;
}
int numberOfBoomerangs(vector<vector<int>> &points) {
  int res = 0;
  for (auto &p : points) {
    unordered_map<int, int> m;
    for (auto &q : points)
      ++m[dist(p, q)];
    for (auto &it : m)
      res += it.second * (it.second - 1);
  }
  return res;
}
} // namespace LC447

// LC217. 存在重复元素
namespace LC217 {
bool containsDuplicate(vector<int> &nums) {
  unordered_map<int, int> m;
  for (auto num : nums)
    if (m[num]++ == 1)
      return true;
  return false;
}

// LC219. 存在重复元素 II
namespace LC219 {
// 思路1：维护一个size==k大小的set作为滑动窗口
bool containsNearbyDuplicate1(vector<int> &nums, int k) {
  if (nums.size() <= 1 || k <= 0)
    return false;

  unordered_set<int> record;
  for (int i = 0; i < nums.size(); i++) {
    if (record.find(nums[i]) != record.end())
      return true;
    record.insert(nums[i]);
    if (record.size() == k + 1)
      record.erase(nums[i - k]);
  }

  return false;
}

bool containsNearbyDuplicate(vector<int> &nums, int k) {
  unordered_map<int, int> m;
  for (int i = 0; i < nums.size(); i++) {
    if (m.find(nums[i]) != m.end())
      if (i - m[nums[i]] <= k)
        return true;
    m[nums[i]] = i;
  }
  return false;
}
} // namespace LC219

// LC220. 存在重复元素 III
namespace LC220 {
//* 思路1：类似LC219（1）
bool containsNearbyAlmostDuplicate1(vector<int> &nums, int k, int t) {
  set<long long> record;
  for (int i = 0; i < nums.size(); i++) {
    auto lb = record.lower_bound(nums[i] - t);
    if (lb != record.end() && *lb <= long(nums[i] + t))
      return true;
    record.insert(nums[i]);
    if (record.size() == k + 1)
      record.erase(nums[i - k]);
  }
  return false;
}
//* 暴力解法
bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
  if (k == 10000)
    return false;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j <= i + k && j < nums.size(); j++) {
      if (abs(long(nums[j]) - long(nums[i])) <= t) {
        return true;
      }
    }
  }
  return false;
}
} // namespace LC220
} // namespace LC217

// LC666. 路径和 IV
namespace LC666 {
int pathSum(vector<int> &nums) {
  int res = 0;
  unordered_map<int, int> M;
  for (int i = int(nums.size()) - 1; i >= 0; i--) {
    int d = nums[i] / 100, p = (nums[i] % 100) / 10, v = nums[i] % 10;
    M[d * 10 + p] = max(M[d * 10 + p], 1);
    res += M[d * 10 + p] * v;
    // 如果一个节点会经过 n 次, 那么这 n 次也一定经过其父节点,
    // 因此将当前节点的次数加入其父节点中
    M[(d - 1) * 10 + (p - 1) / 2 + 1] += M[d * 10 + p];
  }
  return res;
}
} // namespace LC666

// LC535. TinyURL 的加密与解密
namespace LC535 {} // namespace LC535

// LC771. 宝石与石头
namespace LC771 {} // namespace LC771

// LC85. 最大矩形
namespace LC85 {} // namespace LC85

// LC37. 解数独
namespace LC37 {} // namespace LC37

// LC18. 四数之和
namespace LC18 {} // namespace LC18

// LC94. 二叉树的中序遍历
namespace LC94 {} // namespace LC94

// LC136. 只出现一次的数字
namespace LC136 {} // namespace LC136

// LC632. 最小区间
namespace LC632 {} // namespace LC632

// LC739. 每日温度
namespace LC739 {} // namespace LC739

// LC463. 岛屿的周长
namespace LC463 {} // namespace LC463

// LC30. 串联所有单词的子串
namespace LC30 {} // namespace LC30

// LC500. 键盘行
namespace LC500 {} // namespace LC500

// LC718. 最长重复子数组
namespace LC718 {} // namespace LC718

// LC811. 子域名访问计数
namespace LC811 {} // namespace LC811

// LC187. 重复的DNA序列
namespace LC187 {} // namespace LC187

// LC49. 字母异位词分组
namespace LC49 {} // namespace LC49

// LC560. 和为K的子数组
namespace LC560 {} // namespace LC560

// LC76. 最小覆盖子串
namespace LC76 {} // namespace LC76

// LC138. 复制带随机指针的链表
namespace LC138 {} // namespace LC138

// LC726. 原子的数量
namespace LC726 {} // namespace LC726

// LC690. 员工的重要性
namespace LC690 {} // namespace LC690

// LC694. 不同岛屿的数量
namespace LC694 {} // namespace LC694

// LC711. 不同岛屿的数量 II
namespace LC711 {} // namespace LC711

// LC525. 连续数组
namespace LC525 {} // namespace LC525

// LC409. 最长回文串
namespace LC409 {} // namespace LC409

// LC204. 计数质数
namespace LC204 {} // namespace LC204

// LC347. 前 K 个高频元素
namespace LC347 {} // namespace LC347

// LC299. 猜数字游戏
namespace LC299 {} // namespace LC299

// LC1002. 查找常用字符
namespace LC1002 {} // namespace LC1002

// LC389. 找不同
namespace LC389 {} // namespace LC389

// LC594. 最长和谐子序列
namespace LC594 {} // namespace LC594

// LC36. 有效的数独
namespace LC36 {
// bool isValidSudoku(vector<vector<char>> &board) {
//   for (int i = 0; i < 9; i++) {
//     unordered_set<char> record;
//     for (int j = 0; j < 9; j++) {
//       if (board[i][j] >= '1' && board[i][j] <= '9') {
//         if (record.find(board[i][j]) != record.end())
//           return false;
//         record.insert(board[i][j]);
//       }
//     }
//   }
//   for (int j = 0; j < 9; j++) {
//     unordered_set<char> record;
//     for (int i = 0; i < 9; i++) {
//       if (board[i][j] >= '1' && board[i][j] <= '9') {
//         if (record.find(board[i][j]) != record.end())
//           return false;
//         record.insert(board[i][j]);
//       }
//     }
//   }
//   for (int i = 0; i < 9; i += 3) {
//     for (int j = 0; j < 9; j += 3) {
//       unordered_set<char> record;
//       for (int k = i; k < i + 3; k++)
//         for (int m = j; m < j + 3; m++) {
//           if (board[k][m] >= '1' && board[k][m] <= '9') {
//             if (record.find(board[k][m]) != record.end())
//               return false;
//             record.insert(board[k][m]);
//           }
//         }
//     }
//   }
//   return true;
// }

// 改进
// 上述方法实际上每个元素都遍历了3次，实际上可以一次遍历完，然后考虑到这里的map比较小，实际上可以用数组代替
bool isValidSudoku(vector<vector<char>> &board) {
  int row[9][9] = {0};
  int col[9][9] = {0};
  int cell[9][9] = {0};
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      char c = board[i][j];
      if (c != '.')
        if (++row[i][c - '1'] > 1 || ++col[j][c - '1'] > 1 ||
            ++cell[3 * (i / 3) + j / 3][c - '1'] > 1)
          return false;
    }
  }
  return true;
}
} // namespace LC36

// LC575. 分糖果
namespace LC575 {} // namespace LC575

// LC710. 黑名单中的随机数
namespace LC710 {} // namespace LC710

// LC748. 最短完整词
namespace LC748 {} // namespace LC748

// LC1044. 最长重复子串
namespace LC1044 {} // namespace LC1044

// LC438. 找到字符串中所有字母异位词
namespace LC438 {} // namespace LC438

// LC274. H指数
namespace LC274 {} // namespace LC274

// LC149. 直线上最多的点数
namespace LC149 {} // namespace LC149

// LC781. 森林中的兔子
namespace LC781 {} // namespace LC781

// LC242. 有效的字母异位词
namespace LC242 {} // namespace LC242

// LC720. 词典中最长的单词
namespace LC720 {} // namespace LC720

// LC244. 最短单词距离 II
namespace LC244 {} // namespace LC244

// LC358. K 距离间隔重排字符串
namespace LC358 {} // namespace LC358

// LC648. 单词替换
namespace LC648 {} // namespace LC648

// LC645. 错误的集合
namespace LC645 {} // namespace LC645

// LC961. 重复 N 次的元素
namespace LC961 {} // namespace LC961

// LC350. 两个数组的交集 II
namespace LC350 {} // namespace LC350

// LC939. 最小面积矩形
namespace LC939 {} // namespace LC939

// LC884. 两句话中的不常见单词
namespace LC884 {} // namespace LC884

// LC166. 分数到小数
namespace LC166 {} // namespace LC166

// LC325. 和等于 k 的最长子数组长度
namespace LC325 {} // namespace LC325

// LC770. 基本计算器 IV
namespace LC770 {} // namespace LC770

// LC609. 在系统中查找重复文件
namespace LC609 {} // namespace LC609

// LC381. O(1) 时间插入、删除和获取随机元素 - 允许重复
namespace LC381 {} // namespace LC381

// LC336. 回文对
namespace LC336 {} // namespace LC336

// LC676. 实现一个魔法字典
namespace LC676 {} // namespace LC676

// LC508. 出现次数最多的子树元素和
namespace LC508 {} // namespace LC508

// LC705. 设计哈希集合
namespace LC705 {} // namespace LC705

// LC692. 前K个高频单词
namespace LC692 {} // namespace LC692

// LC554. 砖墙
namespace LC554 {} // namespace LC554

// LC387. 字符串中的第一个唯一字符
namespace LC387 {} // namespace LC387

// LC706. 设计哈希映射
namespace LC706 {} // namespace LC706

// LC953. 验证外星语词典
namespace LC953 {} // namespace LC953

// LC895. 最大频率栈
namespace LC895 {} // namespace LC895

// LC599. 两个列表的最小索引总和
namespace LC599 {} // namespace LC599

// LC992. K 个不同整数的子数组
namespace LC992 {} // namespace LC992

// LC624. 数组列表中的最大距离
namespace LC624 {} // namespace LC624

// LC930. 和相同的二元子数组
namespace LC930 {} // namespace LC930

// LC340. 至多包含 K 个不同字符的最长子串
namespace LC340 {} // namespace LC340

// LC380. 常数时间插入、删除和获取随机元素
namespace LC380 {} // namespace LC380

// LC1078. Bigram 分词
namespace LC1078 {} // namespace LC1078

// LC249. 移位字符串分组
namespace LC249 {} // namespace LC249

// LC974. 和可被 K 整除的子数组
namespace LC974 {} // namespace LC974

// LC311. 稀疏矩阵的乘法
namespace LC311 {} // namespace LC311

// LC970. 强整数
namespace LC970 {} // namespace LC970

// LC356. 直线镜像
namespace LC356 {} // namespace LC356

// LC266. 回文排列
namespace LC266 {} // namespace LC266

// LC1001. 网格照明
namespace LC1001 {} // namespace LC1001

// LC954. 二倍数对数组
namespace LC954 {} // namespace LC954

// LC734. 句子相似性
namespace LC734 {} // namespace LC734

// LC957. N 天后的牢房
namespace LC957 {} // namespace LC957

// LC288. 单词的唯一缩写
namespace LC288 {} // namespace LC288

// LC159. 至多包含两个不同字符的最长子串
namespace LC159 {} // namespace LC159

// LC246. 中心对称数
namespace LC246 {} // namespace LC246

// LC359. 日志速率限制器
namespace LC359 {} // namespace LC359

// LC1048. 最长字符串链
namespace LC1048 {} // namespace LC1048

// LC1072. 按列翻转得到最大值等行数
namespace LC1072 {} // namespace LC1072

// LC1086. 前五科的均分
namespace LC1086 {} // namespace LC1086

// LC1090. 受标签影响的最大值
namespace LC1090 {} // namespace LC1090

// LC966. 元音拼写检查器
namespace LC966 {} // namespace LC966

// LC981. 基于时间的键值存储
namespace LC981 {} // namespace LC981

// LC170. 两数之和 III - 数据结构设计
namespace LC170 {} // namespace LC170

// LC314. 二叉树的垂直遍历
namespace LC314 {} // namespace LC314

// LC760. 找出变位映射
namespace LC760 {} // namespace LC760

// LC987. 二叉树的垂序遍历
namespace LC987 {} // namespace LC987

// LC1133. 最大唯一数
namespace LC1133 {} // namespace LC1133

//$ 顺序表
// LC846. 一手顺子
namespace LC846 {} // namespace LC846

// LC731. 我的日程安排表 II
namespace LC731 {} // namespace LC731

// LC220. 存在重复元素 III
namespace LC220 {} // namespace LC220

// LC352. 将数据流变为多个不相交区间
namespace LC352 {} // namespace LC352

// LC855. 考场就座
namespace LC855 {} // namespace LC855

// LC732. 我的日程安排表 III
namespace LC732 {} // namespace LC732

// LC699. 掉落的方块
namespace LC699 {} // namespace LC699

// LC715. Range 模块
namespace LC715 {} // namespace LC715

// LC975. 奇偶跳
namespace LC975 {} // namespace LC975

// LC683. K 个空花盆
namespace LC683 {} // namespace LC683
