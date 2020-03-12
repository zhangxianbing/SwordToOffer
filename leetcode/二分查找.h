/*
 * @Author: zhangxianbing
 * @Date: 2019-08-12 20:32:27
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-12 21:05:32
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 二分查找
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
// LC4. 寻找两个有序数组的中位数
namespace LC4 {} // namespace LC4

// LC29. 两数相除
namespace LC29 {} // namespace LC29

// LC33. 搜索旋转排序数组
namespace LC33 {} // namespace LC33

// LC34. 在排序数组中查找元素的第一个和最后一个位置
namespace LC34 {} // namespace LC34

// LC35. 搜索插入位置
namespace LC35 {} // namespace LC35

// LC50. Pow(x, n)
namespace LC50 {} // namespace LC50

// LC69. x 的平方根
namespace LC69 {} // namespace LC69

// LC74. 搜索二维矩阵
namespace LC74 {} // namespace LC74

// LC81. 搜索旋转排序数组 II
namespace LC81 {} // namespace LC81

// LC153. 寻找旋转排序数组中的最小值
namespace LC153 {} // namespace LC153

// LC154. 寻找旋转排序数组中的最小值 II
namespace LC154 {} // namespace LC154

// LC162. 寻找峰值
namespace LC162 {} // namespace LC162

// LC167. 两数之和 II - 输入有序数组
namespace LC167 {} // namespace LC167

// LC174. 地下城游戏
namespace LC174 {} // namespace LC174

// LC209. 长度最小的子数组
namespace LC209 {} // namespace LC209

// LC222. 完全二叉树的节点个数
namespace LC222 {} // namespace LC222

// LC230. 二叉搜索树中第K小的元素
namespace LC230 {} // namespace LC230

// LC240. 搜索二维矩阵 II
namespace LC240 {} // namespace LC240

// LC270. 最接近的二叉搜索树值
namespace LC270 {} // namespace LC270

// LC275. H指数 II
namespace LC275 {} // namespace LC275

// LC278. 第一个错误的版本
namespace LC278 {} // namespace LC278

// LC287. 寻找重复数
namespace LC287 {} // namespace LC287

// LC300. 最长上升子序列
namespace LC300 {} // namespace LC300

// LC302. 包含全部黑色像素的最小矩形
namespace LC302 {} // namespace LC302

// LC315. 计算右侧小于当前元素的个数
namespace LC315 {} // namespace LC315

// LC327. 区间和的个数
namespace LC327 {} // namespace LC327

// LC349. 两个数组的交集
namespace LC349 {} // namespace LC349

// LC350. 两个数组的交集 II
namespace LC350 {
vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
  vector<int> ret;
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());
  int i = 0, j = 0;
  while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] == nums2[j]) {
      ret.push_back(nums1[i]);
      i++, j++;
    } else if (nums1[i] < nums2[j])
      i++;
    else
      j++;
  }
  return ret;
}
} // namespace LC350

// LC352. 将数据流变为多个不相交区间
namespace LC352 {} // namespace LC352

// LC354. 俄罗斯套娃信封问题
namespace LC354 {} // namespace LC354

// LC363. 矩形区域不超过 K 的最大数值和
namespace LC363 {} // namespace LC363

// LC367. 有效的完全平方数
namespace LC367 {} // namespace LC367

// LC374. 猜数字大小
namespace LC374 {} // namespace LC374

// LC378. 有序矩阵中第K小的元素
namespace LC378 {} // namespace LC378

// LC392. 判断子序列
namespace LC392 {} // namespace LC392

// LC410. 分割数组的最大值
namespace LC410 {} // namespace LC410

// LC436. 寻找右区间
namespace LC436 {} // namespace LC436

// LC441. 排列硬币
namespace LC441 {} // namespace LC441

// LC454. 四数相加 II
namespace LC454 {} // namespace LC454

// LC475. 供暖器
namespace LC475 {} // namespace LC475

// LC483. 最小好进制
namespace LC483 {} // namespace LC483

// LC493. 翻转对
namespace LC493 {} // namespace LC493

// LC644. 最大平均子段和 II
namespace LC644 {} // namespace LC644

// LC658. 找到 K 个最接近的元素
namespace LC658 {} // namespace LC658

// LC668. 乘法表中第k小的数
namespace LC668 {} // namespace LC668

// LC718. 最长重复子数组
namespace LC718 {} // namespace LC718

// LC719. 找出第 k 小的距离对
namespace LC719 {} // namespace LC719

// LC744. 寻找比目标字母大的最小字母
namespace LC744 {} // namespace LC744

// LC702. 搜索长度未知的有序数组
namespace LC702 {} // namespace LC702

// LC774. 最小化去加油站的最大距离
namespace LC774 {} // namespace LC774

// LC704. 二分查找
namespace LC704 {} // namespace LC704

// LC778. 水位上升的泳池中游泳
namespace LC778 {} // namespace LC778

// LC786. 第 K 个最小的素数分数
namespace LC786 {} // namespace LC786

// LC793. 阶乘函数后K个零
namespace LC793 {} // namespace LC793

// LC852. 山脉数组的峰顶索引
namespace LC852 {} // namespace LC852

// LC862. 和至少为 K 的最短子数组
namespace LC862 {} // namespace LC862

// LC710. 黑名单中的随机数
namespace LC710 {} // namespace LC710

// LC875. 爱吃香蕉的珂珂
namespace LC875 {} // namespace LC875

// LC878. 第 N 个神奇数字
namespace LC878 {} // namespace LC878

// LC528. 按权重随机选择
namespace LC528 {} // namespace LC528

// LC497. 非重叠矩形中的随机点
namespace LC497 {} // namespace LC497

// LC887. 鸡蛋掉落
namespace LC887 {} // namespace LC887

// LC911. 在线选举
namespace LC911 {} // namespace LC911

// LC927. 三等分
namespace LC927 {} // namespace LC927

// LC981. 基于时间的键值存储
namespace LC981 {} // namespace LC981

// LC1011. 在 D 天内送达包裹的能力
namespace LC1011 {} // namespace LC1011

// LC1060. 有序数组中的缺失元素
namespace LC1060 {} // namespace LC1060

// LC1064. 不动点
namespace LC1064 {} // namespace LC1064

// LC1044. 最长重复子串
namespace LC1044 {} // namespace LC1044

// LC1095. 山脉数组中查找目标值
namespace LC1095 {} // namespace LC1095
