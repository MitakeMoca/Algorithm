#include <bits/stdc++.h>
using namespace std;

#define lc (p << 1)
#define rc ((p << 1) | 1)

typedef struct{
	int l, r;
	long long sum, tag;
}Seg;

Seg seg[2000005];
long long num[500005] = {0};

void buildTree(int p, int l, int r);
void modifyTree(int p, int l, int r, long long k);
long long quiey(int p, int l, int r);
void pushup(int p);
void pushdown(int p);

int main()
{
	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		cin >> num[i];
	}

	buildTree(1, 1, n);

	int op, x, y;
	long long k;

	while(m--) {
		cin >> op >> x >> y;
		if(op == 1){
			modifyTree(1, x, x, y);
		}
		else{
			cout << quiey(1, x, y) << endl;
		}
	}
	return 0;
}

void buildTree(int p, int l, int r)
{
	seg[p].l = l, seg[p].r = r, seg[p].tag = 0, seg[p].sum = 0;
	if(l == r){
		seg[p].sum = num[l];
		return;
	}

	int mid = (l + r >> 1);
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(p);
}

void pushup(int p)
{
	seg[p].sum = seg[lc].sum + seg[rc].sum;
}

void modifyTree(int p, int l, int r, long long k)
{
	if(l <= seg[p].l && r >= seg[p].r){
		seg[p].tag += k;
		seg[p].sum += k * (seg[p].r - seg[p].l + 1);
		return;
	}
	pushdown(p);

	int mid = (seg[p].l + seg[p].r >> 1);
	if(l <= mid) modifyTree(lc, l, r, k);
	if(r > mid) modifyTree(rc, l, r, k);
	pushup(p);
}

void pushdown(int p)
{
	seg[lc].tag += seg[p].tag;
	seg[rc].tag += seg[p].tag;
	seg[lc].sum += seg[p].tag * (seg[lc].r - seg[lc].l + 1);
	seg[rc].sum += seg[p].tag * (seg[rc].r - seg[rc].l + 1);
	seg[p].tag = 0;
}

long long quiey(int p, int l, int r)
{
	if(l <= seg[p].l && r >= seg[p].r){
		return seg[p].sum;
	}
	pushdown(p);

	int mid = (seg[p].l + seg[p].r >> 1);
	long long ans = 0;

	if(l <= mid) ans += quiey(lc, l, r);
	if(r > mid) ans += quiey(rc, l, r);
	pushup(p);
	return ans;
}