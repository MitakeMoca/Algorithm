#include <bits/stdc++.h>
using namespace std;

#define N 100001
#define VLL vector<long long>

bool V[N] = {0};
int P[N] = {0};
int phi[N] = {0};
int cnt = 0;

void init();
long long qpw(long long a, long long b, long long p);
long long CRT(VLL b, VLL m, int n);
long long mul(long long a, long long b, long long p);
long long exCRT(VLL r, VLL m, int n);
long long exgcd(long long a, long long b, long long &x, long long &y);

int main()
{
	init();
	int n;
	cin >> n;
	VLL b(n), m(n);
	for(int i = 0; i < n; i++){
		cin >> m[i] >> b[i];
	}
	cout << exCRT(b, m, n);
	return 0;
}

void init()
{
	phi[1] = 1;
	for(long long i = 2; i < N; i++){
		if(V[i] == 0) P[cnt++] = i, phi[i] = i - 1;
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0){
				phi[t] = P[j] * phi[i];
				break;
			}
			else phi[t] = phi[i] * (P[j] - 1);
		}
	}
}

long long CRT(VLL b, VLL m, int n)
{
	long long M = 1;
	for(int i = 0; i < n; i++){
		M *= m[i];
	}
	long long ans = 0;
	for(int i = 0; i < n; i++){
		long long c = M / m[i];
		ans = (ans + mul(mul(b[i], c, M), qpw(c, phi[m[i]] - 1, m[i]), M)) % M;
	}
	return ans;
}

long long qpw(long long a, long long b, long long p)
{
	long long ans = 1;
	while(b){
		if(b & 1) ans = mul(ans, a, p);
		a = mul(a, a, p);
		b >>= 1;
	}
	return ans;
}

long long mul(long long a, long long b, long long p)
{
	long long ans = 0;
	while(b){
		if(b & 1) ans = (ans + a) % p;
		a = (a + a) % p;
		b >>= 1;
	}
	return ans;
}

long long exCRT(VLL r, VLL m, int n)
{
	long long R = r[0], M = m[0], p, q;
	for(int i = 1; i < n; i++){
		long long d = exgcd(M, m[i], p, q);
		long long mod =  M / d * m[i];
		p = ((p % mod) + mod) % mod;
		p = mul((R - r[i]) / d, p, mod);
		R = R - mul(p, M, mod);
		M = mod;
		R = (R % M + M) % M;
	}
	return R;
}

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if(a == 0){
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	long long t = exgcd(b % a, a, x1, y1);
	y = x1, x = y1 - b / a * x1;
	return t;
}