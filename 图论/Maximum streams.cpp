#include <bits/stdc++.h>
using namespace std;

int h[100005] = {0};
int e[200005] = {0};
int ne[200005] = {0};
long long W[200005] = {0};
int d[100005] = {0};
int cur[100005] = {0};
int id = 1;

void add(int a, int b, long long w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
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
			if (W[b] == 0 || d[c] != 0) continue;
			d[c] = d[a] + 1;
			q.push(c);
			if (c == t) return true;
		}
	}
	return false;
}

long long dfs(int now, int t, long long sum)
{
	if (now == t) return sum;
	long long res = 0;
	for (int b = cur[now]; b != 0; b = ne[b]) {
		cur[now] = b;
		int c = e[b];
		if (W[b] == 0 || d[c] != d[now] + 1) continue;
		long long tmp = dfs(c, t, min(sum, W[b]));
		W[b] -= tmp;
		W[b ^ 1] += tmp;
		sum -= tmp;
		res += tmp;
		if (sum == 0) break;
	}
	if (res == 0) cur[now] = 0;
	return res;
}

long long Dinic(int s, int t, int n)
{
	long long ans = 0;
	while (bfs(s, t, n)) {
		memcpy(cur, h, sizeof(h));
		ans += dfs(s, t, 1e15);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v;
	long long w;
	while(m--){
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, 0);
	}

	cout << Dinic(s, t, n) << '\n';
	return 0;
}