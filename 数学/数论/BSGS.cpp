#include <bits/stdc++.h>
using namespace std;

#define N 1000001

bool V[N] = {0};
int P[N] = {0};
int phi[N] = {0};
int cnt = 0;

inline long long BSGS(long long a, long long b, long long p);
inline long long qpw(long long a, long long b, long long p);
inline long long exBSGS(long long a, long long b, long long p);
inline long long gcd(long long a, long long b);
inline long long getPhi(long long t);
inline void init();

inline long long read()
{
	long long x = 0;
	char ch = getchar();

	while(!isdigit(ch)){
		ch = getchar();
	}

	while(isdigit(ch)){
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}

	return x;
}

int main()
{
	init();
	while(1){
		long long a, b, p;
		a = read();
		p = read();
		b = read();
		if(p == 0 && a == 0 && b == 0) break;

		long long ans = exBSGS(a, b, p);
		if(ans == -1) puts("No Solution");
		else cout << ans << endl;
	}
	return 0;
}

inline long long qpw(long long a, long long b, long long p)
{
	long long ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ans;
}

inline long long BSGS(long long a, long long b, long long p)
{
	a %= p, b %= p;
	if(b == 1) return 0;

	map<int, int> mp;
	long long m = ceil(sqrt(p));
	long long t = b;
	for(int i = 0; i < m; i++){
		mp[t] = i;
		t = (t * a) % p;
	}

	long long l = qpw(a, m, p); t = 1;
	for(int i = 1; i <= m; i++){
		t = (t * l) % p;
		if(mp.count(t)) return i * m - mp[t];
	}

	return -1;
}

inline long long exBSGS(long long a, long long b, long long p)
{
	a %= p, b %= p;
	if(b == 1 || p == 1) return 0;

	long long k = 0, t = 1;
	while(1){
		long long tmp = gcd(a, p);
		if(tmp == 1) break;
		if(b % tmp != 0) return -1;
		b /= tmp, p /= tmp;
		t = (a / tmp * t) % p, k++;
		if(t == b) return k;
	}
	long long inv = qpw(t, getPhi(p) - 1, p);
	b = (b * inv) % p;
	
	long long ans = BSGS(a, b, p);
	if(ans != -1) return ans + k;
	else return ans;
}

inline long long gcd(long long a, long long b)
{
	if(a == 0) return b;
	return gcd(b % a, a);
}

inline void init()
{
	phi[1] = 1;
	for(long long i = 2; i < N; i++){
		if(V[i] == 0) P[cnt++] = i, phi[i] = i - 1;
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0){
				phi[t] = phi[i] * P[j];
				break;
			}
			else phi[t] = phi[i] * (P[j] - 1);
		}
	}
}

inline long long getPhi(long long t)
{
	if(t < N) return phi[t];
	long long ans = t, f;
	for(int i = 0; 1ll * P[i] * P[i] <= t; i++){
		f = 0;
		while(t % P[i] == 0) t /= P[i], f = 1;
		if(f == 1) ans = ans / P[i] * (P[i] - 1);
	}
	if(t != 1) ans = ans / t * (t - 1);
	return ans;
}