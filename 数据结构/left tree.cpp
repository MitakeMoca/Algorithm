#include <bits/stdc++.h>
using namespace std;

int fa[400005] = {0};
int dis[400005] = {0};
int lc[400005] = {0};
int rc[400005] = {0};
int w[400005] = {0};

int merge(int x, int y)
{
	if(x == 0 || y == 0) return x + y;
	if(w[x] == w[y] ? x > y : w[x] > w[y]) swap(x, y);
	rc[x] = merge(rc[x], y);

	if(dis[lc[x]] < dis[rc[x]]) swap(lc[x], rc[x]);
	dis[x] = dis[rc[x]] + 1;
	return x;
}

int find(int x)
{
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++) fa[i] = i;
	dis[0] = -1;

	for(int i = 1; i <= n; i++){
		cin >> w[i];
	}

	int op, x, y;
	while(m--){
		cin >> op;
		if(op == 1) {
			cin >> x >> y;
			if(w[x] == -1 || w[y] == -1) continue;
			x = find(x), y = find(y);
			if(x != y) fa[x] = fa[y] = merge(x, y);
		}
		else{
			cin >> x;
			if(w[x] == -1){
				cout << -1 << '\n';
				continue;
			}
			x = find(x);
			cout << w[x] << '\n';
			w[x] = -1;
			fa[x] = fa[rc[x]] = fa[lc[x]] = merge(lc[x], rc[x]);
		}
	}
	return 0;
}