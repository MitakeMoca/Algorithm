#include <bits/stdc++.h>
using namespace std;

int A[500005], B[500005];

long long ans = 0;

void merge(int l, int r)
{
	if(l == r) return;
	int mid = l + r >> 1;

	merge(l, mid);
	merge(mid + 1, r);

	int i = l, j = mid + 1, k = l;
	while(i <= mid && j <= r){
		if(A[i] <= A[j]) B[k++] = A[i++];
		else B[k++] = A[j++], ans += mid - i + 1;
	}
	while(i <= mid) B[k++] = A[i++];
	while(j <= r) B[k++] = A[j++];
	for(int i = l; i <= r; i++) A[i] = B[i];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> A[i];
	merge(1, n);
	cout << ans;
	return 0;
}