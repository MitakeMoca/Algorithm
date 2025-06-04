#include <bits/stdc++.h>
using namespace std;

int K = 0;

struct Node {
	int l, r, id;
	bool operator < (const Node &th) {
		return l / K != th.l / K ? l / K < th.l / K : r < th.r;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> A(n + 1);
	vector<Node> Q(m);
	vector<long long> cnt(k + 1, 0);
	vector<long long> ans(m);

	K = sqrt(n);

	for (int i = 1; i <= n; i++)
		cin >> A[i];

	for (int i = 0; i < m; i++) {
		Q[i].id = i;
		cin >> Q[i].l >> Q[i].r;
	}



	sort(Q.begin(), Q.end());
	long long sum = 0;

	auto add = [&](long long x) -> void {
		sum += (cnt[x] + 1) * (cnt[x] + 1) - cnt[x] * cnt[x];
		cnt[x]++;
	};

	auto sub = [&](long long x) -> void {
		cnt[x]--;
		sum -= (cnt[x] + 1) * (cnt[x] + 1) - cnt[x] * cnt[x];
	};

	int l = 1, r = 0;
	for (int i = 0; i < m; i++) {
		while (l > Q[i].l) add(A[--l]);
		while (l < Q[i].l) sub(A[l++]);
		while (r > Q[i].r) sub(A[r--]);
		while (r < Q[i].r) add(A[++r]);
		ans[Q[i].id] = sum;
	}

	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}