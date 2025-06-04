#include <bits/stdc++.h>
using namespace std;

void EBag(vector<int> W, vector<int> V, int weight, int n);
void WBag(vector<int> W, vector<int> V, int weight, int n);

int main()
{
	int t, n;
	cin >> t >> n;

	vector<int> W(n), T(n);
	for(int i = 0; i < n; i++){
		cin >> T[i] >> W[i];
	}
	WBag(T, W, t, n);
	return 0;
}

void EBag(vector<int> W, vector<int> V, int weight, int n)
{
	vector<int> dp(weight + 1, 0);
	for(int i = 0; i < n; i++){
		for(int t = weight; t >= W[i]; t--){
			dp[t] = max(dp[t], dp[t - W[i]] + V[i]);
		}
	}
	cout << dp[weight];
}

void WBag(vector<int> W, vector<int> V, int weight, int n)
{
	vector<int> dp(weight + 1, 0);
	for(int i = 0; i < n; i++){
		for(int t = W[i]; t <= weight; t++){
			dp[t] = max(dp[t], dp[t - W[i]] + V[i]);
		}
	}
	cout << dp[weight];
}