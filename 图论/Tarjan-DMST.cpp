#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e10;

struct DSU {
	vector<int> fa;

	DSU(int n) {
		fa.resize(n + 1);
		iota(fa.begin(), fa.end(), 0);
	}

	int find(int x)
	{
		if (x == fa[x]) return x;
		return fa[x] = find(fa[x]);
	}

	void merge(int u, int v)
	{
		u = find(u), v = find(v);
		fa[v] = u;
	}

	bool isSame(int u, int v)
	{
		u = find(u), v = find(v);
		return u == v;
	}
};

struct LeftTree {
	int dis[200005] = {0};
	long long W[200005] = {0};
	long long tag[200005] = {0};
	int lc[200005] = {0};
	int rc[200005] = {0};
	int from[200005] = {0};
	int to[200005] = {0};
	int rt[2005] = {0};
	int id = 0;

	LeftTree()
	{
		dis[0] = -1;
	}

	int newnode(long long x, int st, int ed)
	{
		W[++id] = x;
		to[id] = ed;
		from[id] = st;
		return id;
	}

	void pushdown(int x)
	{
		W[lc[x]] += tag[x];
		W[rc[x]] += tag[x];
		tag[lc[x]] += tag[x];
		tag[rc[x]] += tag[x];
		tag[x] = 0;
	}

	int merge(int x, int y)
	{
		if (x == 0 || y == 0) return x + y;
		pushdown(x);
		pushdown(y);
		if (W[x] > W[y]) swap(x, y);
		rc[x] = merge(rc[x], y);

		if (dis[lc[x]] < dis[rc[x]]) swap(lc[x], rc[x]);
		dis[x] = dis[rc[x]] + 1;
		return x;
	}

	int del(int x)
	{
		pushdown(x);
		return merge(lc[x], rc[x]);
	}
} leftTree;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, r;
	cin >> n >> m >> r;

	vector<vector<pair<int, long long>>> p(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back({v, w});
	}
	for (int i = 1; i < n; i++) {
		p[i].push_back({i + 1, INF});
	}
	p[n].push_back({1, INF});

	for (int i = 1; i <= n; i++) {
		for (auto [node, weight]: p[i]) {
			leftTree.rt[node] = leftTree.merge(leftTree.rt[node], leftTree.newnode(weight, i, node));
		}
	}

	DSU dsu(2 * n);
	stack<int> stk;
	vector<bool> instk(2 * n + 1, false);
	stk.push(r);
	instk[r] = true;

	int id = n;
	long long ans = 0;

	while (leftTree.rt[stk.top()] != 0) {
		int a = stk.top();
		int node = leftTree.from[leftTree.rt[a]];

		int fa = dsu.find(node);
		if (fa == a) {
			leftTree.rt[a] = leftTree.del(leftTree.rt[a]);
			continue;
		}
		if (instk[fa] == false) {
			stk.push(fa);
			instk[fa] = true;
			continue;
		}

		int p = ++id;
		while (instk[fa]) {
			int now = stk.top();
			stk.pop();
			instk[now] = false;
			dsu.merge(p, now);
			long long tmp = leftTree.W[leftTree.rt[now]];
			leftTree.tag[leftTree.rt[now]] -= tmp;

			if (!dsu.isSame(leftTree.to[leftTree.rt[now]], r)) ans += tmp;
			leftTree.rt[now] = leftTree.del(leftTree.rt[now]);
			leftTree.rt[p] = leftTree.merge(leftTree.rt[p], leftTree.rt[now]);
		}
		stk.push(p);
		instk[p] = true;
	}

	if (ans > INF) ans = -1;

	cout << ans << '\n';
	return 0;
}