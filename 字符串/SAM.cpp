#include <bits/stdc++.h>
using namespace std;

int ch[2000005][26] = {{0}};
int fa[2000005] = {0};
int cnt[2000005] = {0};
int len[2000005] = {0};
vector<int> p[2000005];
int id = 1, np = 1;

void extend(char c)
{
	int t = c - 'a';
	int p = np;
	np = ++id;

	len[np] = len[p] + 1, cnt[np] = 1;
	for (; p != 0 && ch[p][t] == 0; p = fa[p]) ch[p][t] = np;

	if (p == 0) fa[np] = 1;
	else {
		int q = ch[p][t];
		if (len[q] == len[p] + 1) fa[np] = q;
		else {
			int nq = ++id;
			len[nq] = len[p] + 1;
			fa[nq] = fa[q];
			fa[q] = nq;
			fa[np] = nq;
			for (; p != 0 && ch[p][t] == q; p = fa[p]) ch[p][t] = nq;
			memcpy(ch[nq], ch[q], sizeof(ch[q]));
		}
	}
}

void dfs(int t)
{
	for (auto i: p[t]) {
		dfs(i);
		cnt[t] += cnt[i];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;

	int n = s.size();
	for (int i = 0; i < n; i++) {
		extend(s[i]);
	}

	for (int i = 2; i <= id; i++) {
		p[fa[i]].push_back(i);
	}
	dfs(1);

	long long ans = 0;
	for (int i = 2; i <= id; i++) {
		if (cnt[i] > 1) ans = max(ans, 1ll * cnt[i] * len[i]);
	}

	cout << ans << '\n';

	return 0;
}