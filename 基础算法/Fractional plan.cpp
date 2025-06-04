#include <bits/stdc++.h>
using namespace std;

#define eps 1e-5

double dp[1005] = {0};
int w[255] = {0};
int t[255] = {0};

bool check(double x, int n, int W);

int main()
{
	int n, W;
	cin >> n >> W;

	for(int i = 0; i < n; i++){
		cin >> w[i] >> t[i];
	}

	double l = 0, r = 1000, mid;
	while(r - l > eps){
		//cout << l << ' ' << r << endl;
		mid = (l + r) / 2;
		if(check(mid, n, W)) l = mid;
		else r = mid;
	}

	printf("%d", (int)(r * 1000));
	return 0;
}

bool check(double x, int n, int W)
{
	for(int i = 1; i <= W; i++) dp[i] = -1e9;
	for(int i = 0; i < n; i++){
		for(int j = W; j >= 0; j--){
			int k = min(W, j + w[i]);
			dp[k] = max(dp[k], dp[j] + 1.0 * t[i] - x * w[i]);
		}
	}
	return dp[W] >= 0;
}