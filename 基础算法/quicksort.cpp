#include <bits/stdc++.h>
using namespace std;

int A[100005] = {0};

void quicksort(int l, int r)
{
	if(l == r) return;

	int i = l - 1, j = r + 1;
	int x = A[(i + j) / 2];

	while(i < j){
		do i++; while(A[i] < x);
		do j--; while(A[j] > x);
		if(i < j) swap(A[i], A[j]);
	}

	quicksort(l, j);
	quicksort(j + 1, r);
}

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> A[i];
	quicksort(1, n);
	for(int i = 1; i <= n; i++) cout << A[i] << ' ';
	return 0;
}