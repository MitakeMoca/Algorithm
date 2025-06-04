#include <bits/stdc++.h>
using namespace std;

int K = 0;

struct Node {
	int l, r, t, id;
	bool operator < (const Node &th) const
	{
		if (l / K != th.l / K) return l < th.l;
		if (r / K != th.r / K) return r < th.r;
		return t < th.t;
	}
}Q[200005];

struct {
	int p, x;
}M[200005];

int sum[1000005] = {0};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<int> A(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> A[i];

	char op;
	int mm = 0, mq = 0;
	for (int i = 0; i < m; i++) {
		cin >> op;
		if (op == 'Q') {
			cin >> Q[mq].l >> Q[mq].r;
			Q[mq].id = mq;
			Q[mq].t = mm;
			++mq;
		}
		if (op == 'R') {
			cin >> M[mm].p >> M[mm].x;
			++mm;
		}
	}

	K = pow(n, 2.0 / 3.0);
	sort(Q, Q + mq);

	int ans = 0;
	auto add = [&](int t) -> void {
		if (sum[t] == 0) ans++;
		sum[t]++;
	};

	auto sub = [&](int t) -> void {
		if (sum[t] == 1) ans--;
		sum[t]--;
	};

	int l = 1, r = 0, t = 0;
	vector<int> as(mq);
	for (int i = 0; i < mq; i++) {
		while (l < Q[i].l) sub(A[l++]);
		while (l > Q[i].l) add(A[--l]);
		while (r > Q[i].r) sub(A[r--]);
		while (r < Q[i].r) add(A[++r]);
		while (t < Q[i].t) {
			if (M[t].p >= l && M[t].p <= r) {
				sub(A[M[t].p]);
				add(M[t].x);
			}
			swap(M[t].x, A[M[t].p]);
			t++;
		}
		while (t > Q[i].t) {
			t--;
			if (M[t].p >= l && M[t].p <= r) {
				sub(A[M[t].p]);
				add(M[t].x);
			}
			swap(M[t].x, A[M[t].p]);
		}
		as[Q[i].id] = ans;
	}

	for (int i = 0; i < mq; i++) {
		cout << as[i] << '\n';
	}
	return 0;
}