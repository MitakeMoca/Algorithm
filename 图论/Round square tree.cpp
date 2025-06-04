#include <bits/stdc++.h>
using namespace std;

int h1[20005] = {0};
int h2[20005] = {0};
int e1[100005] = {0};
int e2[100005] = {0};
int ne1[100005] = {0};
int ne2[100005] = {0};
long long W1[100005] = {0};
long long W2[100005] = {0};
int dfn[20005] = {0};
int low[20005] = {0};
int fa[20005] = {0};
long long sumC[20005] = {0};
long long C[20005] = {0};
long long fw[20005] = {0};
int fe[20005] = {0};
long long d[200005] = {0};
int dp[200005] = {0};
int p[200005][20] = {0};
int id1 = 1, id2 = 0, l = 1, cn;
int A, B;

void add1(int a, int b, long long w);
void add2(int a, int b, long long w);
void buildTree(long long w, int u, int v);
void Tarjan(int x, int m);
void dfs(int x);
int LCA(int a, int b);

int main()
{
	int n, m, q;
	int u, v;
	long long w;
	scanf("%d%d%d", &n, &m, &q);
	cn = n;
	for(int i = 0; i < m; i++){
		scanf("%d%d%lld", &u, &v, &w);
		add1(u, v, w);
		add1(v, u, w);
	}
	Tarjan(1, 0);
	dp[1] = 1;
	dfs(1);
	for(int i = 0; i < q; i++){
		scanf("%d%d", &u, &v);
		int O = LCA(u, v);
		if(O <= n){
			printf("%lld\n", d[u] + d[v] - 2*d[O]);
		}
		else{
			long long lp = abs(C[A] - C[B]);
			long long temp = min(lp, sumC[A] - lp);
			printf("%lld\n", temp + d[u] + d[v] - d[A] - d[B]);
		}
	}
	return 0;
}

void add1(int a, int b, long long w)
{
	e1[++id1] = b;
	ne1[id1] = h1[a];
	h1[a] = id1;
	W1[id1] = w;
}

void add2(int a, int b, long long w)
{
	e2[++id2] = b;
	ne2[id2] = h2[a];
	h2[a] = id2;
	W2[id2] = w;
} 

void Tarjan(int x ,int m)
{
	int b, c;
	dfn[x] = low[x] = l++;
	for(b = h1[x]; b != 0; b = ne1[b]){
		c = e1[b];
		if(dfn[c] == 0){
			fw[c] = W1[b];
			fe[c] = b;
			fa[c] = x;
			Tarjan(c, b);
			low[x] = min(low[x], low[c]);
			if(dfn[x] < low[c]){
				add2(x, c, fw[c]);
			}
		}
		else if((b ^ 1) != m){
			low[x] = min(low[x], dfn[c]);
		}
	}
	for(b = h1[x]; b != 0; b = ne1[b]){
		c = e1[b];
		if(dfn[c] > dfn[x] && b != fe[c]){
			buildTree(W1[b], x, c);
		}
	}
}

void buildTree(long long w, int u, int v)
{
	int b, c;
	long long sum = w;
	for(b = v; b != u; b = fa[b]){
		C[b] = sum;
		sum += fw[b];
	}
	add2(u, ++cn, 0);
	for(b = v; b != u; b = fa[b]){
		sumC[b] = sum;
		add2(cn, b, min(sum - C[b], C[b]));
	}
}

void dfs(int x)
{
	int b, c;
	for(int i = 1; i < 20; i++){
		p[x][i] = p[p[x][i - 1]][i - 1];
	}
	for(b = h2[x]; b != 0; b = ne2[b]){
		c = e2[b];
		dp[c] = dp[x] + 1;
		d[c] = d[x] + W2[b];
		p[c][0] = x;
		dfs(c);
	}
}

int LCA(int a, int b)
{
	if(dp[a] < dp[b]) swap(a, b);
	while(dp[a] > dp[b]) {
		for(int i = 19; i >= 0; i--){
			if(dp[p[a][i]] >= dp[b]) a = p[a][i];
		}
	}
	if(a == b) return a;
	for(int i = 19; i >= 0; i--){
		if(p[a][i] != p[b][i]){
			a = p[a][i];
			b = p[b][i];
			
		}
	}
	A = a;
	B = b;
	return p[a][0];
}
