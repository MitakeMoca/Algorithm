/*
    优点：当边带编号时非常有用，当 cnt 的初始值为奇数时，x xor 1 即为 x 的反边
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int cnt = -1; 
int nxt[N], head[N], to[N];

void init() {
    cnt = -1;
    memset(head, -1, sizeof(head));
}

// 增加一条边
void add(int u, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}

// 遍历 u 的出边
void loop_u(int u) {
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
    }
}