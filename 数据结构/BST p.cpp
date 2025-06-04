#include <bits/stdc++.h>
using namespace std;

#define lc(x) seg[x].son[0]
#define rc(x) seg[x].son[1]

struct{
	int v, key;
	int son[2];
	int sz;
}seg[20000000];

int root[500005] = {0};

int id = 0;

int newnode(int v);
void split(int p, int v, int &x, int &y);
int merge(int x, int y);
void pushup(int x);
int get_id(int rt, int k);
int get_rank(int rt, int i, int v);
int get_pre(int rt, int i, int v);
int get_suc(int rt, int i, int v);
void insert(int rt, int i, int v);
void del(int rt, int i, int v);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;

	int date, op, x;
	insert(root[0], 0, (1 << 30) - 1 + (1 << 30));
	insert(root[0], 0, (1 << 31) + 1);
	
	for(int i = 1; i <= n; i++){
		cin >> date >> op >> x;
		switch(op){
		case 1:
			insert(root[date], i, x);
			break;
		case 2:
			del(root[date], i, x);
			break;
		case 3:
			cout << get_rank(root[date], i, x) << '\n';
			break;
		case 4:
			cout << seg[get_id(root[date], x + 1)].v << '\n';
			root[i] = root[date];
			break;
		case 5:
			cout << seg[get_pre(root[date], i, x)].v << '\n';
			break;
		case 6:
			cout << seg[get_suc(root[date], i, x)].v << '\n';
			break;
		}
	}
	return 0;
}

void split(int p, int v, int &x, int &y)
{
	if(p == 0){
		x = y = 0;
		return;
	}
	if(seg[p].v <= v){
		x = ++id;
		seg[x] = seg[p];
		split(rc(x), v, rc(x), y);
		pushup(x);
	}
	else{
		y = ++id;
		seg[y] = seg[p];
		split(lc(y), v, x, lc(y));
		pushup(y);
	}
}

int newnode(int v)
{
	int x = ++id;
	seg[x].v = v;
	seg[x].key = rand();
	seg[x].sz = 1;
	return x;
}

void pushup(int x)
{
	seg[x].sz = seg[lc(x)].sz + seg[rc(x)].sz + 1;
}

int merge(int x, int y)
{
	if(x == 0 || y == 0) return x + y;
	if(seg[x].key < seg[y].key){
		rc(x) = merge(rc(x), y);
		pushup(x);
		return x;
	}
	else{
		lc(y) = merge(x, lc(y));
		pushup(y);
		return y;
	}
}

int get_id(int rt, int k)
{
	if(seg[lc(rt)].sz >= k){
		return get_id(lc(rt), k);
	}
	else if(seg[lc(rt)].sz + 1 == k){
		return rt;
	}
	else{
		return get_id(rc(rt), k - seg[lc(rt)].sz - 1);
	}
}

int get_rank(int rt, int i, int v)
{
	int x, y, z;
	split(rt, v - 1, x, y);
	z = seg[x].sz;
	root[i] = merge(x, y);
	return z;
}

int get_pre(int rt, int i, int v)
{
	int x, y, z;
	split(rt, v - 1, x, y);
	z = get_id(x, seg[x].sz);
	root[i] = merge(x, y);
	return z;
}

int get_suc(int rt, int i, int v)
{
	int x, y, z;
	split(rt, v, x, y);
	z = get_id(y, 1);
	root[i] = merge(x, y);
	return z;
}

void insert(int rt, int i, int v)
{
	int x, y, z;
	split(rt, v, x, y);
	z = newnode(v);
	root[i] = merge(merge(x, z), y);
}

void del(int rt, int i, int v)
{
	int x, y, z;
	split(rt, v, x, z);
	split(x, v - 1, x, y);
	root[i] = merge(merge(x, merge(lc(y), rc(y))), z);
}
