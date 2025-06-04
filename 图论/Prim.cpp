#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int e[400005] = {0};
int ne[400005] = {0};
long long W[400005] = {0};
long long d[400005] = {0};
int id = 0;

void add(int a, int b, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
}

long long Prim(int n)
{
	vector<int> V(n + 1, 0);
	priority_queue<pair<long long, int>> q;
	q.push({0, 1});
	long long sum = 0;
	int cnt = 0;

	while (!q.empty()) {
		int a = q.top().second;
		long long wei = -q.top().first;
		q.pop();

		if (V[a] == 1) continue;
		V[a] = 1, cnt++;
		sum += wei;

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			q.push({-W[b], c});
		} 
	}

	if (cnt == n) return sum;
	return -1;
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
		add(v, u, w);
	}

	int ans = Prim(n);
	if (ans == -1) cout << "orz\n";
	else cout << ans << '\n';

	return 0;
}