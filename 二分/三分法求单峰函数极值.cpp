/*
    三分法求单峰函数极值：强调严格单调性
*/

#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;

double f(double x) {
    return x;
}

double check(double l, double r) {
    while(fabs(r - l) > eps) {
        double mid1 = (2 * l + r) / 3;
        double mid2 = (l + 2 * r) / 3;
        if(f(mid1) > f(mid2))
            l = mid1;
        else
            r = mid2;
    }
    return l;
}