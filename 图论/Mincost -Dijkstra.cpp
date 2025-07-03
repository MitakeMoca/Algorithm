#include <bits/stdc++.h>
using namespace std;

int h[5005] = {0};
int pre[5005] = {0};
long long f[5005] = {0};
long long dis[5005] = {0};
long long o[5005] = {0};
int e[200005] = {0};
int ne[200005] = {0};
long long mf[100005] = {0};
long long W[100005] = {0};
int id = 1;

void add(int a, int b, long long f, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
	mf[id] = f;
}

void SPFA(int s, int t, int n)
{
	for (int i = 1; i <= n; i++) o[i] = 1e18;
	vector<bool> V(n + 1, false);
	queue<int> q;
	q.push(s);
	o[s] = 0;
	V[s] = true;

	while (!q.empty()) {
		int a = q.front();
		q.pop();
		V[a] = false;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (mf[b] == 0 || o[c] <= o[a] + W[b]) continue;
			o[c] = o[a] + W[b];
			if (V[c]) continue;
			V[c] = true;
			q.push(c);
		}
	}
}

bool Dijk(int s, int t, int n)
{
	priority_queue<pair<long long, int>> q;
	for (int i = 1; i <= n; i++) dis[i] = 1e18;
	vector<bool> V(n + 1, false);
	q.push({0, s});
	f[s] = 1e18;
	dis[s] = 0;

	while (!q.empty()) {
		auto [weight, node] = q.top();
		q.pop();

		if (V[node]) continue;
		V[node] = true;

		for (int b = h[node]; b != 0; b = ne[b]) {
			int c = e[b];
			long long w = W[b] + o[node] - o[c];
			if (mf[b] == 0 || V[c] || w + dis[node] >= dis[c]) continue;
			pre[c] = b;
			f[c] = min(f[node], mf[b]);
			dis[c] = w + dis[node];
			q.push({-dis[c], c});
		}
	}
	return dis[t] != 1e18;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v;
	long long f1, c;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> f1 >> c;
		add(u, v, f1, c);
		add(v, u, 0, -c);
	}

	SPFA(s, t, n);

	long long ans1 = 0, ans2 = 0;
	while (Dijk(s, t, n)) {
		long long tmp = f[t];
		int now = t;
		do {
			int b = pre[now];
			mf[b] -= tmp;
			mf[b ^ 1] += tmp;
			now = e[b ^ 1];
		} while (now != s);
		for (int i = 1; i <= n; i++) o[i] += dis[i];
		ans2 += tmp * o[t];
		ans1 += tmp;
	}

	cout << ans1 << ' ' << ans2 << '\n';
	return 0;
}