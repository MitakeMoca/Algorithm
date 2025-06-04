#include <bits/stdc++.h>
using namespace std;

#define INF 2147483647

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]
#define ld (i << 1)
#define rd ((i << 1) | 1)

struct{
	int v;
	int son[2];
	int sz;
	int p;
	int cnt;
}tr[30000000];

int id = 0;
int rt[10000000] = {0};
int A[10000000] = {0};

inline void rotate(int x);
inline void splay(int t, int x, int k);
inline void pushup(int x);
inline void insert(int t, int v);
void build(int i, int l, int r);
inline int get_rank(int t, int v);
int query_rank(int i, int l, int r, int x, int y, int v);
int query_val(int i, int x, int y, int k, int n);
void change(int i, int l, int r, int pos, int v);
inline int get_pre(int t, int v);
inline int get_suc(int t, int v);
inline void del(int t, int v);
inline int find(int t, int v);
int query_pre(int i, int l, int r, int x, int y, int v);
int query_suc(int i, int l, int r, int x, int y, int v);

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
	return f == 1 ? -x : x;
}

void printBST(int t){
	if(lc(t)) printBST(lc(t));
	printf("%d ", tr[t].v);
	if(rc(t)) printBST(rc(t));
}

void printSeg(int i, int l, int r)
{
	int mid = l + r >> 1;
	if(l != r) printSeg(ld, l, mid);
	printBST(rt[i]);
	puts("");
	if(l != r) printSeg(rd, mid + 1, r);
} 

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, m;
	n = read();
	m = read();

	for(int i = 1; i <= n; i++){
		A[i] = read();
	}

	build(1, 1, n);

	int op, l, r, pos, x;
	while(m--){
		op = read();
		switch(op){
		case 1:
			l = read(); r = read(); x = read();
			printf("%d\n",query_rank(1, 1, n, l, r, x) + 1);
			break;
		case 2:
			l = read(); r = read(); x = read();
			printf("%d\n",query_val(1, l, r, x, n));
			break;
		case 3:
			pos = read(); x = read();
			change(1, 1, n, pos, x);
			A[pos] = x;
			break;
		case 4:
			l = read(); r = read(); x = read();
			printf("%d\n",query_pre(1, 1, n, l, r, x));
			break;
		case 5:
			l = read(); r = read(); x = read();
			printf("%d\n",query_suc(1, 1, n, l, r, x));
			break;
		}
	}
	return 0;
}

inline void rotate(int x)
{
	int y = tr[x].p;
	int z = tr[y].p;
	int t = tr[y].son[1] == x;

	tr[y].son[t] = tr[x].son[t ^ 1];
	tr[tr[x].son[t ^ 1]].p = y;
	tr[x].son[t ^ 1] = y;
	tr[y].p = x;
	tr[x].p = z;
	tr[z].son[tr[z].son[1] == y] = x;

	pushup(y);
	pushup(x);
}

inline void pushup(int x)
{
	tr[x].sz = tr[lc(x)].sz + tr[rc(x)].sz + tr[x].cnt;
}

inline void splay(int t, int x, int k)
{
	while(tr[x].p != k){
		
		int y = tr[x].p;
		int z = tr[y].p;

		if(z != k){
			((lc(z) == y) ^ (lc(y) == x)) ? rotate(x) : rotate(y);
		}
		rotate(x);
	}
	
	if(k == 0) rt[t] = x;
}

inline void insert(int t, int v)
{
	int x = rt[t], p = 0;
	while(x != 0 && tr[x].v != v){
		p = x;
		x = tr[x].son[v > tr[x].v];		
	}
	if(x != 0) tr[x].cnt++;
	else{
		x = ++id;
		tr[p].son[v > tr[p].v] = x;
		tr[x].p = p;
		tr[x].v = v;
		tr[x].cnt = 1; 	
			
	}
	splay(t, x, 0);
}

void build(int i, int l, int r)
{
	insert(i, -INF);
	insert(i, INF);

	for(int j = l; j <= r; j++) insert(i, A[j]);
	if(l == r) return;
	
	int mid = l + r >> 1;
	build(ld, l, mid);
	build(rd, mid + 1, r);
}

inline int get_rank(int t, int v)
{
	int x = rt[t], res = 0;
	while(x != 0){
		if(tr[x].v < v){
			res += tr[lc(x)].sz + tr[x].cnt;
			x = rc(x);
		}
		else x = lc(x);
	}
	return res;
}

int query_rank(int i, int l, int r, int x, int y, int v)
{
	if(l >= x && r <= y) return get_rank(i, v) - 1;
	int mid = l + r >> 1;

	int res = 0;
	if(x <= mid) res += query_rank(ld, l, mid, x, y, v);
	if(y > mid) res += query_rank(rd, mid + 1, r, x, y, v);
	return res;
}

int query_val(int i, int x, int y, int k, int n)
{
	int l = 0, r = 1e8, ans;
	while(l <= r){
		int mid = l + r >> 1;
		if(query_rank(1, 1, n, x, y, mid) + 1 <= k){
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	return ans;
}

inline int find(int t, int v)
{
	int x = rt[t];
	while(tr[x].v != v && tr[x].son[v > tr[x].v]) x = tr[x].son[v > tr[x].v];
	splay(t, x, 0);
	return x;
}

inline int get_pre(int t, int v)
{
	find(t, v);

	int x = rt[t];
	if(tr[x].v < v) return x;
	x = lc(x);
	while(rc(x)) x = rc(x);
	return x;
}

inline int get_suc(int t, int v)
{
	find(t, v);

	int x = rt[t];
	if(tr[x].v > v) return x;
	x = rc(x);
	while(lc(x)) x = lc(x);
	return x;
}

inline void del(int t, int v)
{
	int pre = get_pre(t, v);
	int suc = get_suc(t, v);

	splay(t, pre, 0);
	splay(t, suc, pre);

	int x = lc(suc);
	if(tr[x].cnt == 1){
		lc(suc) = 0;
		splay(t, suc, 0);
	}
	else{
		tr[x].cnt--;
		splay(t, x, 0);
	}
}

void change(int i, int l, int r, int pos, int v)
{
	del(i, A[pos]);
	insert(i, v);

	if(l == r) return;

	int mid = l + r >> 1;
	if(pos <= mid) change(ld, l, mid, pos, v);
	else change(rd, mid + 1, r, pos, v);
}

int query_pre(int i, int l, int r, int x, int y, int v)
{
	if(l >= x && r <= y) return tr[get_pre(i, v)].v;

	int mid = l + r >> 1;
	int res = -INF;

	if(x <= mid) res = max(res, query_pre(ld, l, mid, x, y, v));
	if(y > mid) res = max(res, query_pre(rd, mid + 1, r, x, y, v));
	return res;
}

int query_suc(int i, int l, int r, int x, int y, int v)
{
	if(l >= x && r <= y) return tr[get_suc(i, v)].v;

	int mid = l + r >> 1;
	int res = INF;

	if(x <= mid) res = min(res, query_suc(ld, l, mid, x, y, v));
	if(y > mid) res = min(res, query_suc(rd, mid + 1, r, x, y, v));
	return res;
}
