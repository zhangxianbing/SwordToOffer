#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 栈
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
// TODO 20. 有效的括号
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

// TODO
namespace LC150 {}  // namespace LC150
// TODO
namespace LC71 {}  // namespace LC71

//! 栈和递归的关系
// TODO
namespace LC144 {}  // namespace LC144
// TODO
namespace LC94 {}  // namespace LC94
// TODO
namespace LC145 {}  // namespace LC145
// TODO
namespace LC341 {}  // namespace LC341
