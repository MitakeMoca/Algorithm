#include <bits/stdc++.h>
using namespace std;

vector<int> p[100005];

int son[100005] = {0};
int sz[100005] = {0};
int w[100005] = {0};
int cnt[100005] = {0};

long long ans[100005] = {0};
long long sum = 0, mx = 0;

void dfs(int t, int fa)
{
	sz[t] = 1;
	for(auto i: p[t]){
		if(i == fa) continue;
		dfs(i, t);
		sz[t] += sz[i];
		if(sz[son[t]] < sz[i]) son[t] = i;
	}
}

void add(int t, int fa, int s)
{
	cnt[w[t]]++;
	if(cnt[w[t]] > mx) mx = cnt[w[t]], sum = w[t];
	else if(cnt[w[t]] == mx) sum += w[t];

	for(auto i: p[t]){
		if(i == fa || i == s) continue;
		add(i, t, s);
	}
}

void sub(int t, int fa)
{
	cnt[w[t]]--;
	for(auto i: p[t]){
		if(i == fa) continue;
		sub(i, t);
	}
}

void dfs2(int t, int fa, int op)
{
	for(auto i: p[t]){
		if(i == fa || i == son[t]) continue;
		dfs2(i, t, 0);
	}
	if(son[t] != 0) dfs2(son[t], t, 1);

	add(t, fa, son[t]);
	ans[t] = sum;
	if(op == 0) sub(t, fa), sum = mx = 0; 
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

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
	dfs2(1, 0, 1);
	for(int i = 1; i <= n; i++){
		cout << ans[i] << ' ';
	}
	return 0;
}