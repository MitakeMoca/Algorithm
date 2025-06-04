#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int e[1000005] = {0};
int ne[1000005] = {0};
long long W[1000005] = {0};
long long d[100005] = {0};
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
	for (int i = 1; i <= n; i++) d[i] = (1 << 31) - 1;
	queue<int> q;
	vector<int> V(n + 1, 0);
	vector<int> cnt(n + 1, 0);
	d[s] = 0;
	q.push(s);
	V[s] = 1;

	while (!q.empty()) {
		int a = q.front();
		q.pop();
		V[a] = 0;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (d[c] > d[a] + W[b]) {
				d[c] = d[a] + W[b];
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

void clear(int n)
{
	for (int i = 1; i <= n; i++) h[i] = 0;
	id = 0;
}

void solve()
{
	int n, m;
	cin >> n >> m;

	int u, v;
	long long w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		add(u, v, w);
		if (w >= 0) add(v, u, w);
	}
	if (SPFA(1, n)) cout << "YES\n";
	else cout << "NO\n";
	clear(n);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}