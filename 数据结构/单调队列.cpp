/*
    单调队列可以用来求解每 k 个连续数中的最大值，分为三步：
        1. 判断队头决策与 i 的距离，处理队头 
        2. 不断删除队尾决策，直到队尾对应的 a 值大于 a[i]（因为我 a[i] 又比你大又比你靠后，你肯定什么用也没有）
        3. 将 i 插入队尾
        4. 此时队头就对应着右端点为 i 时左端点 j 的最优选择
    O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

// q 数组里存的都是下标
int q[N], l, r = -1, a[N];
int n, k;

int enqueue(int i) {
    while(l <= r && q[l] <= i - k)
        l++;
    while(l <= r && a[q[r]] <= a[i])
        r--;
    q[++r] = i;
    return q[l];
}