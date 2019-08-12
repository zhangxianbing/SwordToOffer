/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:58
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-12 20:43:32
 * @Description: file content
 */
#pragma once
#include "../public.h"
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//
//# 栈
//# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #//

// LC20. 有效的括号
namespace LC20 {
bool isValid(string s) {
  stack<char> st;
  for (auto c : s) {
    if (c == '(' || c == '[' || c == '{') {
      st.push(c);
    } else {
      if (st.empty()) return false;
      if (c == ')') {
        if (st.top() == '(')
          st.pop();
        else
          return false;
      }
      if (c == ']') {
        if (st.top() == '[')
          st.pop();
        else
          return false;
      }
      if (c == '}') {
        if (st.top() == '{')
          st.pop();
        else
          return false;
      }
    }
  }
  return st.empty();
}
}  // namespace LC20

// LC42. 接雨水
namespace LC42 {}  // namespace LC42

// LC85. 最大矩形
namespace LC85 {}  // namespace LC85

// LC20. 有效的括号
namespace LC20 {}  // namespace LC20

// LC94. 二叉树的中序遍历
namespace LC94 {}  // namespace LC94

// LC225. 用队列实现栈
namespace LC225 {}  // namespace LC225

// LC739. 每日温度
namespace LC739 {}  // namespace LC739

// LC316. 去除重复字母
namespace LC316 {}  // namespace LC316

// LC394. 字符串解码
namespace LC394 {}  // namespace LC394

// LC496. 下一个更大元素 I
namespace LC496 {}  // namespace LC496

// LC1021. 删除最外层的括号
namespace LC1021 {}  // namespace LC1021

// LC224. 基本计算器
namespace LC224 {}  // namespace LC224

// LC155. 最小栈
namespace LC155 {}  // namespace LC155

// LC71. 简化路径
namespace LC71 {}  // namespace LC71

// LC144. 二叉树的前序遍历
namespace LC144 {}  // namespace LC144

// LC232. 用栈实现队列
namespace LC232 {}  // namespace LC232

// LC726. 原子的数量
namespace LC726 {}  // namespace LC726

// LC173. 二叉搜索树迭代器
namespace LC173 {}  // namespace LC173

// LC682. 棒球比赛
namespace LC682 {}  // namespace LC682

// LC84. 柱状图中最大的矩形
namespace LC84 {}  // namespace LC84

// LC503. 下一个更大元素 II
namespace LC503 {}  // namespace LC503

// LC145. 二叉树的后序遍历
namespace LC145 {}  // namespace LC145

// LC439. 三元表达式解析器
namespace LC439 {}  // namespace LC439

// LC856. 括号的分数
namespace LC856 {}  // namespace LC856

// LC341. 扁平化嵌套列表迭代器
namespace LC341 {}  // namespace LC341

// LC456. 132模式
namespace LC456 {}  // namespace LC456

// LC636. 函数的独占时间
namespace LC636 {}  // namespace LC636

// LC385. 迷你语法分析器
namespace LC385 {}  // namespace LC385

// LC103. 二叉树的锯齿形层次遍历
namespace LC103 {}  // namespace LC103

// LC1019. 链表中的下一个更大节点
namespace LC1019 {}  // namespace LC1019

// LC770. 基本计算器 IV
namespace LC770 {}  // namespace LC770

// LC255. 验证前序遍历序列二叉搜索树
namespace LC255 {}  // namespace LC255

// LC844. 比较含退格的字符串
namespace LC844 {}  // namespace LC844

// LC946. 验证栈序列
namespace LC946 {}  // namespace LC946

// LC402. 移掉K位数字
namespace LC402 {}  // namespace LC402

// LC975. 奇偶跳
namespace LC975 {}  // namespace LC975

// LC331. 验证二叉树的前序序列化
namespace LC331 {}  // namespace LC331

// LC895. 最大频率栈
namespace LC895 {}  // namespace LC895

// LC591. 标签验证器
namespace LC591 {}  // namespace LC591

// LC735. 行星碰撞
namespace LC735 {}  // namespace LC735

// LC901. 股票价格跨度
namespace LC901 {}  // namespace LC901

// LC1047. 删除字符串中的所有相邻重复项
namespace LC1047 {}  // namespace LC1047

// LC907. 子数组的最小值之和
namespace LC907 {}  // namespace LC907

// LC1003. 检查替换后的词是否有效
namespace LC1003 {}  // namespace LC1003

// LC150. 逆波兰表达式求值
namespace LC150 {}  // namespace LC150

// LC921. 使括号有效的最少添加
namespace LC921 {}  // namespace LC921

// LC880. 索引处的解码字符串
namespace LC880 {}  // namespace LC880

// LC1124. 表现良好的最长时间段
namespace LC1124 {}  // namespace LC1124

// LC272. 最接近的二叉搜索树值 II
namespace LC272 {}  // namespace LC272

// LC772. 基本计算器 III
namespace LC772 {}  // namespace LC772

// LC1063. 有效子数组的数目
namespace LC1063 {}  // namespace LC1063
