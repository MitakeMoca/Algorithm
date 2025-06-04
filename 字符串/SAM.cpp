#include <bits/stdc++.h>
using namespace std;

int ch[2000005][26] = {0};
int fa[2000005] = {0};
int cnt[2000005] = {0};
int len[2000005] = {0};
vector<int> T[2000005];
int tot = 1, np = 1;

void setAuto(string s);
void dfs(int t);

int main()
{
	string s;
	cin >> s;
	setAuto(s);

	// long long ans = 0;
	// for(int i = 2; i <= tot; i++){
	// 	if(cnt[i] > 1) ans = max(ans, 1ll * len[i] * cnt[i]);
	// }

	// cout << ans;
	return 0;
}

void setAuto(string s)
{
	for(int i = 0; i < s.size(); i++){
		int t = s[i] - 'a';

		int p = np; np = ++tot;
		len[np] = len[p] + 1, cnt[np] = 1;

		for(; p && !ch[p][t]; p = fa[p]) ch[p][t] = np;

		if(p == 0) fa[np] = 1;
		else if(len[ch[p][t]] == len[p] + 1) fa[np] = ch[p][t];
		else{
			int q = ch[p][t], nq = ++tot;
			len[nq] = len[p] + 1;
			fa[nq] = fa[q], fa[q] = nq, fa[np] = nq;

			for(; p && ch[p][t] == q; p = fa[p]) ch[p][t] = nq;
			memcpy(ch[nq], ch[q], sizeof(ch[q]));
		}
	}
	for(int i = 2; i <= tot; i++) T[fa[i]].push_back(i);
	dfs(1);
}

void dfs(int t)
{
	for(auto i: T[t]){
		dfs(i);
		cnt[t] += cnt[i];
	}
}