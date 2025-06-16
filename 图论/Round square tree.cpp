#include <bits/stdc++.h>
using namespace std;

int h1[200005] = {0};
int h2[200005] = {0};
int ne[1000005] = {0};
int e[1000005] = {0};
int W[1000005] = {0};
int dfn[200005] = {0};
int low[200005] = {0};
int fa[200005] = {0};
int fw[200005] = {0};
int fe[200005] = {0};
int dis[200005] = {0};
int C[200005] = {0};
int dep[200005] = {0};
int st[200005][20] = {{0}};
int pre[200005] = {0};
int id = 1, tot = 0, cnt;
int A, B;

void dfs(int t, int s)
{
	dep[t] = dep[s] + 1;
	st[t][0] = s;
	for (int i = 1; i < 20; i++) {
		st[t][i] = st[st[t][i - 1]][i - 1];
	}
	for (int b = h2[t]; b != 0; b = ne[b]) {
		int c = e[b];
		if (c == s) continue;
		pre[c] = pre[t] + W[b];
		dfs(c, t);
	}
}

int getLCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 19; i >= 0; i--) {
		if (dep[st[u][i]] >= dep[v]) {
			u = st[u][i];
		}
	}
	if (u == v) return u;
	for (int i = 19; i >= 0; i--) {
		if (st[u][i] != st[v][i]) {
			u = st[u][i], v = st[v][i];
		}
	}
	A = u, B = v;
	return st[u][0];
}

void add(int *h, int a, int b, int w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
}

void build(int st, int ed, int weight)
{
	int sum = weight;
	for (int node = ed; node != st; node = fa[node]) {
		dis[node] = sum;
		sum += fw[node];
	}
	dis[st] = C[st] = sum;
	cnt++;
	add(h2, cnt, st, 0);
	add(h2, st, cnt, 0);
	for (int node = ed; node != st; node = fa[node]) {
		C[node] = sum;
		add(h2, cnt, node, min(dis[node], sum - dis[node]));
		add(h2, node, cnt, min(dis[node], sum - dis[node]));
	}
}

void Tarjan(int t, int edgId)
{
	dfn[t] = low[t] = ++tot;
	for (int b = h1[t]; b != 0; b = ne[b]) {
		int c = e[b];
		if (dfn[c] == 0) {
			fa[c] = t, fw[c] = W[b], fe[c] = b;
			Tarjan(c, b);
			low[t] = min(low[t], low[c]);
			if (low[c] > dfn[t]) {
				add(h2, c, t, W[b]);
				add(h2, t, c, W[b]);
			}
		}
		else if (b != (edgId ^ 1)) low[t] = min(low[t], dfn[c]);
	}

	for (int b = h1[t]; b != 0; b = ne[b]) {
		int c = e[b];
		if (dfn[c] > dfn[t] && fe[c] != b) {
			build(t, c, W[b]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, q;
	cin >> n >> m >> q;
	cnt = n;

	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		add(h1, u, v, w);
		add(h1, v, u, w);
	}

	Tarjan(1, 0);
	dfs(1, 0);
	
	while (q--) {
		cin >> u >> v;
		int lca = getLCA(u, v);

		if (lca <= n) {
			cout << pre[u] + pre[v] - 2 * pre[lca] << '\n';
		}
		else {
			int len = abs(dis[A] - dis[B]);
			int tmp = min(len, C[A] - len);
			cout << pre[u] + pre[v] + tmp - pre[A] - pre[B] << '\n';
		}
	}

	return 0;
}