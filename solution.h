#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace T1 {
vector<string> Permutation1(string str)
{
    vector<string> res;
    sort(str.begin(), str.end());
    __util(res, str, 0);
    return res;
}

void __util(vector<string>& res, string& str, int k)
{
    if (k == int(str.size()) - 1) {
        res.push_back(str);
        return;
    }
    for (int i = k; i < int(str.size()); i++) {
        if (i == k || str[i] != str[i - 1]) {
            swap(str[k], str[i]);
            __util(res, str, k + 1);
            swap(str[k], str[i]);
        }
    }
}

vector<string> Permutation(string str)
{
    vector<string> res;
    int n = str.size();
    sort(str.begin(), str.end());

    do {
        res.push_back(str);
        int j = n - 1;
        while (j - 1 >= 0 && str[j - 1] >= str[j])
            j--; // 注意>=
        if (j == 0)
            break;
        int i = j;
        while (str[i] > str[j - 1])
            i++;
        swap(str[i - 1], str[j - 1]);
        sort(str.begin() + j, str.end());
        res.push_back(str);
    } while (true);
    return res;
}

void test()
{
    string str = "abc";
    auto res = Permutation(str);
}
} // namespace T1
