/*
    求 a ^ b % p
    时间复杂度：O(logb)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll quickPow(ll a, ll b, ll c) {
    ll ret = 1;
    while(b) {
        if(b & 1)
            ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}