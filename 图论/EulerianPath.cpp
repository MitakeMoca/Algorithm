#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> p(n + 1);
	int u, v;
	vector<int> din(n + 1, 0), dout(n + 1, 0);

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		p[u].push_back(v);
		dout[u]++, din[v]++;
	}

	int st = 1, l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		if (din[i] != dout[i]) {
			if (din[i] - dout[i] == 1) {
				l++;
			}
			else if (dout[i] - din[i] == 1) {
				r++, st = i;
			}
			else {
				cout << "No\n";
				return;
			}
		}
	}

	if (l != r || (l != 1 && l != 0)) {
		cout << "No\n";
		return;
	}

	for (int i = 1; i <= n; i++) {
		sort(p[i].begin(), p[i].end());
	}

	stack<int> stk;
	vector<int> cur(n + 1, 0);

	auto dfs = [&](auto &&self, int t) -> void {
		for (int i = cur[t]; i < p[t].size(); i = cur[t]) {
			cur[t] = i + 1;
			self(self, p[t][i]);
		}
		stk.push(t);
	};

	dfs(dfs, st);

	while (!stk.empty()) {
		cout << stk.top() << ' ';
		stk.pop();
	}
	cout << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}