#include <bits/stdc++.h>
using namespace std;

int son[6000005][2] = {{0}};
int rt = 1, id = 1;
int L[6000005] = {0}, R[6000005] = {0};
int A[200005] = {0};

void insert(int x, int pos)
{
	int t = rt;
	for (int i = 30; i >= 0; i--) {
		int j = ((x >> i) & 1);
		if (son[t][j] == 0) son[t][j] = ++id;
		t = son[t][j];
		L[t] = min(L[t], pos);
		R[t] = max(R[t], pos);
	}
}

int query(int x, int dep, int now)
{
	int ans = (1 << dep);
	for (int i = dep - 1; i >= 0; i--) {
		int j = ((x >> i) & 1);
		if (son[now][j] != 0) {
			now = son[now][j];
		}
		else {
			now = son[now][j ^ 1];
			ans += 1 << i;
		}
	}
	return ans;
}

long long dfs(int now, int dep)
{
	if (dep < 0) return 0;
	if (son[now][0] != 0 && son[now][1] != 0) {
		int mn = (1 << 30);
		for (int i = L[son[now][1]]; i <= R[son[now][1]]; i++) 
			mn = min(mn, query(A[i], dep, son[now][0]));
		return dfs(son[now][0], dep - 1) + dfs(son[now][1], dep - 1) + mn;
	}
	if (son[now][0]) return dfs(son[now][0], dep - 1);
	if (son[now][1]) return dfs(son[now][1], dep - 1);
	return 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> A[i];

	sort(A, A + n);
	memset(L, 0x3f, sizeof(L));
	for (int i = 0; i < n; i++) {
		insert(A[i], i);
	}

	cout << dfs(rt, 30) << '\n';
	return 0;
}