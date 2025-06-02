/*
    树的重心是删除该点后，最大连通块的大小最小
    时间复杂度：O(n)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int cnt = -1; 
int nxt[N], head[N], to[N];
int vis[N], sz[N], n;

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

int ans, pos;
void dfs(int x) {
    vis[x] = sz[x] = 1;
    int max_part = 0;
    for(int i = head[i]; ~i; i = nxt[i]) {
        int y = to[i];
        if(vis[y])
            continue;
        dfs(y);
        sz[x] += sz[y];
        max_part = max(max_part, sz[y]);
    }
    max_part = max(max_part, n - sz[x]);
    if(max_part < ans) {
        ans = max_part;
        pos = x;
    }
}