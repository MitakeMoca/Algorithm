#include <bits/stdc++.h>
using namespace std;

void greator_motonic_queue(vector<int> A, int n, int k);
void less_motonic_queue(vector<int> A, int n, int k);

int main()
{
	int n, k;
	cin >> n >> k;

	vector<int> num(n);
	for(int i = 0; i < n; i++){
		cin >> num[i];
	}

	less_motonic_queue(num, n, k);
	puts("");
	greator_motonic_queue(num, n, k);

	return 0;
}

void greator_motonic_queue(vector<int> A, int n, int k)
{
	vector<int> q(n);
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		while(r >= l && A[i] >= A[q[r]]) r--;
		q[++r] = i;
		if(q[r] - q[l] == k) l++;
		if(i + 1 >= k) cout << A[q[l]] << ' '; 
	}
}

void less_motonic_queue(vector<int> A, int n, int k)
{
	vector<int> q(n);
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		while(r >= l && A[i] <= A[q[r]]) r--;
		q[++r] = i;
		if(q[r] - q[l] == k) l++;
		if(i + 1 >= k) cout << A[q[l]] << ' '; 
	}
}