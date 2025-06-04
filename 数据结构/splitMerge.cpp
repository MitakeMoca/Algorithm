#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]

struct{
	int son[2];
	long long sum;
}tr[10000000];
int root[200005] = {0};
int id = 0;

void pushup(int t)
{
	tr[t].sum = tr[lc(t)].sum + tr[rc(t)].sum;
}

void change(int &t, int l, int r, int pos, long long k)
{
	if(t == 0) t = ++id;
	if(l == r){
		tr[t].sum += k;
		return;
	}
	int m = l + r >> 1;
	if(pos <= m) change(lc(t), l, m, pos, k);
	else change(rc(t), m + 1, r, pos, k);
	pushup(t);
}

int merge(int x, int y, int l, int r)
{
	if(x == 0 || y == 0) return x + y;
	if(l == r){
		tr[x].sum += tr[y].sum;
		return x;
	}
	int m = l + r >> 1;
	lc(x) = merge(lc(x), lc(y), l, m);
	rc(x) = merge(rc(x), rc(y), m + 1, r);
	pushup(x);
	return x;
}

void split(int x, int &y, long long k)
{
	if(x == 0) return;
	y = ++id;
	if(k <= tr[lc(x)].sum) split(lc(x), lc(y), k), swap(rc(x), rc(y));
	else split(rc(x), rc(y), k - tr[lc(x)].sum);
	tr[y].sum = tr[x].sum - k;
	tr[x].sum = k;
}

long long query(int t, int l, int r, int x, int y)
{
	if(x <= l && y >= r) return tr[t].sum;
	int m = l + r >> 1;
	long long ans = 0;
	if(x <= m) ans += query(lc(t), l, m, x, y);
	if(y > m) ans += query(rc(t), m + 1, r, x, y);
	return ans;
}

int queryNum(int t, int l, int r, long long k)
{
	if(l == r) return l;
	int m = l + r >> 1;
	if(k <= tr[lc(t)].sum) return queryNum(lc(t), l, m, k);
	else return queryNum(rc(t), m + 1, r, k - tr[lc(t)].sum);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	int a, cnt = 1;
	for(int i = 1; i <= n; i++){
		cin >> a;
		change(root[cnt], 1, n, i, a);
	}

	int op, x, y, p, t, q;
	long long k;
	while(m--){
		cin >> op;
		if(op == 0){
			cin >> p >> x >> y;
			long long k1 = query(root[p], 1, n, 1, y);
			long long k2 = query(root[p], 1, n, x, y);
			int tmp = 0;
			split(root[p], root[++cnt], k1 - k2);
			split(root[cnt], tmp, k2);
			root[p] = merge(root[p], tmp, 1, n);
		}
		if(op == 1){
			cin >> p >> t;
			root[p] = merge(root[p], root[t], 1, n);
		}
		if(op == 2){
			cin >> p >> x >> q;
			change(root[p], 1, n, q, x);
		}
		if(op == 3){
			cin >> p >> x >> y;
			cout << query(root[p], 1, n, x, y) << '\n';
		}
		if(op == 4){
			cin >> p >> k;
			if(tr[root[p]].sum < k) cout << "-1\n";
			else cout << queryNum(root[p], 1, n, k) << '\n';
		}
	}
	return 0;
}