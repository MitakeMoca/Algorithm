#include <bits/stdc++.h>
using namespace std;

int ans = 0, tot = 0;
vector<int> p[20005];
vector<int> np[20005];
vector<int> C[20005];
int dfn[20005] = {0};
int low[20005] = {0};
int stk[20005] = {0};
int instk[200005] = {0};
int scc[200005] = {0};
int dcc[200005] = {0};
int d[200005] = {0};
int sz[200005] = {0};
int cut[200005] = {0};
int h[200005] = {0};
int e[200005] = {0};
int ne[200005] = {0};
int bri[200005] = {0};
int f[200005] = {0};
int ID[200005] = {0};
int id = 1;
int top = 0, cnt = 0, root;

struct Edge{
	int u, v;
	bool operator < (const Edge &t) const
	{
		if(u != t.u) return u < t.u;
		return v < t.v;
	}
}edge[200005];

void add(int a, int b);
void SCC_Tarjan(int t);
void CP_Tarjan(int t);
void CE_Tarjan(int t, int ed);
void eDCC_Tarjan(int t, int ed);
void vDCC_Tarjan(int t);

int main()
{
	int n, m;
	cin >> n >> m;

	int u, v;
	while(m--){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	for(root = 1; root <= n; root++){
		if(dfn[root] == 0) vDCC_Tarjan(root);
	}

	int num = cnt;
	for(int i = 1; i <= n; i++){
		if(cut[i] == 0) ID[i] = ++num;
	}
	for(int i = 1; i <= cnt; i++){
		for(auto j: p[i]){
			if(cut[j]){
				np[i].push_back(ID[j]);
				np[ID[j]].push_back(i);
			}
		}
	}


	// eDCC_Tarjan(1, 0);

	// for(int i = 2; i <= id; i++){
	// 	if(bri[i] == 1) {
	// 		d[dcc[e[i]]]++;
	// 	}
	// }
	// int sum = 0;

	// for(int i = 1; i <= cnt; i++){
	// 	if(d[i] == 1) sum++;
	// }

	// cout << (sum + 1) / 2;

	// CE_Tarjan(1, 0);
	// int ans = 0;
	// for(int i = 2; i <= id; i++){
	// 	if(bri[i] == 1) {
	// 		edge[ans].u = min(f[i], e[i]);
	// 		edge[ans].v = max(f[i], e[i]);
	// 		ans++;
	// 	}
	// }

	// sort(edge, edge + ans);
	// for(int i = 0; i < ans; i++){
	// 	cout << edge[i].u << ' ' << edge[i].v << endl;
	// }

	// for(int i = 1; i <= n; i++){
	// 	if(dfn[i] == 0) {
	// 		root = i;
	// 		CP_Tarjan(i);
	// 		//SCC_Tarjan(i);
	// 	}
	// }

	// int ans = 0;
	// for(int i = 1; i <= n; i++){
	// 	if(cut[i] == 1) ans++;
	// }
	// cout << ans << endl;
	// for(int i = 1; i <= n; i++){
	// 	if(cut[i] == 1) cout << i << ' ';
	// }
	// int ans = 0;
	// for(int i = 1; i <= cnt; i++){
	// 	if(sz[i] > 1) ans++;
	// }
	// cout << ans;
	return 0;
}

void add(int a, int b){
	e[++id] = b;
	ne[id] = h[a];
	f[id] = a;
	h[a] = id;
}

void SCC_Tarjan(int t)
{
	dfn[t] = low[t] = ++tot;
	stk[top++] = t, instk[t] = 1;

	for(auto i : p[t]){
		if(dfn[i] == 0){
			SCC_Tarjan(i);
			low[t] = min(low[t], low[i]);
		}
		else if(instk[i]) low[t] = min(dfn[i], low[t]);
	}

	if(low[t] == dfn[t]){
		cnt++;
		int x;
		do{
			x = stk[--top];
			instk[x] = 0;
			scc[x] = cnt;
			sz[cnt]++;
		}while(x != t);
	}
}

void CP_Tarjan(int t)
{
	dfn[t] = low[t] = ++tot;
	int ch = 0;

	for(auto i: p[t]){
		if(dfn[i] == 0){
			CP_Tarjan(i);
			low[t] = min(low[t], low[i]);
			if(low[i] >= dfn[t]){
				ch++;
				if(t != root || ch > 1){
					cut[t] = 1;
				}
			}
		}
		else low[t] = min(dfn[i], low[t]);
	}
}

void CE_Tarjan(int t, int ed)
{
	dfn[t] = low[t] = ++tot;

	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];

		if(dfn[c] == 0){
			CE_Tarjan(c, b);
			low[t] = min(low[t], low[c]);
			if(low[c] > dfn[t]){
				bri[b] = 1;
			}
		}
		else if((b ^ 1) != ed) low[t] = min(dfn[c], low[t]);
	}
}

void eDCC_Tarjan(int t, int ed)
{
	dfn[t] = low[t] = ++tot;
	stk[top++] = t;

	for(int b = h[t]; b != 0; b = ne[b]){
		int c = e[b];

		if(dfn[c] == 0) {
			eDCC_Tarjan(c, b);
			low[t] = min(low[t], low[c]);
			if(low[c] > dfn[t]){
				bri[b] = bri[b ^ 1] = 1;
			}
		}
		else if((b ^ 1) != ed) low[t] = min(low[t], dfn[c]);
	}

	if(dfn[t] == low[t]){
		cnt++;
		while(1){
			int y = stk[--top];
			dcc[y] = cnt;
			if(t == y) break;
		}
	}
}

void vDCC_Tarjan(int t)
{
	dfn[t] = low[t] = ++tot;
	stk[top++] = t;
	int ch = 0;

	for(auto i: p[t]){
		if(dfn[i] == 0){
			vDCC_Tarjan(i);
			low[t] = min(low[t], low[i]);
			if(low[i] >= dfn[t]){
				ch++;
				if(t != root || ch > 1){
					cut[t] = 1;
				}
				cnt++;
				while(1){
					int y = stk[--top];
					C[cnt].push_back(y);
					if(y == i) break;
				}
				C[cnt].push_back(t);
			}
		}
		else low[t] = min(low[t], dfn[i]);
	}
}