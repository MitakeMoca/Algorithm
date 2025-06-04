#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc (lc | 1)

const int inf = 0x3f3f3f3f;
int w[100005] = {0};
int sz[100005] = {0};
int son[100005] = {0};
int dfn[100005] = {0};
int top[100005] = {0};
int bot[100005] = {0};
int fa[100005] = {0};
int id[100005] = {0};
int dp[100005][2] = {{0}};
vector<int> p[100005];
int tot = 0;

struct matrix{
	int g[2][2];
};

matrix operator * (matrix a, matrix b)
{
	matrix c;
	memset(c.g, -0x3f, sizeof(c.g));
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 2; k++){
				c.g[i][j] = max(c.g[i][j], a.g[i][k] + b.g[k][j]);
			}
		}
	}
	return c;
}

matrix tr[400005], mt[100005];

void dfs(int t, int f)
{
	dp[t][1] = w[t];
	dp[t][0] = 0;

	for(auto i: p[t]){
		if(i == f) continue;
		dfs(i, t);
		dp[t][1] += dp[i][0];
		dp[t][0] += max(dp[i][0], dp[i][1]);
	}
}

void dfs1(int t, int f)
{
	sz[t] = 1;
	fa[t] = f;

	for(auto i: p[t]){
		if(i == f) continue;
		dfs1(i, t);
		sz[t] += sz[i];
		if(sz[son[t]] < sz[i]) son[t] = i;
	}
}

void dfs2(int t, int s)
{
	dfn[t] = ++tot;
	id[tot] = t;
	top[t] = s;

	if(son[t] != 0) dfs2(son[t], s), bot[t] = bot[son[t]];
	else bot[t] = t;

	for(auto i: p[t]){
		if(i == son[t] || i == fa[t]) continue;
		dfs2(i, i);
	}
}

void build(int t, int l, int r)
{
	if(l == r){
		int x = id[l];
		int g0 = 0, g1 = w[x];
		for(auto i: p[x]){
			if(i == fa[x] || i == son[x]) continue;
			g0 += max(dp[i][0], dp[i][1]);
			g1 += dp[i][0];
		}
		tr[t] = mt[x] = (matrix){g0, g0, g1, -inf};
		return;
	}
	int m = l + r >> 1;
	build(lc, l, m);
	build(rc, m + 1, r);
	tr[t] = tr[lc] * tr[rc];
}

void change(int t, int l, int r, int pos)
{
	if(l == r){
		tr[t] = mt[id[pos]];
		return;
	}
	int m = l + r >> 1;
	if(pos <= m) change(lc, l, m, pos);
	else change(rc, m + 1, r, pos);
	tr[t] = tr[lc] * tr[rc];
}

matrix query(int t, int l, int r, int x, int y)
{
	if(x == l && y == r) return tr[t];
	int m = l + r >> 1;
	if(y <= m) return query(lc, l, m, x, y);
	if(x > m) return query(rc, m + 1, r, x, y);
	return query(lc, l, m, x, m) * query(rc, m + 1, r, m + 1, y);
}

void update(int t, int k, int n)
{
	mt[t].g[1][0] += k - w[t];
	w[t] = k;

	while(t != 0){
		matrix a = query(1, 1, n, dfn[top[t]], dfn[bot[t]]);
		change(1, 1, n, dfn[t]);
		matrix b = query(1, 1, n, dfn[top[t]], dfn[bot[t]]);
		t = fa[top[t]];

		if(t == 0) break;
		int tmp = max(b.g[0][0], b.g[1][0]) - max(a.g[0][0], a.g[1][0]);
		//cout << t << ' ' << tmp << '\n';
		mt[t].g[0][0] += tmp, mt[t].g[0][1] += tmp;
		mt[t].g[1][0] += b.g[0][0] - a.g[0][0];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		cin >> w[i];
	}

	int u, v;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	dfs(1, 0);
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);

	int x, y;
	while(m--){
		cin >> x >> y;
		update(x, y, n);
		matrix ans = query(1, 1, n, dfn[1], dfn[bot[1]]);
		cout << max(ans.g[0][0], ans.g[1][0]) << '\n';
	}
	return 0;
}