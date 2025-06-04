#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]

struct {
	int son[2];
	int sum;
}tr[4000005];

int A[200005] = {0};
int B[200005] = {0};
int rt[200005] = {0};
int id = 0;

void pushup(int t)
{
	tr[t].sum = tr[lc(t)].sum + tr[rc(t)].sum;
}

void insert(int x, int &y, int l, int r, int pos)
{
	y = ++id;
	tr[y] = tr[x];
	if (l == r) {
		tr[y].sum++;
		return;
	}
	int m = l + r >> 1;
	if (pos <= m) insert(lc(x), lc(y), l, m, pos);
	else insert(rc(x), rc(y), m + 1, r, pos);
	pushup(y);
}

int query(int x, int y, int l, int r, int k)
{
	if (l == r) return l;
	int m = l + r >> 1, temp = tr[lc(y)].sum - tr[lc(x)].sum;

	if (k <= temp) return query(lc(x), lc(y), l, m, k);
	else return query(rc(x), rc(y), m + 1, r, k - temp);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		B[i] = A[i];
	}

	sort(B + 1, B + n + 1);
	int s = unique(B + 1, B + n + 1) - B - 1;

	for (int i = 1; i <= n; i++) {
		int t = lower_bound(B + 1, B + s + 1, A[i]) - B;
		insert(rt[i - 1], rt[i], 1, s, t);
	}

	int l, r, k;
	while (m--) {
		cin >> l >> r >> k;
		cout << B[query(rt[l - 1], rt[r], 1, s, k)] << '\n';
	}
	return 0;
}