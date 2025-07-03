#include <bits/stdc++.h>
using namespace std;

int h[1005] = {0};
int e[100005] = {0};
int ne[100005] = {0};
int fa[1005] = {0};
int match[1005] = {0};
int pre[1005] = {0};
int vis[1005] = {0};
int dfn[1005] = {0};
int tot = 0;
int id = 0;

void add(int a, int b)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
}

int find(int x)
{
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

queue<int> q;

int tim = 0;

int getLCA(int u, int v)
{
	++tim;
	u = find(u);
	v = find(v);

	while (dfn[u] != tim) {
		dfn[u] = tim;
		u = find(pre[match[u]]);
		if (v != 0) swap(u, v);
	}
	return u;
}

void blossom(int u, int v, int lca)
{
	while (find(u) != lca) {
		pre[u] = v;  
		v = match[u];
		if(vis[v] == 2) {
			vis[v] = 1;
			q.push(v);
		}
		if(find(u) == u) fa[u] = lca;
		if(find(v) == v) fa[v] = lca;
		u = pre[v];
	}
}


int bfs(int s, int n)
{
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= n; i++)
		pre[i] = 0;
	for (int i = 1; i <= n; i++)
		vis[i] = 0;

	while (!q.empty()) q.pop();

	q.push(s);
	vis[s] = 1;
	while (!q.empty()) {
		int a = q.front();
		q.pop();

		for (int b = h[a]; b != 0; b = ne[b]) {
			int c = e[b];
			if (find(a) == find(c) || vis[c] == 2) continue;

			if (vis[c] == 0) {
				vis[c] = 2;
				pre[c] = a;
				if (match[c] == 0) {
					for (int k = c, p; k != 0; k = p) {
						p = match[pre[k]];
						match[k] = pre[k];
						match[pre[k]] = k;
					}
					return 1;
				}
				vis[match[c]] = 1;
				q.push(match[c]);
			}
			else {
				int lca = getLCA(a, c);
				blossom(a, c, lca);
				blossom(c, a, lca);
			}
		}
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (match[i] != 0) continue;
		ans += bfs(i, n);
	}

	cout << ans << '\n';
	for (int i = 1; i <= n; i++) {
		cout << match[i] << " \n"[i == n];
	}
	return 0;
}