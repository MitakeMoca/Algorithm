#include <bits/stdc++.h>
using namespace std;

int A[100005];

long long check(int t, int n);

int main()
{
	int n, k;
	cin >> n >> k;

	for(int i = 0; i < n; i++){
		cin >> A[i];
	}

	int l = 1, r = 100000000, mid;
	while(l <= r){
		mid = (l + r >> 1);
		if(check(mid, n) < k) r = mid - 1;
		else if((mid < 100000000 && check(mid + 1, n) < k || mid == 100000000)){
			cout << mid;
			return 0;
		}
		else l = mid + 1;
	}
	cout << 0;
	return 0;
}

long long check(int t, int n)
{
	long long ans = 0;
	for(int i = 0; i < n; i++){
		ans = ans + A[i] / t;
	}
	//printf("ans: %d -> %lld\n", t, ans);
	return ans;
}