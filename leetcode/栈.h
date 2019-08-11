/*
 * @Author: zhangxianbing
 * @Date: 2019-08-09 11:42:58
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-09 11:42:58
 * @Description: file content
 */
#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 栈
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//

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

// LC
namespace LC150 {}  // namespace LC150

// LC
namespace LC71 {}  // namespace LC71

// LC
namespace LC145 {}  // namespace LC145

// LC
namespace LC341 {}  // namespace LC341
