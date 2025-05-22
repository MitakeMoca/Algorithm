/*
    该模板中数组下标应该从 0 开始，但是查找顺序统计量输入的 k 应该从 1 开始
    平均时间复杂度：O(n)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int a[N], n;

int quick_select(int l, int r, int k) {
    if(l == r)
        return a[l];
    int pivot_index = l + rand() % (r - l + 1);
    int pivot = a[pivot_index];
    swap(a[pivot_index], a[r]);

    int i = l;
    for (int j = l; j < r; ++j) 
        if (a[j] <= pivot) 
            swap(a[i++], a[j]);

    swap(a[i], a[r]);

    int count = i - l + 1;
    if (k == count) return a[i];
    else if (k < count) return quick_select(l, i - 1, k);
    else return quick_select(i + 1, r, k - count);
}

int get_kth(int k) {
    return quick_select(0, n - 1, k);
}