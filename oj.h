#include "public.h"

// 本文件主要记录一些在线编程中常见的一些code

//! 读取样例输入
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
namespace OJ1 {
void test()
{
    int m, n, num;
    while (cin >> m >> n) {
        vector<int> v;
        for (int i = 0; i < m; ++i) {
            cin >> num;
            v.push_back(num);
        }

        sort(v.begin(), v.end());

        map<string, int> ms;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            ms[s]++;
        }

        int max = 0;
        int min = 0;
        vector<int>::iterator ite = v.end();
        ite--;
        vector<int>::iterator itb = v.begin();

        vector<int> num;
        for (map<string, int>::iterator mit = ms.begin(); mit != ms.end(); ++mit) {
            num.push_back(mit->second);
        }

        sort(num.begin(), num.end());

        vector<int>::iterator nite = num.end();
        nite--;
        vector<int>::iterator nitb = num.begin();
        nitb--;

        for (; nite != nitb; --nite) {
            max += (*nite) * (*ite);
            min += (*nite) * (*itb);
            ite--;
            itb++;
        }

        cout << min << " " << max << endl;
    }
}
} // namespace OJ1
