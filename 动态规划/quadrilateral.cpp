#include <bits/stdc++.h>
using namespace std;

long long s[305] = {0};
long long dp[305][305] = {{0}};
long long p[305][305] = {{0}};

int main()
{
	int n;
	cin >> n;

	for(int i = 1; i <= n; i++){
		cin >> s[i];
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			dp[i][j] = 1e15;
		}
	}

	for(int i = 1; i <= n; i++){
		dp[i][i] = 0;
		p[i][i] = i;
		s[i] += s[i - 1];
	}

	for(int len = 2; len <= n; len++){
		for(int l = 1; l <= n - len + 1; l++){
			int r = l + len - 1;
			for(int k = p[l][r - 1]; k <= p[l + 1][r]; k++){
				if(dp[l][r] > dp[l][k] + dp[k + 1][r] + s[r] - s[l - 1]){
					dp[l][r] = dp[l][k] + dp[k + 1][r] + s[r] - s[l - 1];
					p[l][r] = k;
				}
			}
		}
	}

	cout << dp[1][n];
	return 0;
}