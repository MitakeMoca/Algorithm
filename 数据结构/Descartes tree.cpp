#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> A(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> A[i];

	vector<int> l(n + 1, 0), r(n + 1, 0);
	vector<int> stk(n + 1);
	int top = 0;

	for (int i = 1; i <= n; i++) {
		int k = top;
		while (k > 0 && A[stk[k]] > A[i]) k--;
		if (k) r[stk[k]] = i;
		if (k < top) l[i] = stk[k + 1];
		stk[++k] = i;
		top = k;
	}

	long long ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i++) {
		ans1 ^= 1ll * i * (l[i] + 1);
		ans2 ^= 1ll * i * (r[i] + 1);
	}
	cout << ans1 << ' ' << ans2 << '\n';

	return 0;
}