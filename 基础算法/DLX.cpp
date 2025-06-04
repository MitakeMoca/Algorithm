#include <bits/stdc++.h>
using namespace std;

int cnt;
int u[1000000], d[1000000];
int l[1000000], r[1000000];
int h[1000000] = {0}, s[1000000] = {0};
int row[1000000] = {0}, col[1000000] = {0};
int ans[1000000] = {0};

void init(int m);
void remove(int y);
void resume(int y);
bool dance(int dep);
void link(int x, int y);

int main()
{
	int n, m, a;
	cin >> n >> m;

	init(m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a;
			if(a == 1) link(i, j);
		}
	}
	
	if(!dance(0)) cout << "No Solution!";
	return 0;
}

void init(int m)
{
	for(int i = 0; i <= m; i++){
		u[i] = d[i] = i;
		l[i] = i - 1, r[i] = i + 1;
	}
	l[0] = m, r[m] = 0, cnt = m;
}

void link(int x, int y)
{
	row[++cnt] = x;
	col[cnt] = y;
	s[y]++;

	d[u[y]] = cnt;
	u[cnt] = u[y];
	d[cnt] = y;
	u[y] = cnt;

	if(h[x] == 0) h[x] = l[cnt] = r[cnt] = cnt;
	else{
		r[l[h[x]]] = cnt;
		l[cnt] = l[h[x]];
		r[cnt] = h[x];
		l[h[x]] = cnt;
	}
}

void remove(int y)
{
	r[l[y]] = r[y];
	l[r[y]] = l[y];
	for(int t = d[y]; t != y; t = d[t]){
		for(int i = r[t]; i != t; i = r[i]){
			u[d[i]] = u[i];
			d[u[i]] = d[i];
			s[col[i]]--;
		}
	}
}

void resume(int y)
{
	l[r[y]] = y, r[l[y]] = y;
	for(int t = u[y]; t != y; t = u[t]){
		for(int i = l[t]; i != t; i = l[i]){
			u[d[i]] = i;
			d[u[i]] = i;
			s[col[i]]++;
		}
	}
}

bool dance(int dep)
{
	if(r[0] == 0){
		for(int i = 0; i < dep; i++){
			cout << ans[i] << ' ';
		}
		return true;
	}

	int y = r[0];
	for(int i = r[0]; i != 0; i = r[i]) if(s[i] < s[y]) y = i;

	remove(y);
	for(int t = d[y]; t != y; t = d[t]){
		for(int i = r[t]; i != t; i = r[i]) remove(col[i]);
		ans[dep] = row[t];
		if(dance(dep + 1)) return true;
		for(int i = l[t]; i != t; i = l[i]) resume(col[i]);
	}
	resume(y);
	return false;
}