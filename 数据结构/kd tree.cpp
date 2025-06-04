#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].l
#define rc(x) tr[x].r

int K, cur, cnt = 0;
double A = 0.7;
double ans;

struct KD{
	int l, r;
	double val[2];
	double L[2], U[2];
	int sz;
	bool operator < (const KD &th) const
	{
		return val[K] < th.val[K];
	}
}tr[200005];

int g[200005] = {0};

// void pushup(int t)
// {
// 	for(int i = 0; i < 2; i++){
// 		tr[t].L[i] = tr[t].U[i] = tr[t].val[i];

// 		if(lc(t) != 0) {
// 			tr[t].L[i] = min(tr[lc(t)].L[i], tr[t].L[i]);
// 			tr[t].U[i] = max(tr[lc(t)].U[i], tr[t].U[i]);
// 		}

// 		if(rc(t) != 0) {
// 			tr[t].L[i] = min(tr[rc(t)].L[i], tr[t].L[i]);
// 			tr[t].U[i] = max(tr[rc(t)].U[i], tr[t].U[i]);
// 		}
// 	}
// }

// int build(int l, int r, int k)  //方差建树更优
// {
// 	if(l > r) return 0;
// 	int m = l + r >> 1;
// 	K = k;

// 	nth_element(tr + l, tr + m, tr + r + 1);
// 	lc(m) = build(l, m - 1, k ^ 1);
// 	rc(m) = build(m + 1, r, k ^ 1);
// 	pushup(m);
// 	return m;
// }

double sq(double t)
{
	return t * t;
}

double dis2(int t)
{
	double res = 0;
	for(int i = 0; i < 2; i++){
		res += sq(tr[cur].val[i] - tr[t].val[i]);
	}
	return res;
}

double dis(int p)
{
	if(p == 0) return 2e18;
	double res = 0;
	for(int i = 0; i < 2; i++){
		res += sq(max(tr[cur].val[i] - tr[p].U[i], 0.0)) + sq(max(tr[p].L[i] - tr[cur].val[i], 0.0));
	}
	return res;
}

bool cmp(int a, int b)
{
	return tr[a].val[K] < tr[b].val[K];
}

void pushup(int t)
{
	tr[t].sz = tr[lc(t)].sz + tr[rc(t)].sz + 1;
	for(int i = 0; i < 2; i++){
		tr[t].L[i] = tr[t].U[i] = tr[t].val[i];

		if(lc(t) != 0) {
			tr[t].L[i] = min(tr[lc(t)].L[i], tr[t].L[i]);
			tr[t].U[i] = max(tr[lc(t)].U[i], tr[t].U[i]);
		}

		if(rc(t) != 0) {
			tr[t].L[i] = min(tr[rc(t)].L[i], tr[t].L[i]);
			tr[t].U[i] = max(tr[rc(t)].U[i], tr[t].U[i]);
		}
	}
}

int rebuild(int l, int r, int k)
{
	if(l > r) return 0;
	int m = l + r >> 1;
	K = k;

	nth_element(g + l, g + m, g + r + 1, cmp);
	lc(g[m]) = rebuild(l, m - 1, k ^ 1);
	rc(g[m]) = rebuild(m + 1, r, k ^ 1);
	pushup(g[m]);
	return g[m];
}

void dfs(int t)
{
	if(t == 0) return;
	g[++cnt] = t;
	dfs(lc(t));
	dfs(rc(t));
}

void check(int &p, int k)
{
	if(A * tr[p].sz < max(tr[lc(p)].sz, tr[rc(p)].sz)){
		cnt = 0;
		dfs(p);
		p = rebuild(1, cnt, k);
	}
}

void insert(int &p, int k)
{
	if(p == 0){
		p = cur;
		pushup(p);
		return;
	}
	insert(tr[cur].val[k] <= tr[p].val[k] ? lc(p) : rc(p), k ^ 1);
	pushup(p);
	check(p, k);
}

void query(int p)
{
	if(p == 0) return;
	if(p != cur) ans = min(ans, dis2(p));

	double dl = dis(lc(p)), dr = dis(rc(p));
	if(dl < dr){
		if(dl < ans) query(lc(p));
		if(dr < ans) query(rc(p));
	}
	else{
		if(dr < ans) query(rc(p));
		if(dl < ans) query(lc(p));
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	int rt = 0;
	for(int i = 1; i <= n; i++){
		cur = i;
		cin >> tr[i].val[0] >> tr[i].val[1];
		insert(rt, 0);
	}

	
	double res = 2e18;
	for(int i = 1; i <= n; i++){
		cur = i;
		ans = 2e18;
		query(rt);
		res = min(res, ans);
	}

	printf("%.4f", sqrt(res));
	return 0;
}