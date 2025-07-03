#include <bits/stdc++.h>
using namespace std;

int h[5005] = {0};
int cur[5005] = {0};
bool V[5005] = {false};
int e[100005] = {0};
int ne[100005] = {0};
long long mf[100005] = {0};
long long W[100005] = {0};
long long dis[100005] = {0};
int id = 1;

void add(int a, int b, long long f, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
	mf[id] = f;
}


bool SPFA(int s, int t, int n)
{
	for (int i = 1; i <= n; i++) {
		dis[i] = 1e18;
	}
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	V[s] = true;

	while (!q.empty()) {
		int a = q.front();
		q.pop();
		V[a] = false;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (mf[b] == 0 || dis[c] <= dis[a] + W[b]) continue;
			dis[c] = dis[a] + W[b];
			if (V[c]) continue;
			V[c] = true;
			q.push(c);
		}
	}

	return dis[t] != 1e18;
}

long long dfs(int now, int t, long long f)
{
	if (now == t) return f;
	V[now] = true;
	long long sum = 0;
	for (int b = cur[now]; b != 0; b = ne[b]) {
		int c = e[b];
		cur[now] = b;
		if (V[c] || dis[c] != dis[now] + W[b] || mf[b] == 0) continue;
		long long tmp = dfs(c, t, min(f, mf[b]));
		mf[b] -= tmp;
		mf[b ^ 1] += tmp;
		sum += tmp;
		f -= tmp;
		if (f == 0) break;
	}
	if (sum == 0) cur[now] = 0;
	V[now] = false;
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v;
	long long f, c;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> f >> c;
		add(u, v, f, c);
		add(v, u, 0, -c);
	}

	long long ans1 = 0, ans2 = 0;
	while (SPFA(s, t, n)) {
		memcpy(cur, h, sizeof(h));
		long long tmp = dfs(s, t, 1e18);
		ans1 += tmp;
		ans2 += tmp * dis[t];
	}
	cout << ans1 << ' ' << ans2 << '\n';
	return 0;
}