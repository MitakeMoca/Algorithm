#include <bits/stdc++.h>
using namespace std;

int ch[20000000][2] = {0};
int sz[20000000] = {0};

void insert(int x, int &y, int t);
int query(int x, int y, int t);

int S[600005] = {0};
int root[600005] = {0};
int id = 0;

int main()
{
	int n, m, a;
	cin >> n >> m;

	for(int i = 1; i <= n; i++){
		cin >> a;
		S[i] = S[i - 1] ^ a;
	}

	insert(root[0], root[1], 0);
	for(int i = 1; i <= n; i++){
		insert(root[i], root[i + 1], S[i]);
	} 

	char ch;
	int l, r, x;
	while(m--){
		cin >> ch;
		if(ch == 'A'){
			cin >> x;
			n++;
			S[n] = S[n - 1] ^ x;
			insert(root[n], root[n + 1], S[n]);
		}
		if(ch == 'Q'){
			cin >> l >> r >> x;
			cout << query(root[l - 1], root[r], x ^ S[n]) << endl;
		}
	}
	return 0;
}

void insert(int x, int &y, int t)
{
	y = ++id;
	int k = y;
	for(int i = 29; i >= 0; i--){
		int j = t >> i & 1;
		ch[k][!j] = ch[x][!j];
		ch[k][j] = ++id;
		x = ch[x][j];
		k = ch[k][j];
		sz[k] = sz[x] + 1;
	}
}

int query(int x, int y, int t)
{
	int ans = 0;
	for(int i = 29; i >= 0; i--){
		int j = t >> i & 1;
		if(sz[ch[y][!j]] - sz[ch[x][!j]] != 0){
			y = ch[y][!j];
			x = ch[x][!j];
			ans |= (1 << i);
		}
		else{
			y = ch[y][j];
			x = ch[x][j];
		}
	}
	return ans;
}