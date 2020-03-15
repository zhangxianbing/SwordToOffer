#pragma once
#include "../public.h"
/*
参考： https://www.cnblogs.com/OctoptusLian/p/9190176.html

*/

/*
 * 猎头简历问题
 * 已知猎头跟简历的对应关系，猎头手中的简历可能重叠，找到能获取全部简历的最少的猎头
 * eg:
 * A -> 1 2 3 4
 * B -> 2 3 5
 * C -> 4 5 6
 * D -> 5 6 7 8
 * E -> 1 4 6
 * result: [A, D]
 */
namespace 猎头简历问题 {
vector<char> solution(map<char, vector<int>> &hrs) {
  vector<char> res;
  unordered_set<int> resumes, record;
  for (auto &hr : hrs) {
    for (auto &resume : hr.second)
      resumes.insert(resume);
  }
  while (record.size() != resumes.size()) {
    int max_num = 0;
    auto max_hr = hrs.begin();
    for (auto it = hrs.begin(); it != hrs.end(); it++) {
      int num = 0;
      for (auto &resume : it->second)
        if (record.find(resume) == record.end())
          num++;
      if (num > max_num) {
        max_num = num;
        max_hr = it;
      }
    }
    res.push_back(max_hr->first);
    for (auto &resume : max_hr->second) {
      record.insert(resume);
    }
  }
  return res;
}
void test() {
  map<char, vector<int>> hrs;
  hrs['A'] = {1, 2, 3, 4};
  hrs['B'] = {2, 3, 5};
  hrs['C'] = {4, 5, 6};
  hrs['D'] = {5, 6, 7, 8};
  hrs['E'] = {1, 4, 6};
  auto res = solution(hrs);
  for (auto r : res)
    cout << r << endl;
}
} // namespace 猎头简历问题