/*
    线性素数筛
    最后 prime[1 ~ m] 保存着 1 ~ n 范围内的所有素数
    时间复杂度：O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int v[N], prime[N], m;

void primes(int n) {
    memset(v, 0, sizeof(v));
    m = 0;
    for(int i = 2; i <= n; i++) {
        if(v[i] == 0)
            v[i] = i, prime[++m] = i;
        
        for(int j = 1; j <= m; j++) {
            if(prime[j] > v[i] || prime[j] > n / i)
                break;
            v[i * prime[j]] = prime[j];
        }
    }
}