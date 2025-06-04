#include <bits/stdc++.h>
using namespace std;

#define N 4000005

void change(int n);
void NTT(long long *A, int n, int op);
long long qpw(long long a, long long b, long long p);

long long A[N] = {0}, B[N] = {0}, C[N] = {0};
const long long P = 998244353ll;
int R[N] = {0};

int main()
{
	int n, m;
	cin >> n >> m;

	for(int i = 0; i <= n; i++) cin >> A[i];
	for(int i = 0; i <= m; i++) cin >> B[i];
	for(m = n + m, n = 1; n <= m; n <<= 1);

	change(n);
	NTT(A, n, 1);
	NTT(B, n, 1);
	for(int i = 0; i < n; i++) C[i] = A[i] * B[i] % P;
	NTT(C, n, -1);
	long long inv = qpw(n, P - 2, P);
	for(int i = 0; i <= m; i++) cout << C[i] * inv % P << ' ';
	return 0; 
}

void change(int n)
{
	for(int i = 1; i < n; i++){
		R[i] = ((R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0));
	}
}

void NTT(long long *A, int n, int op)
{
	for(int i = 0; i < n; i++){
		if(i < R[i]) swap(A[i], A[R[i]]);
	}

	long long inv = qpw(3, P - 2, P);
	for(int k = 2; k <= n; k <<= 1){
		long long g1 = qpw(op == 1 ? 3 : inv, (P - 1) / k, P);
		for(int i = 0; i < n; i += k){
			long long gk = 1;
			for(int j = 0; j < k / 2; j++){
				long long x = A[i + j], y = A[i + j + k / 2] * gk % P;
				A[i + j] = (x + y) % P;
				A[i + j + k / 2] = (x - y + P) % P;
				gk = (gk * g1) % P;
			}
		}
	}
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