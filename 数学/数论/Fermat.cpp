#include <bits/stdc++.h>
using namespace std;

long long qpw(long long a, long long b, long long p);

int main()
{
	long long a, p;
	cin >> a >> p;

	printf("the inv is %lld\n", qpw(a, p - 2, p));
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