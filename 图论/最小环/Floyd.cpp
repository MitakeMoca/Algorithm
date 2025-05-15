/*
    给定一张无向图，求图中一个至少包含 3 个点的最小环
    O(n^3)
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 105;
// 如果 INF 用 0x3f3f3f3f 的话，三个 INF 相加就会溢出
const int INF = 1e8;
int ans = INF;
int d[N][N], w[N][N];

void floyd(int n) {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i < k; i++)
            for(int j = i + 1; j < k; j++)
                ans = min(ans, d[i][j] + w[j][k] + w[k][i]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i != j)
                w[i][j] = INF;

    for(int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        w[u][v] = w[v][u] = min(w[u][v], c);
    }

    memcpy(d, w, sizeof w);
    floyd(n);

    if(ans == INF) cout << "No solution." << endl;
    else cout << ans << endl;
}