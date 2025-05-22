/*
    KMP 算法
    时间复杂度 O(n + m)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int nxt[N], n, m;
// P 是模式串，S 是原串
char P[N], S[N];

// nxt 数组，以及字符串都从 1 开始
void pre() {
	nxt[1] = 0;
	int j = 0;
	for(int i = 1; i < m ;i++) {
		while(j > 0 && P[j + 1] != P[i + 1])
			j = nxt[j];
		if(P[j + 1] == P[i + 1])
			j++;
		nxt[i + 1] = j; 
	}
}

void kmp() {
	int j = 0;
	for(int i = 0; i < n ;i++) {
		while(j > 0 && P[j + 1] != S[i + 1])
			j = nxt[j];
		if(P[j + 1] == S[i + 1])
			j++;
		if(j == m)
			printf("%d ", i + 1 - m + 1), j = nxt[j];
	}
}

int main() {
    scanf("%s", S + 1);
    scanf("%s", P + 1);
    n = strlen(S + 1);
    m = strlen(P + 1);
    pre();
    kmp();
}