#include <bits/stdc++.h>
using namespace std;

#define fa(x) tr[x].p
#define lc(x) tr[x].son[0]
#define rc(x) tr[x].son[1]
#define notroot(x) (lc(fa(x)) == x || rc(fa(x)) == x)

struct{
	int w;
	int sum;
	int tag;
	int p;
	int son[2];
}tr[100005];

void pushup(int t)
{
	tr[t].sum = (tr[lc(t)].sum ^ tr[rc(t)].sum ^ tr[t].w);
}

void pushdown(int t)
{
	if (tr[t].tag != 0) {
		swap(lc(t), rc(t));
		tr[lc(t)].tag ^= 1;
		tr[rc(t)].tag ^= 1;
		tr[t].tag = 0; 
	}
}

void pushall(int t)
{
	if(notroot(t)) pushall(fa(t));
	pushdown(t);
}

void rotate(int x)
{
	int y = fa(x);
	int z = fa(y);

	if (notroot(y))
		tr[z].son[rc(z) == y] = x;
	fa(x) = z;
	int t = (rc(y) == x);
	tr[y].son[t] = tr[x].son[t ^ 1];
	fa(tr[x].son[t ^ 1]) = y;
	tr[x].son[t ^ 1] = y;
	fa(y) = x;

	pushup(y);
	pushup(x);
}

void splay(int x)
{
	pushall(x);
	while (notroot(x)) {
		int y = fa(x);
		int z = fa(y);

		if (notroot(y))
			(rc(z) == y ^ rc(y) == x) ? rotate(x) : rotate(y);
		rotate(x);
	}
}

void access(int x)
{
	for(int y = 0; x; ) {
		splay(x);
		rc(x) = y;
		pushup(x);
		y = x;
		x = fa(x);
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
	tr[x].tag ^= 1;
}

void split(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
}

void output(int x, int y)
{
	split(x, y);
	cout << tr[y].sum << '\n';
}

int findroot(int x)
{
	access(x);
	splay(x);
	while (lc(x)) {
		x = lc(x);
		pushdown(x);
	}
	splay(x);
	return x;
}

void link(int x, int y)
{
	makeroot(x);
	if (findroot(y) != x) fa(x) = y;
}

void cut(int x, int y)
{
	makeroot(x);
	if (findroot(y) == x && fa(y) == x && lc(y) == 0) {
		rc(x) = fa(y) = 0;
		pushup(x);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		cin >> tr[i].w;
		splay(i);
	}

	int op, x, y;
	while(m--){
		cin >> op >> x >> y;
		switch(op){
		case 0:
			output(x, y);
			break;
		case 1:
			link(x, y);
			break;
		case 2:
			cut(x, y);
			break;
		case 3:
			tr[x].w = y;
			splay(x);
			break;
		default:
			break;
		}
	}
	return 0;
}