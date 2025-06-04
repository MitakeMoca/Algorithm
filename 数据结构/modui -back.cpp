#include <bits/stdc++.h>
using namespace std;

int K = 0;
struct Node {
	int l, r, id;
}Q[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<long long> A(n + 1), B(n);
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		B[i - 1] = A[i];
	}
	sort(B.begin(), B.end());
	B.erase(unique(B.begin(), B.end()), B.end());
	
	for (int i = 1; i <= n; i++) {
		A[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
	}
	vector<long long> cnt(n, 0);

	for (int i = 0; i < m; i++) {
		cin >> Q[i].l >> Q[i].r;
		Q[i].id = i;
	}

	K = sqrt(n);
	int tot = n / K;
	vector<int> L(tot + 1), R(tot + 1);
	for (int i = 1; i <= tot; i++) {
		L[i] = (i - 1) * K + 1;
		R[i] = i * K;
	}
	if (R[tot] < n) {
		tot++;
		L.push_back(R.back() + 1);
		R.push_back(n);
	}
	vector<int> pos(n + 1);
	for (int i = 1; i <= tot; i++) {
		for (int j = L[i]; j <= R[i]; j++) {
			pos[j] = i;
		}
	}
	sort(Q, Q + m, [&](Node a, Node b) {
		if (pos[a.l] != pos[b.l]) return a.l < b.l;
		return a.r < b.r;
	});

	int l = 1, r = 0, last = 0;
	long long sum = 0, tmp = 0;
	vector<long long> ans(m);

	auto add = [&](int t) -> void {
		++cnt[t];
		sum = max(sum, cnt[t] * B[t]);
	};

	auto sub = [&](int t) -> void {
		--cnt[t];
	};

	vector<int> _cnt(n + 1);
	for (int i = 0; i < m; i++) {

		if (pos[Q[i].l] == pos[Q[i].r]) {
			long long now = 0;
			for (int j = Q[i].l; j <= Q[i].r; j++) now = max(now, B[A[j]] * ++_cnt[A[j]]);
			for (int j = Q[i].l; j <= Q[i].r; j++) --_cnt[A[j]];
			ans[Q[i].id] = now;
			continue;
		}

		if (pos[Q[i].l] != last) {
			while (r > R[pos[Q[i].l]]) sub(A[r--]);
			while (l < R[pos[Q[i].l]] + 1) sub(A[l++]);
			sum = 0;
			last = pos[Q[i].l];
		}

		while (r < Q[i].r) add(A[++r]);
		tmp = sum;

		while (l > Q[i].l) add(A[--l]);
		ans[Q[i].id] = sum;

		while (l < R[pos[Q[i].l]] + 1) sub(A[l++]);
		sum = tmp;
	}

	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}