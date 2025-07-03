#include <bits/stdc++.h>
using namespace std;

int dfn[200005] = {0};
int inv[200005] = {0};
int fa[200005] = {0};
int uni[200005] = {0};
int mn[200005] = {0};
int sdom[200005] = {0};
int idom[200005] = {0};
int ans[200005] = {0};
int tot = 0;

struct Graph {
	int h[200005];
	int e[300005];
	int ne[300005];
	int id = 0;

	void add(int a, int b)
	{
		e[++id] = b;
		ne[id] = h[a];
		h[a] = id;
	}
}p1, p2, p3;

void dfs(int t)
{
	dfn[t] = ++tot;
	inv[tot] = t;
	for (int b = p1.h[t]; b != 0; b = p1.ne[b]) {
		int c = p1.e[b];
		if (dfn[c] != 0) continue;
		fa[c] = t;
		dfs(c);
	}
}

int find(int x)
{
	if (x == uni[x]) return x;
	int ans = find(uni[x]);
	if (dfn[sdom[mn[uni[x]]]] < dfn[sdom[mn[x]]]) {
		mn[x] = mn[uni[x]];
	}
	return uni[x] = ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		p1.add(u, v);
		p2.add(v, u);
	}

	dfs(1);
	for (int i = 1; i <= n; i++)
		uni[i] = sdom[i] = mn[i] = i;
	for (int i = tot; i > 1; i--) {
		int a = inv[i];
		for (int b = p2.h[a]; b != 0; b = p2.ne[b]) {
			int c = p2.e[b];
			if (dfn[c] == 0) continue;
			find(c);
			if (dfn[sdom[a]] > dfn[sdom[mn[c]]]) {
				sdom[a] = sdom[mn[c]]; // mn[c] 代表祖先中 dfn 最小的 sdom[c]
			}
		}
		uni[a] = fa[a];
		p3.add(sdom[a], a);
		a = fa[a];
		for (int b = p3.h[a]; b != 0; b = p3.ne[b]) {
			int c = p3.e[b];
			find(c);
			if (a == sdom[mn[c]]) {
				idom[c] = a;
			}
			else {
				idom[c] = mn[c];
			}
		}
		p3.h[a] = 0;
	}

	for (int i = 2; i <= tot; i++) {
		int a = inv[i];
		if (sdom[a] != idom[a]) idom[a] = idom[idom[a]];
	}

	for (int i = tot; i > 1; i--) {
		int a = inv[i];
		ans[idom[a]] += ++ans[a];
	}
	ans[1]++;

	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
	}

	return 0;
}