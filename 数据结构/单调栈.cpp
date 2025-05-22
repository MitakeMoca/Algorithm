/*
    求 i 之后第一个大于 a[i] 的元素位置
    O(n)
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 5;

int stk[N], top = -1, a[N], ans[N];

void push(int i) {
    while(top >= 0 && a[stk[top]] < a[i])
        ans[stk[top--]] = i;
    stk[++top] = i;
}