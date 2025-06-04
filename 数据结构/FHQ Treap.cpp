#include <bits/stdc++.h>
using namespace std;

#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]

struct{
	int value, key;
	int son[2];
	int sz;
}tr[100005];
int id = 0, rt = 0;

int newnode(int v)
{
	int t = ++id;
	tr[t].value = v;
	tr[t].key = rand();
	tr[t].sz = 1;
	return t;
}

void pushup(int t)
{
	tr[t].sz = tr[lc(t)].sz + tr[rc(t)].sz + 1;
}

void split(int t, int v, int &x, int &y)
{
	if (t == 0) {
		x = y = 0;
		return;
	}
	if (tr[t].value <= v) {
		x = t;
		split(rc(t), v, rc(x), y);
	}
	else {
		y = t;
		split(lc(t), v, x, lc(y));
	}
	pushup(t);
}

int merge(int x, int y)
{
	if (x == 0 || y == 0) return x + y;
	if (tr[x].key < tr[y].key) {
		rc(x) = merge(rc(x), y);
		pushup(x);
		return x;
	}
	else {
		lc(y) = merge(x, lc(y));
		pushup(y);
		return y;
	}
}

void insert(int v)
{
	int x, y, z;
	z = newnode(v);
	split(rt, v, x, y);
	rt = merge(merge(x, z), y);
}

void del(int v)
{
	int x, y, z;
	split(rt, v, x, z);
	split(x, v - 1, x, y);
	y = merge(lc(y), rc(y));
	rt = merge(merge(x, y), z);
}

int get_rank(int v)
{
	int x, y, z;
	split(rt, v - 1, x, y);
	z = tr[x].sz + 1;
	rt = merge(x, y);
	return z;
}

int get_val(int t, int k)
{
	if(tr[lc(t)].sz >= k){
		return get_val(lc(t), k);
	}
	else if(tr[lc(t)].sz + 1 == k){
		return t;
	}
	else{
		return get_val(rc(t), k - tr[lc(t)].sz - 1);
	}
}

int get_pre(int v)
{
	int x, y, z;
	split(rt, v - 1, x, y);
	z = get_val(x, tr[x].sz);
	rt = merge(x, y);
	return z;
}

int get_suc(int v)
{
	int x, y, z;
	split(rt, v, x, y);
	z = get_val(y, 1);
	rt = merge(x, y);
	return z;
}

int main()
{
	int n;
	cin >> n;

	int op, x;
	while(n--){
		cin >> op >> x;
		switch(op){
		case 1:
			insert(x);
			break;
		case 2:
			del(x);
			break;
		case 3:
			cout << get_rank(x) <<endl;
			break;
		case 4:
			cout << tr[get_val(rt, x)].value << '\n';
			break;
		case 5:
			cout << tr[get_pre(x)].value << '\n';
			break;
		case 6:
			cout << tr[get_suc(x)].value << '\n';
		}
	}
	return 0;
}