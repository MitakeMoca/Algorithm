#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int cur[100005] = {0};
int d[100005] = {0};
int e[1000005] = {0};
int C[1000005] = {0};
int ne[1000005] = {0};
int id = 1;

void add(int a, int b, int c)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	C[id] = c;
}

bool bfs(int s, int t, int n)
{
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 1;

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (d[c] != 0 || C[b] == 0) continue;
			d[c] = d[a] + 1;
			q.push(c);
		}
	}

	return d[t] > 0;
}

int dfs(int now, int t, int w)
{
	if (now == t) return w;
	int sum = 0;
	for (int b = cur[now]; b != 0; b = ne[b]) {
		int c = e[b];
		cur[now] = b;
		if (d[c] != d[now] + 1 || C[b] == 0) continue;
		int tmp = dfs(c, t, min(w, C[b]));
		C[b] -= tmp;
		C[b ^ 1] += tmp;
		w -= tmp;
		sum += tmp;
		if (w == 0) break;
	}
	if (sum == 0) cur[now] = 0;
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, e;
	cin >> n >> m >> e;

	int u, v;
	for (int i = 0; i < e; i++) {
		cin >> u >> v;
		v += n;
		add(u, v, 1);
		add(v, u, 0);
	}

	for (int i = 1; i <= n; i++) {
		add(n + m + 1, i, 1);
		add(i, n + m + 1, 0);
	}

	for (int i = n + 1; i <= n + m; i++) {
		add(i, n + m + 2, 1);
		add(n + m + 2, i, 0);
	}

	n += m + 2;
	int ans = 0;
	while (bfs(n - 1, n, n)) {
		memcpy(cur, h, sizeof(h));
		ans += dfs(n - 1, n, 1e9);
	}
	cout << ans << '\n';
	return 0;
}