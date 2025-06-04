#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int e[400005] = {0};
int ne[400005] = {0};
long long d[100005] = {0};
long long W[400005] = {0};
int id = 0;

void add(int a, int b, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
}

void Dijk(int s, int n)
{
	for (int i = 1; i <= n; i++) d[i] = 1e18;
	priority_queue<pair<long long, int>> q;
	d[s] = 0;
	q.push({0, s});
	vector<int> V(n + 1, 0);

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

	int n, m, s;
	cin >> n >> m >> s;

	int u, v;
	long long w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		add(u, v, w);
	}

	Dijk(s, n);
	for (int i = 1; i <= n; i++)
		cout << d[i] << " \n"[i == n];
	return 0;
}