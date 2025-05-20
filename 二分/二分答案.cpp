/*
    二分答案模板
    二分答案中，最为关键的就是实现 check 函数，理清随着规模的增大，check 如何具有单调性
    时间复杂度 O(logn) * check
*/
#include <bits/stdc++.h>

bool check(int i) {
    return true;
}

int find(int l, int r) {
    int ret = -1;
    while(l <= r) {
        int mid = l + r >> 1;
        if(check(mid))
            ret = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ret;
}