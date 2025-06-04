#include <bits/stdc++.h>
using namespace std;

long long qpw(long long a, long long b, long long p);

int main()
{
	long long a, b, p;
	cin >> a >> b >> p;

	printf("%lld^%lld mod %lld=%lld", a, b, p, qpw(a, b, p));
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