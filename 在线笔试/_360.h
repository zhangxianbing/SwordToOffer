/*
 * @Author: zhangxianbing
 * @Date: 2019-08-15 11:50:55
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-15 21:04:01
 * @Description: file content
 */
#pragma once
#include "../public.h"

/*
有一个城市需要修建，给你N个民居的坐标X,Y，问把这么多民居全都包进城市的话，城市所需最小面积是多少（注意，城市为平行于坐标轴的正方形）


输入描述:
第一行为N，表示民居数目（2≤N≤1000）

输出描述:
城市所需最小面积

输入例子1:
2
0 0
2 2

输出例子1:
4

输入例子2:
2
0 0
0 3

输出例子2:
9
*/
namespace _360T1 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int N;
  while (cin >> N) {
    long long X, Y, minX = INT32_MAX, maxX = INT32_MIN, minY = INT32_MAX,
                    maxY = INT32_MIN;
    while (N-- > 0) {
      cin >> X >> Y;
      minX = min(minX, X);
      maxX = max(maxX, X);
      minY = min(minY, Y);
      maxY = max(maxY, Y);
    }
    long long l = max(maxX - minX, maxY - minY);
    cout << l * l;
  }
  return 0;
}
}  // namespace _360T1

/*
圈地运动，就是用很多木棍摆在地上组成一个面积大于0的多边形～

小明喜欢圈地运动，于是他需要去小红店里面买一些木棍，期望圈出一块地来。小红想挑战一下小明，所以给小明设置了一些障碍。障碍分别是：

1.如果小明要买第i块木棍的话，他就必须把前i-1块木棍都买下来。

2.买了的木棍都必须用在圈地运动中。

那么请问小明最少买多少根木棍，才能使得木棍围成的图形是个面积大于0多边形呢？

输入描述:
第一行一个数n，表示木棍个数。
第二行n个数，第i个数表示第i个木棍的长度ai
1<=n<=10000
1<=ai<=10000

输出描述:
输出一个数，表示最少需要的木棍个数，如果无解输出-1

输入例子1:
3
6 8 10

输出例子1:
3

例子说明1:
用三根6，8，10的木棍可以组成一个直角三角形的图形。
*/
namespace _360T2 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;
  while (cin >> n) {
    int res = 0, sum = 0, maxV = INT32_MIN;
    bool flag = false;
    auto nums = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    for (auto num : nums) {
      res++;
      maxV = max(maxV, num);
      sum += num;
      if (sum - maxV > maxV) {
        flag = true;
        break;
      }
    }
    cout << (flag ? res : -1) << endl;
  }

  return 0;
}
}  // namespace _360T2

/*
[编程题]Bittttttts
时间限制：1秒

空间限制：65536K

现在有q个询问，每次询问想问你在[l,r]区间内，k进制表示中，k-1的数量最多的数是哪个数。比如当k=2时，9的二进制就是1001，那么他就有2个1.


输入描述:
第一行一个q，表示有q组询问。

接下来q行，每行三个整数k,l,r,分别表示进制数,查询的数字,以及查询的范围。

满足1<=q<=100000,2<=k<=16,1<=l<=r<=10^16

输出描述:
对于每组询问，输出答案。如果有多个答案，请输出最小的。

输入例子1:
1
8 1 100

输出例子1:
63
*/
namespace _360T3 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int q;
  while (cin >> q) {
    int k, l, r;
    cin >> k >> l >> r;
    int res = 0;
    while (res <= r) {
      res += res * (k - 1) + k - 1;
    }
    if (res < l) {
      res = l;
    }
    cout << res << endl;
  }

  return 0;
}
}  // namespace _360T3

/*
[编程题]看花
时间限制：2秒

空间限制：65536K

小明有一个花园，花园里面一共有m朵花，对于每一朵花，都是不一样的，小明用1～m中的一个整数表示每一朵花。

他很喜欢去看这些花，有一天他看了n次，并将n次他看花的种类是什么按照时间顺序记录下来。

记录用a[i]表示，表示第i次他看了a[i]这朵花。

小红很好奇，她有Q个问题,问[l,r]的时间内，小明一共看了多少朵不同的花儿，小明因为在忙着欣赏他的花儿，所以想请你帮他回答这些问题。


输入描述:
输入两个数n,m;(1<=n<=2000,1<=m<=100);分别表示n次看花，m表示一共有m朵花儿。

接下来输入n个数a[1]~a[n]，a[i]表示第i次，小明看的花的种类;

输入一个数Q(1<=Q<=1000000);表示小红的问题数量。

输入Q行
每行两个数l,r(1<=l<=r<=n);表示小红想知道在第l次到第r次，小明一共看了多少不同的花儿。

输出描述:
一共Q行

每一行输出一个数 表示小明在[l,r]的时间内看了多少种花。

输入例子1:
5 3
1 2 3 2 2
3
1 4
2 4
1 5

输出例子1:
3
2
3
*/
namespace _360T4 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<int> a(n), b(n);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) cin >> a[i];

    int Q;
    cin >> Q;
    vector<pair<int, int>> q(Q);
    for (int i = 0; i < Q; i++) cin >> q[i].first >> q[i].second;
  }
  return 0;
}
}  // namespace _360T4

