#include <bits/stdc++.h>
using namespace std;

// #define lc (t << 1)
// #define rc ((t << 1) | 1)

// struct{
// 	int l, r;
// 	int sum;
// }tr[4000005];

// int A[100005];

// void pushup(int t)
// {
// 	tr[t].sum = max(tr[lc].sum, tr[rc].sum);
// }

// void build(int t, int l, int r)
// {
// 	tr[t].l = l, tr[t].r = r;
// 	if(l == r){
// 		tr[t].sum = A[l];
// 		return;
// 	}
// 	int mid = l + r >> 1;
// 	build(lc, l, mid);
// 	build(rc, mid + 1, r);
// 	pushup(t);
// }

// int query(int t, int l, int r)
// {
// 	if(l <= tr[t].l && r >= tr[t].r) return tr[t].sum;
// 	int mid = tr[t].l + tr[t].r >> 1, ans = 0;
// 	if(l <= mid) ans = max(ans, query(lc, l, r));
// 	if(r > mid) ans = max(ans, query(rc, l, r));
// 	return ans;
// }

int st[100005][20] = {{0}};

inline int read()
{
	bool f = 0;
	int x = 0;
	char ch = getchar();

	while(!isdigit(ch)){
		f = ch == '-';
		ch = getchar();
	}

	while(isdigit(ch)){
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}

	return f == 0 ? x : -x;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	n = read();
	m = read();

	for(int i = 1; i <= n; i++) st[i][0] = read();
	for(int j = 1; j < 20; j++){
		for(int i = 1; i + (1 << j) - 1 <= n; i++){
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	//build(1, 1, n);
	int l, r;
	while(m--){
		l = read();
		r = read();
		int k = log2(r - l + 1);
		cout << max(st[l][k], st[r - (1 << k) + 1][k]) << '\n';
		//cout << query(1, l, r) << '\n';
	}
	return 0;
}