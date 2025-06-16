#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> p(n + 1);
	int u, v;

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		p[u].push_back(v);
	}

	vector<int> dfn(n + 1, 0);
	vector<int> low(n + 1, 0);
	vector<vector<int>> scc(n + 1);
	vector<bool> instk(n + 1, false);
	stack<int> stk;
	int id = 0, tot = 0;

	auto dfs = [&](auto &&self, int t) -> void {
		dfn[t] = low[t] = ++id;
		instk[t] = true;
		stk.push(t);

		for (auto i: p[t]) {
			if (dfn[i] == 0) {
				self(self, i);
				low[t] = min(low[t], low[i]);
			}
			else if (instk[i]) {
				low[t] = min(low[t], dfn[i]);
			}
		}

		if (low[t] == dfn[t]) {
			int now;
			++tot;
			do {
				now = stk.top();
				instk[now] = false;
				stk.pop();

				scc[tot].push_back(now);
			}while (now != t);
		}
	};

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0) {
			dfs(dfs, i);
		}
	}
	int ans = 0;

	for (int i = 1; i <= tot; i++) {
		if (scc[i].size() > 1) ans++;
	}
	cout << ans << '\n';
	return 0;
}