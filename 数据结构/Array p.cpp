#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]

int A[1000005] = {0};
int rt[1000005] = {0};
int id = 0;

struct{
	int son[2];
	int w;
}tr[40000005];

void build(int &t, int l, int r)
{
	t = ++id;
	if (l == r) {
		tr[t].w = A[l];
		return;
	}
	int m = l + r >> 1;
	build(lc(t), l, m);
	build(rc(t), m + 1, r);
}

void modify(int x, int &y, int l, int r, int p, int k)
{
	y = ++id;
	tr[y] = tr[x];

	if (l == r) {
		tr[y].w = k;
		return;
	}

	int m = l + r >> 1;
	if (p <= m) modify(lc(x), lc(y), l, m, p, k);
	else modify(rc(x), rc(y), m + 1, r, p, k);
}

int query(int t, int l, int r, int pos)
{
	if (l == r) return tr[t].w;
	int m = l + r >> 1;

	if (pos <= m) return query(lc(t), l, m, pos);
	else return query(rc(t), m + 1, r, pos);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> A[i];

	build(rt[0], 1, n);

	int op, date, pos, k;
	for (int i = 1; i <= m; i++) {
		cin >> date >> op;
		if (op == 2) {
			cin >> pos;
			cout << query(rt[date], 1, n, pos) << '\n';
			rt[i] = rt[date];
		}
		if (op == 1) {
			cin >> pos >> k;
			modify(rt[date], rt[i], 1, n, pos, k);
		}
	}
	return 0;
}