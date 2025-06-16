#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc (lc | 1)

vector<int> p[200005];
vector<int> np[200005];
multiset<int> st[200005];
stack<int> stk;
int dfn[200005] = {0};
int low[200005] = {0};
int W[200005] = {0};
int fa[200005] = {0};
int sz[200005] = {0};
int mn[4000005] = {0};
int son[200005] = {0};
int top[200005] = {0};
int dep[200005] = {0};
int inv[200005] = {0};
int id = 0, cnt = 0, n;

void Tarjan(int t)
{
	dfn[t] = low[t] = ++id;
	stk.push(t);

	for (auto i: p[t]) {
		if (dfn[i] == 0) {
			Tarjan(i);
			low[t] = min(low[t], low[i]);
			if (dfn[t] == low[i]) {
				int now;
				cnt++;
				do {
					now = stk.top();
					stk.pop();

					np[cnt].push_back(now);
					np[now].push_back(cnt);
				} while (now != i);

				np[t].push_back(cnt);
				np[cnt].push_back(t);
			}
		}
		else low[t] = min(low[t], dfn[i]);
	}
}

void dfs1(int t, int s)
{
	dep[t] = dep[s] + 1;
	fa[t] = s;
	sz[t] = 1;

	for (auto i: np[t]) {
		if (i == s) continue;
		dfs1(i, t);
		sz[t] += sz[i];
		if (sz[son[t]] < sz[i]) son[t] = i;
	}
}

void dfs2(int t, int s)
{
	top[t] = s;
	dfn[t] = ++id;
	inv[id] = t;
	if (son[t] != 0) dfs2(son[t], s);

	for (auto i: np[t]) {
		if (i == fa[t] || i == son[t]) continue;
		dfs2(i, i);
	}
}

void pushup(int t)
{
	mn[t] = min(mn[lc], mn[rc]);
}

void build(int t, int l, int r)
{
	if (l == r) {
		mn[t] = W[inv[l]];
		return;
	}
	int m = l + r >> 1;
	build(lc, l, m);
	build(rc, m + 1, r);
	pushup(t);
}

int query(int t, int l, int r, int x, int y)
{
	if (x <= l && y >= r) return mn[t];
	int ans = 2e9, m = l + r >> 1;
	if (x <= m) ans = min(ans, query(lc, l, m, x, y));
	if (y > m) ans = min(ans, query(rc, m + 1, r, x, y));
	return ans;
}

void modify(int t, int l, int r, int pos, int k)
{
	if (l == r) {
		mn[t] = k;
		return;
	}
	int m = l + r >> 1;
	if (pos <= m) modify(lc, l, m, pos, k);
	else modify(rc, m + 1, r, pos, k);
	pushup(t);
}

int queryPath(int u, int v)
{
	int ans = 2e9;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans = min(ans, query(1, 1, cnt, dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	ans = min(ans, query(1, 1, cnt, dfn[u], dfn[v]));
	if (u > n) ans = min(ans, W[fa[u]]);
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int m, q;
	cin >> n >> m >> q;
	cnt = n;

	for (int i = 1; i <= n; i++) {
		cin >> W[i];
	}

	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		p[v].push_back(u);
		p[u].push_back(v);
	}

	Tarjan(1);
	id = 0;

	dfs1(1, 0);
	dfs2(1, 1);

	for (int i = 1; i <= n; i++) {
		if (fa[i] != 0) st[fa[i]].insert(W[i]);
	}
	for (int i = n + 1; i <= cnt; i++) {
		W[i] = *st[i].begin();
	}

	build(1, 1, cnt);
	char op;
	while (q--) {
		cin >> op >> u >> v;
		if (op == 'C') {
			modify(1, 1, cnt, dfn[u], v);
			if (fa[u] != 0) {
				st[fa[u]].extract(W[u]);
				st[fa[u]].insert(v);
				W[fa[u]] = *st[fa[u]].begin();
				modify(1, 1, cnt, dfn[fa[u]], W[fa[u]]);
			}
			W[u] = v;
		}
		else {
			cout << queryPath(u, v) << '\n';
		}
	}

	return 0;
}