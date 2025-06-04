#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int u, v;
	long long w;
	bool operator < (const Edge &th) const
	{
		return w < th.w;
	}
}e[200005];
int fa[100005];

int find(int x)
{
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

long long Kruskal(int n, int m)
{
	for (int i = 1; i <= n; i++) fa[i] = i;
	int cnt = 0;
	sort(e, e + m);
	long long sum = 0;
	for (int i = 0; i < m; i++) {
		int u = find(e[i].u), v = find(e[i].v);
		if (u == v) continue;
		sum += e[i].w;
		cnt++;
		fa[u] = v;
	}
	if (cnt != n - 1) return -1;
	return sum;
}

int main()
{
	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++){
		cin >> e[i].u >> e[i].v >> e[i].w;
	}

	int ans = Kruskal(n, m);
	if (ans == -1) cout << "orz\n";
	else cout << ans << '\n';
	return 0;
}