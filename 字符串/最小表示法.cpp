#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> A(n * 2);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		A[i + n] = A[i];
	}

	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		if (A[i + k] > A[j + k]) {
			i = i + k + 1;
			k = 0;
		}
		else if (A[i + k] < A[j + k]) {
			j = j + k + 1;
			k = 0;
		}
		else {
			k++;
		}
		if (i == j) i++;
	}

	int st = min(i, j);
	for (int i = 0; i < n; i++) {
		cout << A[st + i] << " \n"[i == n - 1];
	}
	return 0;
}