#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

struct Node {
	int l, r, id;
	long long res;
}Q[100005];

struct Need {
	int l, r, id, x, y;
};

vector<Need> need[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<int> A(n + 1), B(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		B[i] = A[i];
	}

	sort(B.begin() + 1, B.end());
	B.erase(unique(B.begin() + 1, B.end()), B.end());

	for (int i = 1; i <= n; i++) {
		A[i] = lower_bound(B.begin() + 1, B.end(), A[i]) - B.begin();
	}

	vector<int> tree(n + 1, 0);
	vector<long long> pre0(n + 1, 0), pre1(n + 1, 0);

	auto add = [&](int x, int k) -> void {
		while (x <= n) tree[x] += k, x += lowbit(x);
	};

	auto query = [&](int x) -> int {
		int ans = 0;
		while (x) ans += tree[x], x -= lowbit(x);
		return ans;
	};

	for (int i = 1; i <= n; i++) {
		add(A[i], 1);
		pre0[i] = i - query(A[i]) + pre0[i - 1];
		pre1[i] = query(A[i] - 1) + pre1[i - 1];
	}

	for (int i = 0; i < m; i++) {
		cin >> Q[i].l >> Q[i].r;
		Q[i].id = i;
	}

	int K = sqrt(n);
	sort(Q, Q + m, [&](Node a, Node b) {
		if (a.l / K != b.l / K) return a.l < b.l;
		return a.l / K & 1 ? a.r > b.r : a.r < b.r; 
	});

	int l = 1, r = 0;
	for (int i = 0; i < m; i++) {
		if (l > Q[i].l) {
			need[r].push_back((Need){Q[i].l, l - 1, i, 1, 0}); 
			Q[i].res -= pre1[l - 1] - pre1[Q[i].l - 1]; // l -> Q[i].l, ans += g(A[l], r)(tag) - g(A[l], l - 1);
			l = Q[i].l;
		}
		if (r < Q[i].r) {
			need[l - 1].push_back((Need){r + 1, Q[i].r, i, -1, 1});
			Q[i].res += pre0[Q[i].r] - pre0[r]; // r -> Q[i].r, ans += f(A[r], r - 1) - f(A[r], l - 1)(tag);
			r = Q[i].r;
		}
		if (l < Q[i].l) {
			need[r].push_back((Need){l, Q[i].l - 1, i, -1, 0});
			Q[i].res += pre1[Q[i].l - 1] - pre1[l - 1]; // l -> Q[i].l, ans -= g(A[l], r)(tag) - g(A[l], l - 1);
			l = Q[i].l;
		}
		if (r > Q[i].r) {
			need[l - 1].push_back((Need){Q[i].r + 1, r, i, 1, 1});
			Q[i].res -= pre0[r] - pre0[Q[i].r]; // r -> Q[i].r, ans -= f(A[r], r - 1) - f(A[r], l - 1)(tag);
			r = Q[i].r;
		}
	}

	fill(tree.begin(), tree.end(), 0);
	for (int i = 1; i <= n; i++) {
		add(A[i], 1);
		for (Need t: need[i]) {
			for (int j = t.l; j <= t.r; j++) {
				if (t.y == 0) {
					Q[t.id].res += t.x * (query(A[j] - 1));
				}
				else {
					Q[t.id].res += t.x * (i - query(A[j]));
				}
			}
		}
	}

	for (int i = 1; i < m; i++) {
		Q[i].res += Q[i - 1].res;
	}

	vector<long long> ans(m);
	for (int i = 0; i < m; i++) {
		ans[Q[i].id] = Q[i].res;
	}
	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}