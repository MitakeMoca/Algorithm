#include <bits/stdc++.h>
using namespace std;

void LCS(string A, string B);

int main()
{
	string A, B;
	cin >> A >> B;

	LCS(A, B);

	return 0;
}

void LCS(string A, string B)
{
	int len1 = A.size() - 1;
	int len2 = B.size() - 1;

	vector<vector<int>> dp(2, vector<int>(len2 + 1, 0));
	vector<vector<int>> sum(2, vector<int>(len2 + 1, 0));

	for(int i = 0; i <= len2; i++){
		sum[0][i] = 1;
	}
	sum[1][0] = 1;

	for(int i = 1; i <= len1; i++){
		for(int j = 1; j <= len2; j++){
			sum[i & 1][j] = 0;
			dp[i & 1][j] = max(max(dp[(i - 1) & 1][j], dp[i & 1][j - 1]), dp[(i - 1) & 1][j - 1] + (A[i - 1] == B[j - 1]));

			if(A[i - 1] == B[j - 1]){
				sum[i & 1][j] += sum[(i - 1) & 1][j - 1];
			}

			if(dp[i & 1][j] == dp[(i - 1) & 1][j]){
				sum[i & 1][j] += sum[(i - 1) & 1][j];
			}

			if(dp[i & 1][j] == dp[i & 1][j - 1]){
				sum[i & 1][j] += sum[i & 1][j - 1];
			}

			if(dp[i & 1][j] == dp[(i - 1) & 1][j - 1]){
				sum[i & 1][j] -= sum[(i - 1) & 1][j - 1];
			}

			sum[i & 1][j] %= 100000000;
		}
	}

	cout << dp[len1 & 1][len2] << endl << sum[len1 & 1][len2];
}