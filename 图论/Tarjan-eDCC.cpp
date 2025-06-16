#include <bits/stdc++.h>
using namespace std;

int h[500005] = {0};
int e[4000005] = {0};
int ne[4000005] = {0};
int id = 1;

void add(int a, int b)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
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
		add(u, v);
		add(v, u);
	}

	vector<int> dfn(n + 1, 0), low(n + 1);
	vector<vector<int>> eDcc(n + 1);
	stack<int> stk;
	int nid = 0, tot = 0;

	auto dfs = [&](auto &&self, int t, int edgId) -> void {
		dfn[t] = low[t] = ++nid;
		stk.push(t);

		for (int b = h[t]; b != 0; b = ne[b]) {
			int c = e[b];
			if (dfn[c] == 0) {
				self(self, c, b);
				low[t] = min(low[t], low[c]);
			}
			else if (edgId != (b ^ 1)) low[t] = min(low[t], dfn[c]); 
		}

		if (dfn[t] == low[t]) {
			int now;
			++tot;

			do {
				now = stk.top();
				stk.pop();

				eDcc[tot].push_back(now);
			} while (t != now);
		}
	};

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0) {
			dfs(dfs, i, 0);
		}
	}

	cout << tot << '\n';
	for (int i = 1; i <= tot; i++) {
		cout << eDcc[i].size();
		for (auto j: eDcc[i]) {
			cout << ' ' << j;
		}
		cout << '\n';
	}
	return 0;
}