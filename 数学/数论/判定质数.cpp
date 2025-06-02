/*
    判定 n 是不是素数
    时间复杂度：O(sqrt(n))
*/
#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if(n < 2)
        return false;
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0)
            return false;
    return true;
}