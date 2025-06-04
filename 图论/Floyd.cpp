#include <bits/stdc++.h>
using namespace std;

void Floyd();

int main()
{
	Floyd();
	return 0;
}

void Floyd()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 1, vector<int>(n + 1, 10000000));

	int u, v, w;
	while(m--){
		cin >> u >> v >> w;
		G[u][v] = min(G[u][v], w);
		G[v][u] = min(G[v][u], w);
	}

	for(int i = 1; i <= n; i++) G[i][i] = 0;

	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
			}
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout << G[i][j] << ' ';
		}
		puts("");
	}
}