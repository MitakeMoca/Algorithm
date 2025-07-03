#include <bits/stdc++.h>
using namespace std;

int getNode(int a, int f, int n)
{
	return a + f * n;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> p(2 * n + 1);
	int a, b, c, d;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c >> d;
		int u, v;
		u = getNode(a, b ^ 1, n);
		v = getNode(c, d, n);
		p[u].push_back(v);
		u = getNode(a, b, n);
		v = getNode(c, d ^ 1, n);
		p[v].push_back(u);
	}

	vector<int> dfn(2 * n + 1), low(2 * n + 1);
	vector<bool> instk(2 * n + 1, false);
	vector<int> scc(2 * n + 1);
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
			else if (instk[i]) low[t] = min(low[t], dfn[i]);
		}

		if (low[t] == dfn[t]) {
			int now;
			++tot;

			do {
				now = stk.top();
				stk.pop();
				instk[now] = false;
				scc[now] = tot;
			} while (now != t);
		}
	};

	for (int i = 1; i <= 2 * n; i++) {
		if (dfn[i] == 0) dfs(dfs, i);
	}

	for (int i = 1; i <= n; i++) {
		if (scc[i] == scc[i + n]) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}

	cout << "POSSIBLE\n";
	vector<int> ans(n + 1);
	for (int i = 1; i <= n; i++) {
		if (scc[i] > scc[i + n]) ans[i] = 1;
		else ans[i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
	}
	return 0;
}