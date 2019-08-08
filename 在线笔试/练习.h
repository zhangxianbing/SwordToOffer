#include "../public.h"
/*
* 常用头文件
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
* 数据结构
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
*
using namespace std;
 */

// 例：采购单（京东2017秋招真题）https://exercise.acmcoder.com/online/online_judge_ques?ques_id=3378&konwledgeId=41
// 这道题算法简单，主要难点是处理样例的输入
/*
样例输入(不含虚线):
---------------------
5 3
4 2 1 10 5
apple
orange
mango
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
---------------------
 */
namespace EX1 {
void test() {
  int m, n;
  while (cin >> m >> n) {
    vector<int> p;
    for (int i = 0; i < m; i++) {
      int t;
      cin >> t;
      p.push_back(t);
    }
    sort(p.begin(), p.end());
    auto pb = p.begin();
    auto pe = p.end();
    pe--;

    unordered_map<string, int> hm;
    for (int i = 0; i < n; i++) {
      string t;
      cin >> t;
      hm[t]++;
    }
    vector<int> b;
    for (auto it : hm) b.push_back(it.second);
    sort(b.begin(), b.end());

    int Max = 0, Min = 0;
    for (int i = int(b.size()) - 1; i >= 0; i--) {
      Max += (*pe) * b[i];
      Min += (*pb) * b[i];
      pe--;
      pb++;
    }
    cout << Min << " " << Max << endl;
  }
}
}  // namespace EX1

// 集合（京东2017秋招真题）https://exercise.acmcoder.com/online/online_judge_ques?ques_id=3374&konwledgeId=41
namespace EX2 {
void test() {
  int n, m;
  while (cin >> m >> n) {
    int t;
    set<int> S;
    for (int i = 0; i < m; i++) cin >> t, S.insert(t);
    for (int i = 0; i < n; i++) cin >> t, S.insert(t);
    vector<int> V;
    for (auto it : S) V.push_back(it);
    sort(V.begin(), V.end());
    for (int i = 0; i < int(V.size()) - 1; i++) cout << V[i] << " ";
    cout << V.back() << endl;
  }
}
}  // namespace EX2

// 字典序（今日头条2017秋招真题）
// https://exercise.acmcoder.com/online/online_judge_ques?ques_id=3341&konwledgeId=158
namespace EX3 {}  // namespace EX3
