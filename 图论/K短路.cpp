#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;

struct LeftTree {

	int dis[3000005] = {0};
	int lc[3000005] = {0};
	int rc[3000005] = {0};
	double W[3000005] = {0};
	int to[3000005] = {0};
	int rt[5005] = {0};
	int id = 0;

	LeftTree() {
		dis[0] = -1;
	}

	int newnode(double w, int node)
	{
		W[++id] = w;
		to[id] = node;
		return id;
	}

	int merge(int x, int y)
	{
		if (x == 0 || y == 0) return x + y;
		if (W[x] > W[y]) swap(x, y);

		int p = ++id;
		lc[p] = lc[x];
		W[p] = W[x];
		to[p] = to[x];
		rc[p] = merge(rc[x], y);

		if (dis[lc[p]] < dis[rc[p]]) swap(lc[p], rc[p]);
		dis[p] = dis[rc[p]] + 1;
		return p;
	}
} tr;

struct Edge {

	int h[5005] = {0};
	int e[200005] = {0};
	int ne[200005] = {0};
	double W[200005] = {0};
	int id = 0;

	void add(int a, int b, double w)
	{
		e[++id] = b;
		ne[id] = h[a];
		h[a] = id;
		W[id] = w;
	}
} p1, p2;

double dis[5005] = {0};
bool V[5005] = {false};

void Dijk(int s, int t, int n)
{
	for (int i = 1; i <= n; i++)
		dis[i] = 1e18;

	priority_queue<pair<double, int>> q;
	q.push({0, s});
	dis[s] = 0;

	while (!q.empty()) {
		auto [weight, node] = q.top();
		q.pop();

		if (V[node]) continue;
		V[node] = true;

		for (int b = p2.h[node]; b != 0; b = p2.ne[b]) {
			int c = p2.e[b];
			
			if (dis[c] > dis[node] + p2.W[b]) {
				dis[c] = dis[node] + p2.W[b];
				q.push({-dis[c], c});
			}
		}
	}
}

bool V2[5005] = {false};
int fa[5005] = {0};
bool onTree[200005] = {false};

void dfs1(int t)
{
	V2[t] = true;
	for (int b = p2.h[t]; b != 0; b = p2.ne[b]) {
		int c = p2.e[b];

		if (V2[c] == false && fabs(dis[c] - p2.W[b] - dis[t]) < eps) {
			onTree[b] = true;
			fa[c] = t;
			dfs1(c);
		}
	}
}

bool V3[5005] = {false};
void dfs2(int t)
{
	V3[t] = true;
	if (fa[t] != 0) tr.rt[t] = tr.merge(tr.rt[t], tr.rt[fa[t]]);
	for (int b = p2.h[t]; b != 0; b = p2.ne[b]) {
		int c = p2.e[b];
		if (fa[c] == t && !V3[c]) dfs2(c);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	double e;

	cin >> n >> m >> e;

	int u, v;
	double w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		p1.add(u, v, w);
		p2.add(v, u, w);
	}

	Dijk(n, 1, n);
	dfs1(n);

	for (int i = 1; i < n; i++) {
		if (!V[i]) continue;

		for (int b = p1.h[i]; b != 0; b = p1.ne[b]) {
			int c = p1.e[b];

			if (onTree[b] || !V[c]) continue;

			tr.rt[i] = tr.merge(tr.rt[i], tr.newnode(dis[c] + p1.W[b] - dis[i], c));
		}
	}

	dfs2(n);

	priority_queue<pair<double, int>> q;
	e -= dis[1];

	if (e < 0) {
		cout << 0 << '\n';
		return 0;
	}

	int ans = 1;
	if (tr.rt[1] != 0) q.push({-(dis[1] + tr.W[tr.rt[1]]), tr.rt[1]});

	while (!q.empty()) {
		auto [weight, node] = q.top();
		q.pop();

		weight = -weight;
		if (e < weight) break;
		e -= weight;
		ans++;

		if (tr.lc[node] != 0) q.push({-(weight - tr.W[node] + tr.W[tr.lc[node]]), tr.lc[node]});
		if (tr.rc[node] != 0) q.push({-(weight - tr.W[node] + tr.W[tr.rc[node]]), tr.rc[node]});

		node = tr.to[node];
		if (tr.rt[node] != 0) q.push({-(weight + tr.W[tr.rt[node]]), tr.rt[node]});
	}

	cout << ans << '\n';

	return 0;
}