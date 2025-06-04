#include <bits/stdc++.h>
using namespace std;

#define N 20000001

bool V[N] = {0};
int P[N] = {0};
long long mu[N] = {0};
long long phi[N] = {0};
int cnt = 0;

map<int, long long> mp_phi;
map<int, long long> mp_mu;

void init();
void solve();
long long getSumMu(long long n);
long long getSumPhi(long long n);

int main()
{
	init();
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}

void init()
{
	mu[1] = phi[1] = 1;
	for(long long i = 2; i < N; i++){
		if(V[i] == 0){
			P[cnt++] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0){
				mu[t] = 0;
				phi[t] = phi[i] * P[j];
				break;
			}
			else{
				mu[t] = -mu[i];
				phi[t] = phi[i] * (P[j] - 1);
			}
		}
	}
	for(int i = 1; i < N; i++){
		phi[i] += phi[i - 1], mu[i] += mu[i - 1];
	}
}

void solve()
{
	long long n;
	cin >> n;

	long long ans1 = getSumPhi(n);
	long long ans2 = getSumMu(n);

	cout << ans1 << ' ' << ans2 << endl;
}

long long getSumPhi(long long n)
{
	if(n < N) return phi[n];
	if(mp_phi.count(n)) return mp_phi[n];

	long long ans = (n + 1) * n / 2;
	for(long long l = 2, r; l <= n; l = r + 1){
		r =  n / (n / l);
		ans -= (r - l + 1) * getSumPhi(n / l);
	}

	return mp_phi[n] = ans;
}

long long getSumMu(long long n)
{
	if(n < N) return mu[n];
	if(mp_mu.count(n)) return mp_mu[n];

	long long ans = 1;
	for(long long l = 2, r; l <= n; l = r + 1){
		r = n / (n / l);
		ans -= (r - l + 1) * getSumMu(n / l);
	}

	return mp_mu[n] = ans;
}