#include <bits/stdc++.h>
using namespace std;

#define lc(t) tr[t].son[0]
#define rc(t) tr[t].son[1]
#define fa(t) tr[t].father

struct {
	int son[2];
	int value;
	int father;
	int sz;
	int cnt;
}tr[100005];
int rt = 0, id = 0;

void pushup(int t)
{
	tr[t].sz = tr[lc(t)].sz + tr[rc(t)].sz + tr[t].cnt;
}

void rotate(int x)
{
	int y = fa(x);
	int z = fa(y);

	int t = (rc(y) == x);
	tr[y].son[t] = tr[x].son[t ^ 1];
	fa(tr[x].son[t ^ 1]) = y;
	tr[x].son[t ^ 1] = y;
	fa(y) = x;
	tr[z].son[rc(z) == y] = x;
	fa(x) = z;

	pushup(y);
	pushup(x);
}

void splay(int x, int k)
{
	while (fa(x) != k) {
		int y = fa(x);
		int z = fa(y);

		if (z != k)
			(lc(z) == y ^ lc(y) == x) ? rotate(x) : rotate(y);
		rotate(x);
	}
	if (k == 0) rt = x;
}

void find(int v)
{
	int t = rt;
	while (tr[t].value != v && tr[t].son[tr[t].value < v])
		t = tr[t].son[tr[t].value < v];
	splay(t, 0);
}

int get_pre(int v)
{
	find(v);
	int t = rt;

	if (tr[t].value < v) return t;
	t = lc(t);

	while (rc(t)) t = rc(t);
	splay(t, 0);
	return t;
}

int get_suc(int v)
{
	find(v);
	int t = rt;

	if (tr[t].value > v) return t;
	t = rc(t);

	while (lc(t)) t = lc(t);
	splay(t, 0);
	return t;
}

void del(int v)
{
	int pre = get_pre(v);
	int suc = get_suc(v);

	splay(pre, 0);
	splay(suc, pre);

	int t = lc(suc);
	if (tr[t].cnt > 1) {
		tr[t].cnt--;
		splay(t, 0);
	}
	else {
		lc(suc) = 0;
		splay(suc, 0);
	}
}

int get_rank(int v)
{
	int pre = get_pre(v);
	return tr[pre].sz - tr[rc(pre)].sz;
}

int get_val(int k)
{
	k++;
	int t = rt;
	while (1) {
		int y = lc(t);
		if (tr[y].sz >= k) t = y;
		else if (tr[y].sz + tr[t].cnt < k) {
			k -= tr[y].sz + tr[t].cnt;
			t = rc(t);
		}
		else break;
	}
	splay(t, 0);
	return tr[t].value;
}

void insert(int v)
{
	int t = rt, f = 0;
	while (tr[t].value != v && t != 0) {
		f = t;
		t = tr[t].son[tr[t].value < v];
	}
	if (t) tr[t].cnt++;
	else {
		t = ++id;
		tr[f].son[tr[f].value < v] = t;
		tr[t].sz = 1;
		tr[t].cnt = 1;
		tr[t].value = v;
		fa(t) = f;
	}
	splay(t, 0);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	insert(1e9);
	insert(-1e9);

	int n, op, a;
	cin >> n;

	while(n--){
		cin >> op >> a;
		switch(op){
			case 1:
				insert(a);
				break;
			case 2:
				del(a);
				break;
			case 3:
				cout << get_rank(a) << '\n';
				break;
			case 4:
				cout << get_val(a) << '\n';
				break;
			case 5:
				cout << tr[get_pre(a)].value << '\n';
				break;
			case 6:
				cout << tr[get_suc(a)].value << '\n';
				break;
		}
	}
	return 0;
}