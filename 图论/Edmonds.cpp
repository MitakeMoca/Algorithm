#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, rt;
	cin >> n >> m >> rt;

	vector<int> u(m), v(m);
	vector<long long> W(m);

	for (int i = 0; i < m; i++) {
		cin >> u[i] >> v[i] >> W[i];
	}

	vector<long long> in(n + 1);
	vector<int> fa(n + 1), lp(n + 1), pre(n + 1);
	long long ans = 0;
	while (true) {
		fill(in.begin(), in.end(), INF);
		fill(lp.begin(), lp.end(), 0);
		fill(fa.begin(), fa.end(), 0);
		int tot = 0;
		for (int i = 0; i < m; i++) {
			if (u[i] != v[i] && in[v[i]] > W[i]) {
				pre[v[i]] = u[i];
				in[v[i]] = W[i];
			}
		}
		in[rt] = 0;
		for (int i = 1; i <= n; i++) {
			ans += in[i];
			if (in[i] == INF) {
				cout << -1 << '\n';
				return 0;
			}
		}
		for (int u = 1, v = 1; u <= n; u++, v = u) {
			while (v != rt && fa[v] != u && lp[v] == 0) fa[v] = u, v = pre[v];
			if (v != rt && lp[v] == 0) {
				lp[v] = ++tot;
				for (int i = pre[v]; i != v; i = pre[i]) lp[i] = tot;
			}
		}
		if (tot == 0) {
			cout << ans << '\n';
			return 0;
		}
		for (int i = 1; i <= n; i++) {
			if (lp[i] == 0) lp[i] = ++tot;
		}
		for (int i = 0; i < m; i++) {
			W[i] -= in[v[i]];
			u[i] = lp[u[i]];
			v[i] = lp[v[i]];
		}
		n = tot;
		rt = lp[rt];
	}

	return 0;
}