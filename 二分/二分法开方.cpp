/*
    使用二分法求出 sqrt(n) 的整数部分
    时间复杂度 O(logn)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll my_sqrt(ll n) {
    ll l = 0, r = n;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (mid * mid <= n) 
            l = mid;
        else 
            r = mid;
    }
    return l;
}