#include <bits/stdc++.h>
using namespace std;

vector<int> p[100005];
int st[100005][20] = {0};
int dep[100005] = {0};
int dfn[100005] = {0};
int cnt = 0;

int h[100005] = {0};
int ne[100005] = {0};
int sz[100005] = {0};
int e[100005] = {0};
int A[100005] = {0};
int id = 0;

int stk[100005] = {0};
int top = 0, ans = 0;

bool cmp(int a, int b)
{
	return dfn[a] < dfn[b];
}

void add(int a, int b)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
}

void dfs(int t, int fa)
{
	dfn[t] = ++cnt;
	dep[t] = dep[fa] + 1;
	st[t][0] = fa;

	for(int i = 1; i < 20; i++){
		st[t][i] = st[st[t][i - 1]][i - 1];
	}

	for(auto i: p[t]){
		if(i == fa) continue;
		dfs(i, t);
	}
}

int getLCA(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i--){
		if(dep[st[x][i]] >= dep[y]) x = st[x][i];
	}

	if(x == y) return x;
	for(int i = 19; i >= 0; i--){
		if(st[x][i] != st[y][i]){
			x = st[x][i], y = st[y][i];
		}
	}
	return st[x][0];
}

void build(int k)
{
	sort(A, A + k, cmp);
	id = 0, top = 0;

	stk[++top] = 1;
	if(A[0] != 1) stk[++top] = A[0];

	for(int i = 1; i < k; i++){
		int l = getLCA(stk[top], A[i]);
		while(top > 1 && dep[stk[top - 1]] >= dep[l]){
			add(stk[top - 1], stk[top]);
			top--;
		}
		if(stk[top] != l){
			add(l, stk[top]);
			stk[top] = l;
		}
		stk[++top] = A[i];
	}

	while(top > 1){
		add(stk[top - 1], stk[top]);
		top--;
	}
}

void DP(int t)
{
	//cout << t << ' ' << sz[t] << '\n';
	if(sz[t] == 1) {
		for(int b = h[t]; b != 0; b = ne[b]){
			int c = e[b];
			DP(c);
			if(sz[c] == 1) ans++, sz[c] = 0;
		}
	}
	else{
		for(int b = h[t]; b != 0; b = ne[b]){
			int c = e[b];
			DP(c);
			sz[t] += sz[c];
			sz[c] = 0;
		}
		if(sz[t] > 1) ans++, sz[t] = 0;
	}
	h[t] = 0;
}

void solve(int n)
{
	int k;
	cin >> k;

	ans = 0, sz[1] = 0;

	for(int i = 0; i < k; i++){
		cin >> A[i];
		sz[A[i]] = 1;
	}

	for(int i = 0; i < k; i++){
		if(sz[st[A[i]][0]] == 1){
			for(int j = 0; j < k; j++){
				sz[A[j]] = 0;		
			}
			cout << -1 << '\n';
			return;
		}
	}

	build(k);
	DP(1);
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	int u, v;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}
	dfs(1, 0);

	int q;
	cin >> q;
	while(q--){
		solve(n);
	}

	return 0;
}