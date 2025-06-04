#include <bits/stdc++.h>
using namespace std;

int A[100005] = {0};
int n, d = 1;

bool dfs(int t);

int main()
{
	A[0] = 1;
	while(1){
		cin >> n;
		if(n == 0) break;
		
		d = 1;
		while(!dfs(1)) d++;
		for(int i = 0; i < d; i++) {
			cout << A[i];
			i == d - 1 ? puts("") : putchar(' ');
		}
	}
	return 0;
}

bool dfs(int t)
{
	if(t == d) return A[t - 1] == n;
	for(int i = t - 1; i >= 0; i--){
		int m = A[t - 1] + A[i];
		if(m > n) continue;
		A[t] = m;
		for(int j = i + 1; j <= d; j++) m *= 2;
		if(m < n) return false;
		if(dfs(t + 1)) return true;
	}
	return false;
}