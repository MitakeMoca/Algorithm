#include <bits/stdc++.h>
using namespace std;

int h[5005] = {0};
int e[100005] = {0};
int ne[100005] = {0};
long long W[100005] = {0};
long long dis[100005] = {0};
int cnt[100005] = {0};
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
	vector<bool> V(n + 1, false);
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		dis[i] = 1e15;
	}
	q.push(s);
	dis[s] = 0;
	V[s] = true;

	while (!q.empty()) {
		int a = q.front();
		q.pop();
		V[a] = false;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (dis[c] > dis[a] + W[b]) {
				dis[c] = dis[a] + W[b];
				cnt[c] = cnt[a] + 1;
				if (cnt[c] > n) return false;
				if (V[c]) continue;
				V[c] = true;
				q.push(c);
			}
		}
	}
	return true;
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
		add(v, u, w);
	}

	for (int i = 1; i <= n; i++) {
		add(n + 1, i, 0);
	}

	if (SPFA(n + 1, n + 1) == false) {
		cout << "NO\n";
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		cout << dis[i] << " \n"[i == n];
	}
	return 0;
}