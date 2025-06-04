#include <bits/stdc++.h>
using namespace std;

long long w[200005] = {0};
long long dp[200005] = {0};
long long q[200005] = {0};

int main()
{
	int n, k;
	cin >> n >> k;

	for(int i = 1; i <= n; i++){
		cin >> w[i];
	}

	int l = 0, r = 1;
	long long ans = 1e11;
	for(int i = 1; i <= n; i++){
		dp[i] = dp[q[l]] + w[i];
		while(l < r && dp[q[r - 1]] >= dp[i]) r--;
		q[r++] = i;
		if(q[r - 1] - q[l] >= k) l++;
		if(i > n - k) ans = min(ans, dp[i]);
	}
	cout << ans;
	return 0;
}