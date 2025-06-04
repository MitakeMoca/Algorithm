#include <bits/stdc++.h>
using namespace std;

#define P 1000000007ll
long long A[405][805] = {0};

bool Guass(int n);
long long qpw(long long a, long long b, long long p);

int main()
{
	int n;
	cin >> n;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> A[i][j];
		}
	}

	for(int i = 1; i <= n; i++){
		A[i][i + n] = 1;
	}

	if(Guass(n)){
		for(int i = 1; i <= n; i++){
			for(int j = n + 1; j <= n * 2; j++){
				cout << A[i][j] << ' ';
			}
			puts("");
		}
	}
	else puts("No Solution");

	return 0;
}

long long qpw(long long a, long long b, long long p)
{
	long long ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ans;
}

bool Guass(int n)
{
	for(int i = 1; i <= n; i++){

		int r = i;
		for(int j = i; j <= n; j++){
			if(A[j][i] != 0){
				r = j;
				break;
			}
		}
		if(r != i) swap(A[r], A[i]);
		if(A[i][i] == 0) return false;

		long long inv = qpw(A[i][i], P - 2, P);
		for(int j = i; j <= 2 * n; j++) {
			A[i][j] = A[i][j] * inv % P;
		}
		for(int j = i + 1; j <= n; j++){
			for(int k = 2 * n; k >= i; k--){
				A[j][k] = (A[j][k] - A[j][i] * A[i][k]) % P;
				A[j][k] = (A[j][k] + P) % P;
			}
		}
	}

	for(int i = n; i >= 1; i--){
		for(int k = 2 * n; k > i; k--){
			for(int j = n; j > i; j--){
				A[i][k] = (A[i][k] - A[j][k] * A[i][j]) % P;
				A[i][k] = (A[i][k] + P) % P;
			}
		}
	}
	return true;
}