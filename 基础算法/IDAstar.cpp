#include <bits/stdc++.h>
using namespace std;

int A[20];
int n;

int f();
bool check();
int dfs(int t);

int main()
{
	int m;
	cin >> m;
	while(m--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> A[i];
		}
		int t = dfs(0);
		if(t == 5) puts("5 or more");
		else cout << t << '\n';
	}
	return 0;
}

int dfs(int t)
{
	if(t + f() >= 5) return 5;
	if(check()) return t;

	int ans = 5;
	int B[20];
	for(int i = 1; i <= n; i++){
		for(int l = i + 1; l <= n; l++){
			memcpy(B, A, sizeof(A));
			for(int r = l; r <= n; r++){
				for(int m = i, n = l; n <= r; m++, n++) A[m] = B[n];
				for(int m = i + r - l + 1, n = i; n < l; m++, n++) A[m] = B[n];
				ans = min(ans, dfs(t + 1));
			}
			memcpy(A, B, sizeof(B));
		}
	}
	return ans;
}

bool check()
{
	for(int i = 1; i < n; i++){
		if(A[i] != i) return false;
	}
	return true;
}

int f()
{
	int ans = 0;
	for(int i = 2; i <= n; i++){
		ans += (A[i] != A[i - 1] + 1);
	}
	return (ans + 2) / 3;
}