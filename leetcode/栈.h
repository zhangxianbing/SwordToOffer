#pragma once
#include "../public.h"
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
//! 栈
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *//
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

namespace LC150 {}  // namespace LC150

namespace LC71 {}  // namespace LC71

//! 栈和递归的关系
namespace LC144 {}  // namespace LC144

namespace LC94 {}  // namespace LC94

namespace LC145 {}  // namespace LC145

namespace LC341 {}  // namespace LC341
