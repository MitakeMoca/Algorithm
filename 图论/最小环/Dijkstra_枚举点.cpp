/*
    给定一张有向图，求图中的最小环
    O(n*(n + m)log(n))
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2005, M = 5005;
const int INF = 0x3f3f3f3f;
int head[N], cnt = -1, nxt[M], to[M], weight[M], from[M];
int ans = INF;

void add(int u, int v, int w) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
    weight[cnt] = w;
    from[cnt] = u;
}

struct element {
    int node, value;
    element(int node_, int value_) :
        node(node_), value(value_){}

    // 小根堆
    bool operator < (const element &other) const {
        return value > other.value;
    }
};
int dis[N][N], vis[N][N];
void dijkstra(int s) {
    priority_queue<element> q;
    // 压入起点
    q.push(element(s, 0));
    while(!q.empty()) {
        element k = q.top();
        q.pop();
        if(vis[s][k.node])
            continue;
        vis[s][k.node] = true;
        dis[s][k.node] = k.value;
        for(int i = head[k.node]; ~i; i = nxt[i]) 
            q.push(element(to[i], weight[i] + k.value));
    }
}

void dijkstra_cycle(int n, int m) {
    memset(dis, 0x3f, sizeof(dis));
    // 对所有点跑一个 dijkstra
    for(int i = 1; i <= n; i++)
        dijkstra(to[i]);
    for(int i = 0; i < m; i++)
        ans = min(ans, weight[i] + dis[to[i]][from[i]]);
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }

    dijkstra_cycle(n, m);

    return 0;
}