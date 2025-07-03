#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, e;
	cin >> n >> m >> e;

	vector<vector<int>> p(n + 1);
	int u, v;
	for (int i = 0; i < e; i++) {
		cin >> u >> v;
		p[u].push_back(v);
	}

	vector<int> match(m + 1, 0);
	vector<bool> vis(m + 1, 0);

	auto dfs = [&](auto &&self, int t) -> bool {
		for (auto i: p[t]) {
			if (vis[i]) continue;
			vis[i] = true;
			if (match[i] == 0 || self(self, match[i])) {
				match[i] = t;
				return true;
			}
		}
		return false;
	};

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		fill(vis.begin(), vis.end(), false);
		if (dfs(dfs, i)) ans++;
	}
	cout << ans << '\n';
	return 0;
}