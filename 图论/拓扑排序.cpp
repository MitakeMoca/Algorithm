/*
    基于 bfs 的拓扑排序算法
    拓扑排序：排出一个节点序，使得所有边都从前面的结点指向后面的结点
    调用 topo_logic 后，a[1 ~ n] 就是拓扑序
    时间复杂度：O(n + m)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int cnt = -1; 
int nxt[N], head[N], to[N];
int deg[N], n, a[N], cnt;

void init() {
    cnt = -1;
    memset(head, -1, sizeof(head));
}

// 增加一条边
void add(int u, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
    deg[v]++;
}

void topo_logic() {
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(deg[i] == 0)
            q.push(i);
    while(q.size()) {
        int x = q.front();
        q.pop();
        a[++cnt] = x;
        for(int i = head[x]; ~i; i = nxt[i]) {
            int y = to[i];
            if(--deg[y] == 0)
                q.push(y);
        }
    }
}