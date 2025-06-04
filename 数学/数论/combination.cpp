#include <bits/stdc++.h>
using namespace std;

#define P 1000000007

long long C[2005][2005] = {0};
long long f[1000005], g[1000005];

void direct(int n);
void init(int n, long long p);
long long qpw(long long a, long long b, long long p);
long long getC(long long m, long long n, long long p);
long long Lucas(long long m, long long n, long long p);

int main()
{
	long long n, m, p, t;
	cin >> t;
	while(t--){
		cin >> n >> m >> p;
		init(p, p);
		cout << Lucas(n + m, n, p) << endl;
	}
	return 0;
}

void direct(int n)
{
	for(int i = 1; i <= n; i++){
		for(int j = 0;  j <= i; j++){
			if(j == 0) C[i][j] = 1;
			else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
		}
	}
}

void init(int n, long long p)
{
	f[0] = g[0] = 1;
	for(int i = 1; i < n; i++){
		f[i] = f[i - 1] * i % p;
		g[i] = g[i - 1] * qpw(i, p - 2, p) % p;
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

long long getC(long long m, long long n, long long p)
{
	//printf("%lld %lld %lld\n", m, n, p);
	if(m < n) return 0;
	return f[m] * g[n] % p * g[m - n] % p;
}

long long Lucas(long long m, long long n, long long p)
{
	if(n == 0) return 1;
	return Lucas(m / p, n / p, p) * getC(m % p, n % p, p) % p;
}