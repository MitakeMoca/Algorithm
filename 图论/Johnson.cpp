#include <bits/stdc++.h>
using namespace std;

int h[3005] = {0};
int e[60005] = {0};
int ne[60005] = {0};
long long W[60005] = {0};
long long d[3005] = {0};
long long o[3005] = {0};
int id = 0;

void add(int a, int b, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
}

bool SPFA(int s, int n)
{
	for (int i = 1; i <= n; i++) o[i] = 1e9;
	vector<int> cnt(n + 1, 0);
	vector<int> V(n + 1, 0);
	queue<int> q;
	q.push(s);
	o[s] = 0;
	V[s] = 1;

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		V[a] = 0;
		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (o[c] > o[a] + W[b]) {
				o[c] = o[a] + W[b];
				cnt[c] = cnt[a] + 1;
				if (cnt[c] > n) return true;
				if (V[c] == 1) continue;
				V[c] = 1;
				q.push(c);
			}
		}
	}
	return false;
}

void Dijk(int s, int n)
{
	for (int i = 1; i <= n; i++) d[i] = 1e9;
	vector<int> V(n + 1, 0);
	priority_queue<pair<int, int>> q;
	d[s] = 0;
	q.push({0, s});

	while (!q.empty()) {
		int a = q.top().second;
		q.pop();

		if (V[a] == 1) continue;
		V[a] = 1;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];

			if (d[c] > d[a] + W[b]) {
				d[c] = d[a] + W[b];
				q.push({-d[c], c});
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	int u, v;
	long long w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		add(u, v, w);
	}

	for (int i = 1; i <= n; i++) {
		add(0, i, 0);
	}

	if (SPFA(0, n)) {
		cout << "-1\n";
		return 0;
	}


	for (int i = 1; i <= n; i++) {
		for (int b = h[i]; b != 0; b = ne[b]) {
			int c = e[b];
			W[b] += o[i] - o[c];
		}
	}

	for (int i = 1; i <= n; i++) {
		long long ans = 0;
		Dijk(i, n);
		for (int j = 1; j <= n; j++) {
			if (d[j] != 1e9) d[j] += o[j] - o[i];
			ans += d[j] * j;
		}
		cout << ans << '\n';
	}
	
	return 0;
}