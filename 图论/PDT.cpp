#include <bits/stdc++.h>
using namespace std;

#define N 100005

int h[N] = {0};
int W[N] = {0};
int e[N * 2] = {0};
int ne[N * 2] = {0};

int cnt = 0, n;

void add(int a, int b)
{
	e[++cnt] = b;
	ne[cnt] = h[a];
	h[a] = cnt;
}

struct{
	int dep[N] = {0};
	int st[N][20] = {{0}};

	void dfs(int t, int fa)
	{
		dep[t] = dep[fa] + 1;
		st[t][0] = fa;
		for(int i = 1; i < 20; i++){
			st[t][i] = st[st[t][i - 1]][i - 1];
		}
		for(int b = h[t]; b != 0; b = ne[b]){
			int c = e[b];
			if(c == fa) continue;
			dfs(c, t);
		}
	}

	int lca(int u, int v)
	{
		if(dep[u] < dep[v]) swap(u, v);
		for(int i = 19; i >= 0; i--){
			if(dep[st[u][i]] >= dep[v]) u = st[u][i];
		}
		if(u == v) return u;
		for(int i = 19; i >= 0; i--){
			if(st[u][i] != st[v][i]){
				u = st[u][i], v = st[v][i];
			}
		}
		return st[u][0];
	}

	int queryDis(int x, int y)
	{
		int fa = lca(x, y);
		return dep[x] + dep[y] - 2 * dep[fa];
	}
}LCA;

struct SegTree{
	int id = 0;
	int root[N], sum[N * 40], lc[N * 40], rc[N * 40];

	void change(int &t, int l, int r, int d, int v)
	{
		if(t == 0) t = ++id;
		sum[t] += v;
		if(l == r) return;
		int mid = l + r >> 1;
		if(d <= mid) change(lc[t], l, mid, d, v);
		else change(rc[t], mid + 1, r, d, v);
	}

	int query(int t, int l, int r, int x, int y){
		if(l >= x && r <= y) return sum[t];
		int mid = l + r >> 1, ans = 0;
		if(x <= mid) ans += query(lc[t], l, mid, x, y);
		if(y > mid) ans += query(rc[t], mid + 1, r, x, y);
		return ans;
	}
}sg, ch;

struct PointTree{
	int root = 0, sum = 0, mn = 0;
	int sz[N], del[N], dep[N], fa[N], dis[N][20], pre[N];

	void find_root(int t, int f)
	{
		pre[t] = f;
		sz[t] = 1;
		int s = 0;
		for(int b = h[t]; b != 0; b = ne[b]){
			int c = e[b];
			if(c == f || del[c] == 1) continue;
			find_root(c, t);
			sz[t] += sz[c];
			s = max(s, sz[c]);
		}
		s = max(s, sum - sz[t]);
		if(s < mn) root = t, mn = s;
	}

	void build_sg(int x, int f, int rt, int d)
	{
		sg.change(sg.root[rt], 0, n, d, W[x]);
		for(int b = h[x]; b != 0; b = ne[b]){
			int c = e[b];
			if(c == f || del[c] == 1) continue;
			build_sg(c, x, rt, d + 1);
		}
	}

	void build_ch(int x, int f, int rt, int d)
	{
		ch.change(ch.root[rt], 0, n, d, W[x]);
		for(int b = h[x]; b != 0; b = ne[b]){
			int c = e[b];
			if(c == f || del[c] == 1) continue;
			build_ch(c, x, rt, d + 1);
		}
	}

	void build(int t)
	{
		del[t] = 1;
		build_sg(t, 0, t, 0);
		int tmp = sum;
		for(int b = h[t]; b != 0; b = ne[b]){
			int c = e[b];
			if(del[c] == 1) continue;
			if(pre[t] != c) sum = sz[c];
			else sum = tmp - sz[t];
			mn = sum + 1, root = 0;
			find_root(c, t);
			build_ch(c, t, root, 1);
			fa[root] = t, dep[root] = dep[t] + 1;
			build(root);
		}
	}

	void init()
	{
		LCA.dfs(1, 0);
		sum = n;
		mn = sum + 1, root = 0;
		find_root(1, 0);
		build(root);
		for(int i = 1; i <= n; i++){
			for(int j = i; j != 0; j = fa[j]){
				dis[i][dep[i] - dep[j]] = LCA.queryDis(i, j);
			}
		}
	}

	int query(int x, int y)
	{
		int ans = sg.query(sg.root[x], 0, n, 0, y);
		for(int i = x; fa[i] != 0; i = fa[i]){
			int d = dis[x][dep[x] - dep[fa[i]]];
			if(d > y) continue;
			ans += sg.query(sg.root[fa[i]], 0, n, 0, y - d);
			ans -= ch.query(ch.root[i], 0, n, 0, y - d);
		}
		return ans;
	}

	void change(int x, int y)
	{
		sg.change(sg.root[x], 0, n, 0, y - W[x]);
		for(int i = x; fa[i] != 0; i = fa[i]){
			int d = dis[x][dep[x] - dep[fa[i]]];
			sg.change(sg.root[fa[i]], 0, n, d, y - W[x]);
			ch.change(ch.root[i], 0, n, d, y - W[x]);
		}
	}
}pt;

int main()
{
	int m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		cin >> W[i];
	}

	int u, v;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}

	pt.init();

	int op, x, y, ans = 0;
	while(m--){
		cin >> op >> x >> y;
		x ^= ans;
		y ^= ans;
		if(op == 0){
			ans = pt.query(x, y);
			cout << ans << endl;
		}
		else{
			pt.change(x, y);
			W[x] = y;
		}
	}
	return 0;
}