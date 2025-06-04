#include <bits/stdc++.h>
using namespace std;

#define INF 1e18

long long W[505][505];
long long la[505];
long long lb[505] = {0};
long long d[505];
int match[505] = {0};
int va[505] = {0};
int vb[505] = {0};
int pre[505] = {0};

void KM(int n);
bool dfs(int t, int n);
void bfs(int t, int n);
long long KM_bfs(int n);

int main()
{
	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			W[i][j] = -INF;
		}
	}

	int u, v;
	long long w;
	while(m--){
		cin >> u >> v >> w;
		W[u][v] = w;
	}

	//KM(n);
	long long ans = KM_bfs(n);
	cout << ans << endl;
	for(int i = 1; i <= n; i++){
		cout << match[i] << ' ';
	}
	return 0;
}

bool dfs(int t, int n)
{
	va[t] = 1;
	for(int j = 1; j <= n; j++){
		if(vb[j] == 0){
			if(la[t] + lb[j] == W[t][j]){
				vb[j] = 1;
				if(match[j] == 0 || dfs(match[j], n)){
					match[j] = t;
					return true;
				}
			}
			else d[j] = min(d[j], la[t] + lb[j] - W[t][j]);
		}
	}
	return false;
}


void KM(int n)
{
	for(int i = 1; i <= n; i++) la[i] = -INF;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			la[i] = max(la[i], W[i][j]);
		}
	}

	for(int i = 1; i <= n; i++){
		while(1){
			for(int j = 1; j <= n; j++) va[j] = 0;
			for(int j = 1; j <= n; j++) vb[j] = 0;
			for(int j = 1; j <= n; j++) d[j] = INF;
			if(dfs(i, n)) break;
			long long delta = INF;
			for(int j = 1; j <= n; j++){
				if(vb[j] == 0) delta = min(delta, d[j]);
			}
			for(int j = 1; j <= n; j++){
				if(va[j] == 1) la[j] -= delta;
				if(vb[j] == 1) lb[j] += delta;
			}
		}
	}

	long long ans = 0;
	for(int i = 1; i <= n; i++){
		ans += W[match[i]][i];
	}
	cout << ans << endl;
	for(int i = 1; i <= n; i++){
		cout << match[i] << ' ';
	}
}

void bfs(int t, int n)
{
	int x, y = 0, yy = 0;
	long long delta;
	for(int i = 0; i <= n; i++) pre[i] = 0;
	for(int i = 1; i <= n; i++) d[i] = INF;
	match[y] = t;
	while(1){
		x = match[y];
		delta = INF;
		vb[y] = 1;
		for(int i = 1; i <= n; i++){
			if(vb[i] == 1) continue;
			if(d[i] > la[x] + lb[i] - W[x][i]){
				d[i] = la[x] + lb[i] - W[x][i];
				pre[i] = y;
			}
			if(d[i] < delta){
				delta = d[i];
				yy = i;
			}
		}
		for(int i = 0; i <= n; i++){
			if(vb[i] == 1) la[match[i]] -= delta, lb[i] += delta;
			else d[i] -= delta;
		}
		y = yy;
		if(match[y] == -1) break;
	}
	while(y){
		match[y] = match[pre[y]];
		y = pre[y];
	}
}

long long KM_bfs(int n)
{
	for(int i = 0; i <= n; i++) match[i] = -1;
	for(int i = 0; i <= n; i++) la[i] = 0;
	for(int i = 0; i <= n; i++) lb[i] = 0;

	for(int i = 1; i <= n; i++){
		for(int i = 0; i <= n; i++) vb[i] = 0;
		bfs(i, n);
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		if(match[i] != -1) ans += W[match[i]][i];
	}
	return ans;
}