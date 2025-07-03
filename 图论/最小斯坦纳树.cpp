#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<int, long long>>> p(n + 1);
	int u, v;
	long long w;

	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		p[u].push_back({v, w});
		p[v].push_back({u, w});
	}

	vector<int> S(k);
	for (int i = 0; i < k; i++) {
		cin >> S[i];
	}

	m = (1 << k) - 1;
	vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
	for (int i = 0; i < k; i++) {
		dp[S[i]][(1 << i)] = 0;
	}

	queue<int> q;
	vector<bool> V(n + 1, false);

	auto SPFA = [&](int t) -> void {
		while (!q.empty()) {
			int a = q.front();
			q.pop();
			V[a] = false;

			for (auto [node, weight]: p[a]) {
				if (dp[node][t] > dp[a][t] + weight) {
					dp[node][t] = dp[a][t] + weight;
					if (V[node] == true) continue;
					V[node] = true;
					q.push(node);
				}
			}
		}
	};

	for (int i = 1; i <= m; i++) {
		for (int k = 1; k <= n; k++) {
			for (int j = (i & (i - 1)); j != 0; j = ((j - 1) & i)) {
				dp[k][i] = min(dp[k][i], dp[k][j] + dp[k][i ^ j]);
			}
			if (dp[k][i] < INF) {
				q.push(k);
				V[k] = true;
			}
		}
		SPFA(i);
	}

	long long ans = INF;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, dp[i][m]);
	}
	cout << ans << '\n';
	return 0;
}