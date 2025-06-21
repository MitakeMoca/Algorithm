#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
long long W[505][505] = {{0}};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			W[i][j] = -INF;
		}
	}

	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		W[u][v] = w;
	}

	vector<long long> la(n + 1, 0), lb(n + 1, 0);
	vector<int> match(n + 1, -1);

	vector<bool> vb(n + 1);
	vector<long long> mb(n + 1), pre(n + 1);
	
	auto bfs = [&](int t) -> void {
		fill(vb.begin(), vb.end(), false);
		fill(pre.begin(), pre.end(), 0);
		fill(mb.begin(), mb.end(), INF);
		long long x, y = 0, yy = 0, delta;
		match[y] = t;
		do {
			x = match[y], delta = INF, vb[y] = true;
			for (int i = 1; i <= n; i++) {
				if (vb[i]) continue;
				if (mb[i] > la[x] + lb[i] - W[x][i]) {
					mb[i] = la[x] + lb[i] - W[x][i];
					pre[i] = y;
				}
				if (delta > mb[i]) delta = mb[i], yy = i;
			}
			for (int i = 0; i <= n; i++) {
				if (vb[i]) la[match[i]] -= delta, lb[i] += delta;
				else mb[i] -= delta;
			}
			y = yy;
		} while (match[y] != -1);
		
		while (y != 0) {
			match[y] = match[pre[y]];
			y = pre[y];
		} 
	};

	for (int i = 1; i <= n; i++) {
		bfs(i);
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += W[match[i]][i];
	}
	cout << ans << '\n';
	for (int i = 1; i <= n; i++) {
		cout << match[i] << " \n"[i == n];
	}
	return 0;
}