#include <bits/stdc++.h>
using namespace std;

int get_min(vector<int> A);

int main()
{
	int n;
	cin >> n;

	vector<int> A(2 * n);
	for(int i = 0; i < n; i++){
		cin >> A[i];
		A[i + n] = A[i];
	}

	int t = get_min(A);
	for(int i = t; i < t + n; i++){
		cout << A[i] << ' ';
	}

	return 0;
}

int get_min(vector<int> A)
{
	int i = 0, j = 1, k = 0;
	int n = A.size() / 2;
	while(i < n && j < n){
		for(k = 0; k < n && A[i + k] == A[j + k]; k++);
		A[i + k] > A[j + k] ? i = i + k + 1 : j = j + k + 1;
		if(i == j) j++;
	}
	return min(i, j);
}