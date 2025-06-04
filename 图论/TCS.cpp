#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc (lc | 1)

vector<int> p[100005];
long long A[100005] = {0};
int dep[100005] = {0};
int top[100005] = {0};
int son[100005] = {0};
int fa[100005] = {0};
int sz[100005] = {0};

int id[100005] = {0};
int to[100005] = {0};

long long sum[400005] = {0};
long long tag[400005] = {0};

int tot = 0;

void dfs1(int t, int s)
{
	dep[t] = dep[s] + 1;
	fa[t] = s;
	sz[t] = 1;

	for (auto i: p[t]) {
		if (i == s) continue;
		dfs1(i, t);
		sz[t] += sz[i];
		if (sz[son[t]] < sz[i]) son[t] = i;
	}
}

void dfs2(int t, int s)
{
	id[t] = ++tot;
	to[tot] = t;
	top[t] = s;

	if (son[t]) dfs2(son[t], s);

	for (auto i: p[t]) {
		if (i == son[t] || i == fa[t]) continue;
		dfs2(i, i); 
	}
}

void pushup(int t)
{
	sum[t] = sum[lc] + sum[rc];
}

void pushdown(int t, int l, int r)
{
	if (tag[t] != 0) {
		int m = l + r >> 1;
		tag[lc] += tag[t];
		tag[rc] += tag[t];
		sum[lc] += tag[t] * (m - l + 1);
		sum[rc] += tag[t] * (r - m);
		tag[t] = 0;
	}
}

void build(int t, int l, int r)
{
	if (l == r) {
		sum[t] = A[to[l]];
		return;
	}
	int m = l + r >> 1;
	build(lc, l, m);
	build(rc, m + 1, r);
	pushup(t);
}

void modify(int t, int l, int r, int x, int y, long long k)
{
	if (x <= l && y >= r) {
		sum[t] += (r - l + 1) * k;
		tag[t] += k;
		return;
	}
	pushdown(t, l, r);
	int m = l + r >> 1;
	if (x <= m) modify(lc, l, m, x, y, k);
	if (y > m) modify(rc, m + 1, r, x, y, k);
	pushup(t);
}

long long query(int t, int l, int r, int x, int y)
{
	if (x <= l && y >= r) return sum[t];
	int m = l + r >> 1;
	long long ans = 0;
	pushdown(t, l, r);
	if (x <= m) ans += query(lc, l, m, x, y);
	if (y > m) ans += query(rc, m + 1, r, x, y);
	return ans;
}

void modify_path(int u, int v, int n, long long k)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(1, 1, n, id[top[u]], id[u], k);
		u = fa[top[u]]; 
	}
	if (dep[u] < dep[v]) swap(u, v);
	modify(1, 1, n, id[v], id[u], k);
}

long long query_path(int u, int v, int n)
{
	long long ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += query(1, 1, n, id[top[u]], id[u]);
		u = fa[top[u]]; 
	}
	if (dep[u] < dep[v]) swap(u, v);
	ans += query(1, 1, n, id[v], id[u]);
	return ans;
}

void modify_tree(int t, int n, long long k)
{
	modify(1, 1, n, id[t], id[t] + sz[t] - 1, k);
}

long long query_tree(int t, int n)
{
	return query(1, 1, n, id[t], id[t] + sz[t] - 1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, r, P;
	cin >> n >> m >> r >> P;

	for (int i = 1; i <= n; i++)
		cin >> A[i];

	int u, v;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	dfs1(r, 0);
	dfs2(r, r);
	build(1, 1, n);

	int op;
	long long k;

	while (m--) {
		cin >> op;
		if (op == 1) {
			cin >> u >> v >> k;
			modify_path(u, v, n, k);
		}
		if (op == 2) {
			cin >> u >> v;
			cout << query_path(u, v, n) % P << '\n';
		}
		if (op == 3) {
			cin >> u >> k;
			modify_tree(u, n, k);
		}
		if (op == 4) {
			cin >> u;
			cout << query_tree(u, n) % P << '\n';
		}
	}
	return 0;
}