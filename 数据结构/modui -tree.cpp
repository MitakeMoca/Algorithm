#include <bits/stdc++.h>
using namespace std;

long long V[1000005] = {0};
long long W[1000005] = {0};
int C[100005] = {0};
vector<int> p[100005];
int in[100005] = {0};
int out[100005] = {0};
int A[200005] = {0};
int dep[100005] = {0};
int st[100005][20] = {{0}};
int id = 0, K = 0;

struct Node {
	int l, r, t, id, lca;
	bool operator < (const Node &th) const
	{
		if (l / K != th.l / K) return l < th.l;
		if (r / K != th.r / K) return r < th.r;
		return t < th.t;
	}
}Q[100005];

struct {
	int p, x;
}M[100005];

void dfs(int t, int fa)
{
	dep[t] = dep[fa] + 1;
	st[t][0] = fa;
	A[++id] = t;
	in[t] = id;

	for (int i = 1; i < 20; i++) {
		st[t][i] = st[st[t][i - 1]][i - 1];
	}

	for (auto i: p[t]) {
		if (i == fa) continue;
		dfs(i, t);
	}

	A[++id] = t;
	out[t] = id;
}

int getLCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = 19; i >= 0; i--) {
		if (dep[st[a][i]] >= dep[b]) {
			a = st[a][i];
		}
	}

	if (a == b) return a;

	for (int i = 19; i >= 0; i--) {
		if (st[a][i] != st[b][i]) {
			a = st[a][i];
			b = st[b][i];
		}
	}

	return st[a][0];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, q;
	cin >> n >> m >> q;

	for (int i = 1; i <= m; i++) {
		cin >> V[i];
	}

	for (int i = 1; i <= n; i++) {
		cin >> W[i];
	}

	int u, v;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}
	dfs(1, 1);

	for (int i = 1; i <= n; i++)
		cin >> C[i];

	int op, x, y;
	int mq = 0, mm = 0;
	while (q--) {
		cin >> op >> x >> y;
		if (op == 1) {
			Q[mq].id = mq;
			Q[mq].t = mm;
			if (in[x] > in[y]) swap(x, y);
			int lca = getLCA(x, y);
			if (x == lca) {
				Q[mq].l = in[x];
				Q[mq].r = in[y];
				Q[mq].lca = 0;
			}
			else {
				Q[mq].l = out[x];
				Q[mq].r = in[y];
				Q[mq].lca = lca;
			}
			++mq;
		}
		else {
			M[mm].p = x, M[mm].x = y;
			++mm;
		}
	}

	K = pow(n, 2.0 / 3.0);
	sort(Q, Q + mq);
	vector<long long> ans(mq);
	vector<int> cnt(m + 1);
	vector<int> vis(n + 1);
	long long sum = 0;

	auto add = [&](int t) -> void {
		vis[t] ^= 1;
		if (vis[t] == 1) sum += V[C[t]] * W[++cnt[C[t]]];
		else sum -= W[cnt[C[t]]--] * V[C[t]];
	};

	int l = 1, r = 0, t = 0;
	for (int i = 0; i < mq; i++) {
		while (l < Q[i].l) add(A[l++]);
		while (l > Q[i].l) add(A[--l]);
		while (r > Q[i].r) add(A[r--]);
		while (r < Q[i].r) add(A[++r]);
		while (t < Q[i].t) {
			if (vis[M[t].p] == 1) {
				add(M[t].p);
				swap(C[M[t].p], M[t].x);
				add(M[t].p);
			}
			else swap(C[M[t].p], M[t].x);
			t++;
		}
		while (t > Q[i].t) {
			t--;
			if (vis[M[t].p] == 1) {
				add(M[t].p);
				swap(C[M[t].p], M[t].x);
				add(M[t].p);
			}
			else swap(C[M[t].p], M[t].x);
		}
		ans[Q[i].id] = sum;
		if (Q[i].lca != 0) {
			ans[Q[i].id] += W[cnt[C[Q[i].lca]] + 1] * V[C[Q[i].lca]];
		}
	}

	for (int i = 0; i < mq; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}