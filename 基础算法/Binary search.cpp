#include <bits/stdc++.h>
using namespace std;

int A[1000005] = {0};

int find(int k, int n);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m;

	for(int i = 0; i < n; i++){
		cin >> A[i];
	}

	for(int i = 0; i < m; i++){
		cin >> k;
		cout << find(k, n) << ' ';
	}
	return 0;
}

int find(int k, int n)
{
	int l = 0, r = n - 1, mid;
	while(l <= r){
		mid = (l + r) / 2;
		if(A[mid] > k) r = mid - 1;
		else if(A[mid] < k) l = mid + 1;
		else if((mid == 0 && A[mid] == k) || (mid > 0 && A[mid - 1] < k)) return mid + 1;
		else r = mid - 1;
	}
	return -1;
	
}