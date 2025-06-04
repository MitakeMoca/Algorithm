#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long n, k;
	cin >> n >> k;

	long long ans = n * k;
	long long t = min(n, k);
	for(long long l = 1, r; l <= t; l = r + 1){
		r = k / (k / l);
		r = min(r, t);
		ans -= (k / l) * (r - l + 1) * (r + l) / 2;
	}

	cout << ans;
	return 0;
}