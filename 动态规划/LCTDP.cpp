#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]
#define fa(x) tr[x].p
#define notroot(x) (lc(fa(x)) == x || rc(fa(x)) == x)

const int inf = 1e9;

struct matrix{int g[2][2];};
matrix operator * (matrix a, matrix b)
{
	matrix c;
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++)
		c.g[i][j] = -inf;
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++)
	for(int k = 0; k < 2; k++)
		c.g[i][j] = max(c.g[i][j], a.g[i][k] + b.g[k][j]);
	return c;
}
int w[100005] = {0};
vector<int> p[100005];
int dp[100005][2] = {{0}};


struct{
	int p;
	int son[2];
	matrix w;
	matrix sum;
}tr[100005];

void dfs(int t, int f)
{
	fa(t) = f;
	dp[t][1] = w[t];
	dp[t][0] = 0;

	for(auto i: p[t]){
		if(i == f) continue;
		dfs(i, t);
		dp[t][0] += max(dp[i][0], dp[i][1]);
		dp[t][1] += dp[i][0];
	}

	tr[t].w.g[0][0] = tr[t].w.g[0][1] = dp[t][0];
	tr[t].w.g[1][0] = dp[t][1];
	tr[t].w.g[1][1] = -inf;
	tr[t].sum = tr[t].w;
}

void pushup(int t)
{
	tr[t].sum = tr[t].w;
	if(lc(t) != 0) tr[t].sum = tr[lc(t)].sum * tr[t].sum;
	if(rc(t) != 0) tr[t].sum = tr[t].sum * tr[rc(t)].sum;
}

void rotate(int x)
{
	int y = fa(x);
	int z = fa(y);
	int k = (rc(y) == x);

	if(notroot(y))
		tr[z].son[rc(z) == y] = x;
	fa(x) = z;
	tr[y].son[k] = tr[x].son[k ^ 1];
	fa(tr[x].son[k ^ 1]) = y;
	tr[x].son[k ^ 1] = y;
	fa(y) = x;
	pushup(y);
	pushup(x);
}

void splay(int x)
{
	while(notroot(x)){
		int y = fa(x);
		int z = fa(y);
		if(notroot(y)){
			((rc(z) == y) ^ (rc(y) == x)) ? rotate(x) : rotate(y); 
		}
		rotate(x);
	}
}

void access(int x)
{
	for(int y = 0; x != 0;){
		splay(x);
		if(rc(x) != 0){
			tr[x].w.g[0][0] += max(tr[rc(x)].sum.g[0][0], tr[rc(x)].sum.g[1][0]);
			tr[x].w.g[0][1] = tr[x].w.g[0][0];
			tr[x].w.g[1][0] += tr[rc(x)].sum.g[0][0];
		}
		if(y != 0){
			tr[x].w.g[0][0] -= max(tr[y].sum.g[0][0], tr[y].sum.g[1][0]);
			tr[x].w.g[0][1] = tr[x].w.g[0][0];
			tr[x].w.g[1][0] -= tr[y].sum.g[0][0];
		}
		rc(x) = y;
		pushup(x);
		y = x;
		x = fa(x);
	}
}

void update(int x, int y)
{
	access(x);
	splay(x);
	tr[x].w.g[1][0] += y - w[x];
	pushup(x);
	w[x] = y;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++) cin >> w[i];
	int u, v;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	dfs(1, 0);

	int x, y;
	while(m--){
		cin >> x >> y;
		update(x, y);
		cout << max(tr[x].sum.g[0][0], tr[x].sum.g[1][0]) << '\n';
	}
	return 0;
}