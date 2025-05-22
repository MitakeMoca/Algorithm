/*
    当直接对整个数组进行二分会超时，而需要一个与答案区间长度适配的算法时，我们可以使用倍增
    比如假如每次输入一个 T，求满足 sum[1 : k] <= T 的最大的 k
    假如这个 T 每次都很小，导致用 log(n) 的二分方法得到的 k 也很小，结果还不如遍历
    此时就可以使用倍增法
    O(logk)
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int a[N], S[N];

int binary_lifting(int T) {
    int p = 1, k = 0, sum = 0;
    while(p) {
        // 计算 A 数组中 k 之后的 p 个元素之和
        if(sum + S[k + p] - S[k] <= T)
            sum += S[k + p] - S[k], k += p, p *= 2;
        else
            p /= 2;
    }
    return k;
}