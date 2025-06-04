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

	stack<int> s;
	vector<int> ans(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		while (!s.empty() && A[s.top()] < A[i]) {
			ans[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}

	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];
	return 0;
}