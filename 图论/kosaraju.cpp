#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> p(n + 1);
	vector<vector<int>> p2(n + 1);
	int u, v;

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		p[u].push_back(v);
		p2[v].push_back(u);
	}

	vector<bool> V(n + 1, false);
	vector<int> dfn;

	auto dfs1 = [&](auto &&self, int t) -> void {
		V[t] = true;
		for (auto i: p[t]) {
			if (V[i]) continue;
			self(self, i);
		}
		dfn.push_back(t);
	};

	vector<bool> V2(n + 1, false);
	vector<vector<int>> scc(n + 1);
	vector<int> to(n + 1);
	int tot = 0;
	auto dfs2 = [&](auto &&self, int t) -> void {
		scc[tot].push_back(t);
		to[t] = tot;
		V2[t] = true;
		for (auto i: p2[t]) {
			if (V2[i]) continue;
			self(self, i);
		}
	};

	for (int i = 1; i <= n; i++) {
		if (V[i] == false) dfs1(dfs1, i);
	}

	for (int i = n - 1; i >= 0; i--) {
		if (V2[dfn[i]] == false) {
			++tot;
			dfs2(dfs2, dfn[i]);
		}
	}

	vector<bool> vis(n + 1, false);
	cout << tot << '\n';
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		int now = to[i];
		sort(scc[now].begin(), scc[now].end());
		for (auto j: scc[now]) {
			cout << j << ' ';
			vis[j] = true;
		}
		cout << '\n';
	}

	return 0;
}