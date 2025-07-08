#include <bits/stdc++.h>
using namespace std;

int tr[2000005][26] = {0};
int ne[2000005] = {0};
long long cnt[2000005] = {0};
vector<int> inv[2000005];
int din[2000005] = {0};
int id = 0;

void insert(string s, int p)
{
	int n = s.size();
	int now = 0;

	for (int i = 0; i < n; i++) {
		int t = s[i] - 'a';
		if (tr[now][t] == 0) tr[now][t] = ++id;
		now = tr[now][t];
	}

	inv[now].push_back(p);
}

void build()
{
	queue<int> q;
	for (int i = 0; i < 26; i++) {
		if (tr[0][i] != 0) q.push(tr[0][i]);
	}

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		for (int i = 0; i < 26; i++) {
			int node = tr[a][i];
			if (node != 0) {
				ne[node] = tr[ne[a]][i];
				din[tr[ne[a]][i]]++;
				q.push(node);
			}
			else tr[a][i] = tr[ne[a]][i];
		}
	}
}

void query(string s)
{
	int n = s.size();

	int now = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		int t = s[i] - 'a';
		now = tr[now][t];
		cnt[now]++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	string s;
	vector<long long> A(n);
	for(int i = 0; i < n; i++){
		cin >> s;
		insert(s, i);
	}

	build();

	string t;
	cin >> t;
	query(t);

	queue<int> q;
	for (int i = 1; i <= id; i++) {
		if (din[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		for (auto node: inv[a]) {
			A[node] = cnt[a];
		}
		if (ne[a] == 0) continue;
		cnt[ne[a]] += cnt[a];
		din[ne[a]]--;

		if (din[ne[a]] == 0) q.push(ne[a]);
	}

	for (int i = 0; i < n; i++) {
		cout << A[i] << '\n';
	}

	return 0;
}