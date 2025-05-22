/*
    利用归并排序求逆序对数
    时间复杂度：O(nlogn)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

int a[N], b[N];

ll mergeCount(int l, int mid, int r) {
	ll cnt = 0;
    int i = l, j = mid + 1;
    for(int k = l; k <= r; k++) 
        if(j > r || i < mid + 1 && a[i] <= a[j])
            b[k] = a[i++];
        else
            b[k] = a[j++], cnt += mid - i + 1;
    
    for(int k = l; k <= r; k++)
        a[k] = b[k];
	return cnt;
} 

ll mergeSort(int l, int r) {
    if(l < r) {
        int mid = l + r >> 1;
        return mergeSort(l, mid) + mergeSort(mid + 1, r) + mergeCount(l, mid, r);
    }
	return 0;
}