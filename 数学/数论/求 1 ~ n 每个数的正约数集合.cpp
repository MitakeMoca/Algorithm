/*
    倍数法求 n 的所有正约数
    时间复杂度：O(nlogn)
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> factor[500010];
void times(int n) {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n / i; j++)
            factor[i * j].push_back(i);
}