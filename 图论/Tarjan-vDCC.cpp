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
		if (u == v) continue;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	vector<int> dfn(n + 1, 0), low(n + 1);
	stack<int> stk;
	vector<vector<int>> vDcc(n + 1);
	int id = 0, tot = 0, rt = 0;

	auto dfs = [&](auto &&self, int t) -> void {
		dfn[t] = low[t] = ++id;

		if (p[t].size() == 0) {
			++tot;
			vDcc[tot].push_back(t);
			return;
		}

		stk.push(t);
		int child = 0;
		for (auto i: p[t]) {
			if (dfn[i] == 0) {
				self(self, i);
				low[t] = min(low[t], low[i]);
				if (low[i] >= dfn[t]) {
					++tot;
					int now;

					do {
						now = stk.top();
						stk.pop();

						vDcc[tot].push_back(now);
					} while (now != i);
					vDcc[tot].push_back(t);
				}
			}
			else low[t] = min(low[t], dfn[i]);
		}
	};

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0) {
			rt = i;
			dfs(dfs, i);
		}
	}

	cout << tot << '\n';
	for (int i = 1; i <= tot; i++) {
		cout << vDcc[i].size();
		for (auto j: vDcc[i]) {
			cout << ' ' << j;
		}
		cout << '\n';
	}

	return 0;
}