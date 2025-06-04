#include <bits/stdc++.h>
using namespace std;

vector<int> p[200005];
int h[200005] = {0};
int e[200005] = {0};
int ne[200005] = {0};
int W[200005] = {0};
int d[200005] = {0};
int cur[200005] = {0};
int match[200005] = {0};
int V[200005] = {0};
int id = 1;

void add(int a, int b, int w);
int Dinic(int s, int t, int n);
int dfs(int s, int t, int m);
bool bfs(int s, int t, int n);
bool Hungarian(int t);

int main()
{
	int n, m, e;
	cin >> n >> m >> e;

	int u, v;
	while(e--){
		cin >> u >> v;
		v = v + n;
		add(u, v, 1);
		add(v, u, 0);
		//p[u].push_back(v);
	}

	for(int i = 1; i <= n; i++){
		add(n + m + 2, i, 1);
		add(i, n + m + 2, 0);
	}

	for(int i = n + 1; i <= n + m; i++){
		add(i, n + m + 1, 1);
		add(n + m + 1, i, 0);
	}

	cout << Dinic(n + m + 2, n + m + 1, n + m + 2);

	// int ans = 0;
	// for(int i = 1; i <= n; i++){
	// 	memset(V + n + 1, 0, m * sizeof(int));
	// 	if(Hungarian(i)) ans++;
	// }

	// cout << ans;
	return 0;
}

bool Hungarian(int t)
{
	for(auto i: p[t]){
		if(V[i] == 1) continue;
		V[i] = 1;

		if(match[i] == 0 || Hungarian(match[i])){
			match[i] = t;
			return true;
		}
	}
	return false;
}

bool bfs(int s, int t, int n)
{
	for(int i = 1; i <= n; i++) d[i] = 0;
	queue<int> q;
	q.push(s);
	d[s] = 1;

	while(!q.empty()){
		int a = q.front();
		q.pop();

		for(int b = h[a]; b != 0; b = ne[b]){
			int c = e[b];

			if(d[c] == 0 && W[b] != 0){
				d[c] = d[a] + 1;
				q.push(c);
				if(c == t) return true;
			}
		}
	}
	return false;
}

void add(int a, int b, int w)
{
	e[++id] = b;
	ne[id] = h[a];
	h[a] = id;
	W[id] = w;
}

int dfs(int s, int t, int m)
{
	if(s == t) return m;

	int sum = 0;
	for(int b = cur[s]; b != 0; b = ne[b]){
		cur[s] = b;
		int c = e[b];

		if(d[c] == d[s] + 1 && W[b] != 0){
			int f = dfs(c, t, min(m, W[b]));
			W[b] -= f;
			W[b ^ 1] += f;
			sum += f;
			m -= f;
			if(m == 0) break;
		}
	}
	if(sum == 0) d[s] = 0;
	return sum;
}

int Dinic(int s, int t, int n)
{
	int ans = 0;
	while(bfs(s, t, n)){
		for(int i = 1; i <= n; i++) cur[i] = h[i];
		ans += dfs(s, t, 1e8);
	}
	return ans;
}