#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc ((t << 1) | 1)

struct Line{
	int x1, x2, y;
	int tag;
	bool operator < (const Line &th) const
	{
		return y < th.y;
	}
}L[200005];

struct Seg{
	int l, r;
	int cnt, len;
}seg[1600005];

int X[200005];

void build(int t, int l, int r);
void modify(int t, int l, int r, int tag);
void pushup(int t);

int main()
{
	int n;
	cin >> n;

	int x1, y1, x2, y2;
	for(int i = 1; i <= n; i++){
		cin >> x1 >> y1 >> x2 >> y2;
		L[i] = {x1, x2, y1, 1};
		L[i + n] = {x1, x2, y2, -1};
		X[i] = x1, X[i + n] = x2;
	}
	n *= 2;
	sort(L + 1, L + n + 1);
	sort(X + 1, X + n + 1);
	int s = unique(X + 1, X + n + 1) - X - 1;
	build(1, 1, s - 1);

	long long ans = 0;
	for(int i = 1; i < n; i++){
		int l = lower_bound(X + 1, X + s + 1, L[i].x1) - X;
		int r = lower_bound(X + 1, X + s + 1, L[i].x2) - X;
		modify(1, l, r - 1, L[i].tag);
		ans += 1ll * seg[1].len * (L[i + 1].y - L[i].y);
	}
	cout << ans;
	return 0;
}

void build(int t, int l, int r)
{
	seg[t] = {l, r, 0, 0};
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
}

void modify(int t, int l, int r, int tag)
{
	if(l <= seg[t].l && r >= seg[t].r){
		seg[t].cnt += tag;
		pushup(t);
		return;
	}
	int mid = (seg[t].l + seg[t].r) >> 1;
	if(l <= mid) modify(lc, l, r, tag);
	if(r > mid) modify(rc, l, r, tag);
	pushup(t);
}

void pushup(int t)
{
	int l = seg[t].l, r = seg[t].r;
	if(seg[t].cnt) seg[t].len = X[r + 1] - X[l];
	else seg[t].len = seg[lc].len + seg[rc].len;
}