#include <bits/stdc++.h>
using namespace std;

int fa[10005] = {0};

int find(int x);

int main()
{
	int n, m;
	cin >> n >> m;

	iota(fa, fa + n + 1, 0);

	int op, x, y;
	while(m--) {
		cin >> op >> x >> y;
		int a = find(x), b = find(y);
		if(op == 2) {
			a == b ? puts("Y") : puts("N");
		}
		else{
			fa[a] = b;
		}
	}
	return 0;
}

int find(int x)
{
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}