/*
[编程题]Array
时间限制：1秒

空间限制：65536K

小红有两个长度为n的排列A和B。每个排列由[1,n]数组成，且里面的数字都是不同的。

现在要找到一个新的序列C，要求这个新序列中任意两个位置(i,j)满足:

如果在A数组中C[i]这个数在C[j]的后面，那么在B数组中需要C[i]这个数在C[j]的前面。

请问C序列的长度最长为多少呢？


输入描述:
第一行一个整数，表示N。

第二行N个整数，表示A序列。

第三行N个整数，表示B序列。

满足:N<=50000

输出描述:
输出最大的长度

输入例子1:
5
1 2 4 3 5
5 2 3 4 1

输出例子1:
4

例子说明1:
最长的C为1,3,4,5
*/
namespace _360T5 {
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int main() {
  int N;
  while (cin >> N) {
    vector<int> A(N), B(N);
    unordered_map<int, int> M;
    for (int i = 0; i < N; i++) cin >> A[i], M[A[i]] = N - i - 1;
    for (int i = 0; i < N; i++) cin >> B[i];
    // 寻找最长递增子序列
    int res = 1;
    vector<int> dp(N, 1);  // dp[i]表示以B[i]结尾的最长递增子序列长度
    for (int i = 0; i < N; i++) {
      for (int j = i; j >= 0; j--) {
        if (M[B[i]] > M[B[j]]) dp[i] = max(dp[i], dp[j] + 1);
      }
      res = max(res, dp[i]);
    }
    cout << res << endl;
  }

  return 0;
}
}  // namespace _360T5

/*
[编程题]魔法排列
时间限制：1秒

空间限制：65536K

众所周知，集合{1 2 3
…N}有N!种不同的排列，假设第i个排列为Pi且Pi,j是该排列的第j个数。将N个点放置在x轴上，第i个点的坐标为xi且所有点的坐标两两不同。对于每个排列（以Pi为例），可以将其视为对上述N个点的一种遍历顺序，即从第Pi,1个点出发，沿直线距离到达第Pi,2个点，再沿直线距离到达第Pi,3个点，以此类推，最后到达第Pi,N个点，将该路线的总长度定义为L(Pi)，那么所有N!种路线的总长度之和是多少，即L(P1)+L(P2)+L(P3)+...+L(PN!)的结果是多少？


输入描述:
第一行包含一个整数N，1≤N≤105。

第二行包含N个空格隔开的整数x1到xN，0≤x1<x2<x3<...<xN≤109。


输出描述:
输出L(P1)+L(P2)+L(P3)+...+L(PN!)对109+7取模后的结果。


输入例子1:
3
0 1 3

输出例子1:
24

例子说明1:
P1={1 2 3}，P2={1 3 2}，P3={2 1 3}，P4={2 3 1}，P5={3 1 2}，P6={3 2 1}；

L(P1)=3，L(P2)=5，L(P3)=4，L(P4)=5，L(P5)=4，L(P6)=3。
*/
namespace _360T6 {}  // namespace _360T6

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

/*
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
将长N*M厘米的矩形区域划分成N行M列（每行每列的宽度均为1厘米），在第i行第j列的位置上叠放Ai,j个边长为1厘米的正方体（1≤Ai,j≤100），所有正方体就组成了一个立体图形，每个正方体六个面中的一部分会被其它正方体遮挡，未被遮挡的部分的总面积即为该立体图形的表面积，那么该立体图形的表面积是多少平方厘米？
*/
namespace _360TEST1 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int N, M;
  while (cin >> N >> M) {
    vector<vector<int>> A(N, vector<int>(M));
    int m = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++) {
        cin >> A[i][j];
        m = max(m, A[i][j]);
      }
    int S = 2 * N * M;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++) {
        if (A[i][j] == 0) S -= 2;
        for (int k = 1; k <= m; k++) {
          if (i == 0 && A[i][j] >= k) S++;
          if (j == 0 && A[i][j] >= k) S++;
          if (A[i][j] >= k && (i + 1 >= N || A[i + 1][j] < k)) S++;
          if (A[i][j] < k && (i + 1 < N && A[i + 1][j] >= k)) S++;
          if (A[i][j] >= k && (j + 1 >= M || A[i][j + 1] < k)) S++;
          if (A[i][j] < k && (j + 1 < M && A[i][j + 1] >= k)) S++;
        }
      }
    cout << S << endl;
  }
  return 0;
}
}  // namespace _360TEST1

/*
序列重组
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
在一个古老的国度，这个国家的人并不懂得进位，但是对取模情有独钟，因此诞生了一个经典的问题，给出两个在m进制下含有n位的数字，你可以分别将这两个数各位上的数字重新排列，然后将两个数按位对应相加并分别对m取模，这样显然可以得到一个新的m进制下的n位数(可能存在前导0)，但是这个结果是不唯一的，问题来了，按照这样的操作，能够得到的最大的m进制下的数字是多少呢。

输入
输入第一行包含两个正整数n,m分别表示数字含有n位，和在m进制下。

输入第二行和第三行分别包含n个整数，中间用空格隔开，每个整数都在0到m-1之间。每行第i个数表示的是当前数第i位上的数字。

输出
输出包含n个数字，中间用空格隔开，表示得到的最大的数字，从高位到低位输出，如6在2进制下输出3位的结果是1
1 0。


样例输入
5 5
4 4 1 1 1
4 3 0 1 2
样例输出
4 4 3 3 2

提示
4 4 1 1 1 →1 4 1 4 1
4 3 0 1 2 →3 0 2 4 1（重排序列不唯一，数位相加后的数字为 4 4 3 8 2，对5取模即可
）
*/
namespace _360TEST2 {
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
  }
  return 0;
}
}  // namespace _360TEST2