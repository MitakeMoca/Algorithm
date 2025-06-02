/*
    试除法求 n 的所有正约数
    推论：一个正整数的约数个数上界为 2 * sqrt(n)
    时间复杂度：O(sqrt(n))
*/
#include <bits/stdc++.h>
using namespace std;

int factor[1600], m = 0;
void divide(int n) {
    for(int i = 1; i * i <= n; i++) 
        if(n % i == 0) {
            factor[++m] = i;
            if(i != n / i)
                factor[++m] = n / i;
        }
}