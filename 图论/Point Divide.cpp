#include <bits/stdc++.h>
using namespace std;

int sum = 0, id = 0, mn, root = 0, cnt = 0, m, INF = 0;
int h[100005] = {0};
int e[100005] = {0};
int ne[100005] = {0};
int dis[100005] = {0};
int pre[100005] = {0};
int W[100005] = {0};
int Q[100005] = {0};
int D[100005] = {0};
int sz[100005] = {0};
int d[100005] = {0};
int J[10000005] = {0};
int ask[105] = {0};
int ans[105] = {0};

void add(int a, int b, int w);
void getroot(int t, int fa);
void getdis(int t, int fa);
void divide(int t);
void calc(int t);

int main()
{
	int n;
	cin >> n >> m;

	int u, v, w;
	for(int i = 1; i < n; i++){
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	sum = n;
	mn = sum + 1;

	for(int i = 0; i < m; i++){
		cin >> ask[i];
		INF = max(INF, ask[i]);
	}

	getroot(1, 0);
	divide(root);

	for(int i = 0; i < m; i++){
		if(ans[i] == 1) puts("AYE");
		else puts("NAY");
	}
	return 0;
}

void add(int a, int b, int w)
{
	e[++id] = b;
	W[id] = w;
	ne[id] = h[a];
	h[a] = id;
}

void getroot(int t, int fa)
{
	sz[t] = 1;
	int s = 0;
	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];
		pre[c] = t;
		if(c == fa || D[c] == 1) continue;
		getroot(c, t);
		sz[t] += sz[c];
		s = max(sz[c], s);
	}
	s = max(sum - sz[t], s);
	if(s < mn) root = t, mn = s;
}

void getdis(int t, int fa)
{
	dis[cnt++] = d[t];
	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];

		if(c == fa || D[c] == 1) continue;
		d[c] = d[t] + W[b];
		getdis(c, t);
	}
}

void divide(int t)
{
	calc(t);
	
	int tmp = sum;
	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];
		if(D[c] == 1) continue;
		if(c != pre[t]) sum = sz[c];
		else sum = tmp - sz[t];
		mn = sum + 1;
		getroot(c, t);
		divide(root);
	}
}

void calc(int t)
{
	D[t] = J[0] = 1;
	int p = 0;

	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];
		if(D[c] == 1) continue;

		cnt = 0;
		d[c] = W[b];
		getdis(c, t);

		for(int i = 0; i < cnt; i++){
			for(int k = 0; k < m; k++){
				if(ask[k] >= dis[i]){
					ans[k] |= J[ask[k] - dis[i]];
				}
			}
		}

		for(int i = 0; i < cnt; i++){
			if(dis[i] <= INF){
				Q[p++] = dis[i];
				J[dis[i]] = 1;
			}
		}
	}

	for(int i = 0; i < p; i++) J[Q[i]] = 0;
}