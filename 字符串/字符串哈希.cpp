/*
    字符串哈希模板，支持计算哈希和求 [l, r] 的 hash 值两种操作
    注意字符串数组和前缀哈希值数组都从下标 1 开始
*/

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int P = 131;
const int N = 2e5;
// 字符串和 h 数组都从 1 开始
ull p[N], h[N];
char s[N];

// 预处理 hash 函数的前缀和
void init(int n) {
	p[0] = 1, h[0] = 0;
	for(int i = 1; i <= n; i++) {
		p[i] = p[i - 1] * P;
		h[i] = h[i - 1] * P + s[i]; 
	}
}

// 计算 s[l ~ r] 的 hash 值
ull get(int l, int r) {
	return h[r] - h[l - 1] * p[r - l + 1];
}