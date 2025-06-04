#include <bits/stdc++.h>
using namespace std;

vector<int> p[1000005];
int len[1000005] = {0};
int son[1000005] = {0};
int pos[1000005] = {0};
int ans[1000005] = {0};
int dp[1000005] = {0};
int tot = 0;

void dfs1(int t, int fa)
{
	for (auto i: p[t]) {
		if (i == fa) continue;
		dfs1(i, t);
		if (len[son[t]] < len[i]) son[t] = i;
	}
	len[t] = len[son[t]] + 1;
}

void dfs2(int t, int fa)
{
	pos[t] = ++tot;
	dp[pos[t]] = 1;
	int now = pos[t];

	if (son[t] != 0) {
		dfs2(son[t], t);
		ans[t] = ans[son[t]] + 1;
	}

	for (auto i: p[t]) {
		if (i == fa || i == son[t]) continue;
		dfs2(i, t);
		for (int j = 0; j < len[i]; j++) {
			dp[now + j + 1] += dp[pos[i] + j];
			if (dp[now + j + 1] > dp[now + ans[t]]) {
				ans[t] = j + 1;
			}
			else if (dp[now + j + 1] == dp[now + ans[t]]) {
				ans[t] = min(ans[t], j + 1);
			}
		}
	}

	if (dp[now + ans[t]] == 1) ans[t] = 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;

	int u, v;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	dfs1(1, 0);
	dfs2(1, 0);

	for (int i = 1; i <= n; i++)
		cout << ans[i] << '\n';

	return 0;
}