#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> p(500005, vector<int>());
vector<pair<int, int>> Q[500005];
int A[500005] = {0};
int st[500005][20] = {0};
int dp[500005] = {0};
int V[500005] = {0};
int F[500005] = {0}; 
int sz[500005] = {0};
int son[500005] = {0};
int top[500005] = {0};

struct LCA{
	int dep[500005] = {0};
	int st[500005][20] = {{0}};

	void dfs(int t, int fa)
	{
		st[t][0] = fa;
		dep[t] = dep[fa] + 1;
		for (int i = 1; i < 20; i++)
			st[t][i] = st[st[t][i - 1]][i - 1];

		for (auto i: p[t]) {
			if (i == fa) continue;
			dfs(i, t);
		}
	}

	int getLCA(int x, int y)
	{
		if (dep[x] < dep[y]) swap(x, y);
		for (int i = 19; i >= 0; i--) {
			if (dep[st[x][i]] >= dep[y]) x = st[x][i];
		}

		if (x == y) return x;
		for (int i = 19; i >= 0; i--){
			if (st[x][i] != st[y][i]) {
				x = st[x][i], y = st[y][i];
			}
		}
		return st[x][0];
	}
}lca;

struct {
	int sz[500005] = {0};
	int son[500005] = {0};
	int fa[500005] = {0};
	int top[500005] = {0};
	int dep[500005] = {0};

	void dfs1(int t, int s)
	{
		fa[t] = s;
		sz[t] = 1;
		dep[t] = dep[s] + 1;

		for (auto i: p[t]) {
			if (i == s) continue;
			dfs1(i, t);
			sz[t] += sz[i];
			if (sz[son[t]] < sz[i]) son[t] = i;
		}
	}

	void dfs2(int t, int s)
	{
		top[t] = s;
		if (son[t]) dfs2(son[t], s);

		for (auto i: p[t]) {
			if (i == son[t] || i == fa[t]) continue;
			dfs2(i, i);
		}
	}

	void init(int s)
	{
		dfs1(s, 0);
		dfs2(s, 0);
	}

	int getLCA(int x, int y)
	{
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? x : y;
	}
}pt;

void LCA_double(int s, int fa);
int LCA_double_quiey(int x, int y);
void LCA_Tarjan(int s, int fa);
void LCA_TCS_getSon(int s, int fa);
void LCA_LCS_getTop(int s, int t);
int LCA_LCS_quiey(int x, int y);
int find(int x);

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    int u, v;
    for(int i = 1; i < n; i++) {
    	cin >> u >> v;
    	p[u].push_back(v);
    	p[v].push_back(u);
    }

    //LCA_double(s, 0);
    //iota(F, F + n + 1, 0);
   	LCA_TCS_getSon(s, 0);
   	LCA_LCS_getTop(s, s);

    for(int i = 0; i < m; i++){
    	cin >> u >> v;
    	cout << LCA_LCS_quiey(u, v) << endl;
    	//cout << LCA_double_quiey(u, v) << endl;
    	// Q[u].push_back({v, i});
    	// Q[v].push_back({u, i});
    }

    // LCA_Tarjan(s, 0);
    // for(int i = 0; i < m; i++){
    // 	cout << A[i] << endl;
    // }
    return 0;
}

void LCA_double(int s, int fa)
{
	st[s][0] = fa;
	dp[s] = dp[fa] + 1;
	for(int i = 1; i < 20; i++){
		st[s][i] = st[st[s][i - 1]][i - 1];
		if(st[s][i] == 0) break;
	}

	for(auto i : p[s]){
		if(i == fa) continue;
		LCA_double(i, s);
	}
}

int LCA_double_quiey(int x, int y)
{
	if(dp[x] < dp[y]) swap(x, y);
	for(int i = 19; i >= 0; i--){
		if(dp[st[x][i]] >= dp[y]) x = st[x][i];
	}

	if(x == y) return x;

	for(int i = 19; i >= 0; i--){
		if(st[x][i] != st[y][i]){
			x = st[x][i];
			y = st[y][i];
		}
	}

	return st[x][0];
}

int find(int x)
{
	if(x == F[x]) return x;
	return F[x] = find(F[x]);
}

void LCA_Tarjan(int s, int fa)
{
	V[s] = 1;

	for(auto i : p[s]){
		if(i == fa) continue;
		LCA_Tarjan(i, s);
		F[i] = s;
	}

	for(auto pr: Q[s]){
		int v = pr.first, i = pr.second;
		if(V[v] == 1) A[i] = find(v);
	}
}

void LCA_TCS_getSon(int s, int fa)
{
	sz[s] = 1;
	dp[s] = dp[fa] + 1;
	F[s] = fa;

	int mx = 0;
	for(auto i: p[s]){
		if(i == fa) continue;
		LCA_TCS_getSon(i, s);
		if(mx < sz[i]){
			son[s] = i;
			mx = sz[i];
		}
		sz[s] += sz[i];
	}
}

void LCA_LCS_getTop(int s, int t)
{
	top[s] = t;

	if(son[s]) LCA_LCS_getTop(son[s], t);

	for(auto i: p[s]){
		if(i == F[s] || i == son[s]) continue;
		LCA_LCS_getTop(i, i);
	}
}

int LCA_LCS_quiey(int x, int y)
{
	while(top[x] != top[y]) {
		if(dp[top[x]] < dp[top[y]]) swap(x, y);
		x = F[top[x]];
	}

	return dp[x] > dp[y] ? y : x;
}