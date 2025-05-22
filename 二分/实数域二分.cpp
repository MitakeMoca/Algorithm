/*
    有两种实现方式：
        一种是使用 eps，当要求保留 k 位小数时，eps = 10^-(k+2)
        另一种是采用固定循环次数
*/
#include <bits/stdc++.h>
using namespace std;
double eps = 1e-10;

bool check(double i) {
    return true;
}

double find1(double l, double r) {
    while(fabs(l - r) < eps) {
        double mid = (l + r) / 2.0;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }
    return l;
}

double find2(double l, double r) {
    for(int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }
    return l;
}