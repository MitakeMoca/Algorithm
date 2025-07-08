#include <bits/stdc++.h>
using namespace std;

struct SA {

	vector<int> rk, y, c, sa;
	vector<int> height;

	SA(string s)
	{
		int n = s.size(), m = 128;
		const int N = max(2 * n + 1, m);
		rk.resize(N, 0);
		y.resize(N, 0);
		c.resize(N, 0);
		sa.resize(N, 0);

		for (int i = 0; i < n; i++) rk[i + 1] = s[i];
		for (int i = 1; i <= n; i++) c[rk[i]]++;
		for (int i = 1; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i > 0; i--) sa[c[rk[i]]--] = i;

		for (int k = 1; k < n; k <<= 1) {

			for (int i = 1; i <= m; i++) c[i] = 0;
			for (int i = 1; i <= n; i++) y[i] = sa[i];
			for (int i = 1; i <= n; i++) c[rk[y[i] + k]]++;
			for (int i = 1; i <= m; i++) c[i] += c[i - 1];
			for (int i = n; i > 0; i--) sa[c[rk[y[i] + k]]--] = y[i];

			for (int i = 1; i <= m; i++) c[i] = 0;
			for (int i = 1; i <= n; i++) y[i] = sa[i];
			for (int i = 1; i <= n; i++) c[rk[y[i]]]++;
			for (int i = 1; i <= m; i++) c[i] += c[i - 1];
			for (int i = n; i > 0; i--) sa[c[rk[y[i]]]--] = y[i];

			for (int i = 1; i <= n; i++) y[i] = rk[i];
			m = 0;
			for (int i = 1; i <= n; i++) {
				if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
					rk[sa[i]] = m;
				else 
					rk[sa[i]] = ++m;
			}

			if (n == m) break;
		}

		height.resize(n + 1, 0);
		for (int i = 1, k = 0; i <= n; i++) {
			if (rk[i] == 0) continue;
			if (k != 0) k--;
			while (s[i + k - 1] == s[sa[rk[i] - 1] + k - 1]) k++;
			height[rk[i]] = k;
		}
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;

	int n = s.size();
	SA sa(s);
	for (int i = 1; i <= n; i++) {
		cout << sa.sa[i] << " \n"[i == n];
	}
	return 0;
}