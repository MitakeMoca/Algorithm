#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int e[400005] = {0};
int ne[400005] = {0};
long long W[400005] = {0};
long long C[400005] = {0};
long long d[100005] = {0};
long long mf[100005] = {0};
int pre[100005] = {0};
int id = 1;

void add(int a, int b, long long w, long long c)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
	C[id] = c;
}

bool SPFA(int s, int t, int n)
{
	for (int i = 1; i <= n; i++) d[i] = 1e15;
	mf[t] = 0;
	queue<int> q;
	vector<int> V(n + 1, 0);
	q.push(s);
	V[s] = 1;
	d[s] = 0;
	mf[s] = 1e15;

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		V[a] = 0;
		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (W[b] == 0 || d[c] <= d[a] + C[b]) continue;
			d[c] = d[a] + C[b];
			pre[c] = b;
			mf[c] = min(mf[a], W[b]);
			if (V[c] == 1) continue;
			q.push(c);
			V[c] = 1;
		}
	}

	return mf[t] > 0;
}

void EK(int s, int t, int n)
{
	long long ans1 = 0, ans2 = 0;
	while (SPFA(s, t, n)) {
		ans1 += mf[t];
		ans2 += mf[t] * d[t];

		int now = t;
		while (now != s) {
			int tmp = pre[now];
			W[tmp] -= mf[t];
			W[tmp ^ 1] += mf[t];
			now = e[tmp ^ 1];
		}
	}
	cout << ans1 << ' ' << ans2 << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v;
	long long w, c;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w >> c;
		add(u, v, w, c);
		add(v, u, 0, -c);
	}

	EK(s, t, n);
	
	return 0;
}