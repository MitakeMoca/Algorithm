#include <bits/stdc++.h>
using namespace std;

#define N 100001

int P[N] = {0};
bool V[N] = {0};
int cnt = 0;

void init();
long long tran(string s, long long p);
long long qpw(long long a, long long b, long long p);
long long getPhi(long long t);

int main()
{
	init();
	long long a, p;
	string s;
	cin >> a >> p >> s;

	long long phi = getPhi(p);
	long long b = tran(s, phi);

	cout << qpw(a, b, p);
	return 0;
}

void init()
{
	for(long long i = 2; i < N; i++){
		if(V[i] == 0) P[cnt++] = i;
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0) break;
		}
	}
}

long long getPhi(long long t)
{
	long long ans = t;
	for(int i = 0; P[i] * P[i] <= t; i++){
		int f = 0;
		while(t % P[i] == 0) t /= P[i], f = 1;
		if(f == 1) ans = ans / P[i] * (P[i] - 1);
	}
	if(t != 1) ans = ans / t * (t - 1);
	return ans;
}

long long tran(string s, long long p)
{
	long long ans = 0;
	for(int i = 0; i < s.size(); i++){
		ans = (ans << 3) + (ans << 1) + (s[i] ^ 48);
		if(ans > p) ans = ans % p + p;
	}
	return ans;
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