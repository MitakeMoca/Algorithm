#include <bits/stdc++.h>
using namespace std;

bool V[1000000005] = {0};
int P[100005] = {0};
int cnt = 0;

bool isprim(int t);
void init();

int main()
{
	int n, a;
	init();
	V[1] = 1;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a;
		if(V[a] == 0) cout << a << ' ';
	}
	return 0;
}

bool isprim(int t)
{
	if(t == 2) return true;
	if(t == 1) return false;
	for(int i = 2; i * i <= t; i++){
		if(t % i == 0) return false;
	}
	return true;
}

void init() // 最小质数 * 最大因数保证唯一性
{
	for(long long i = 2; i <= 100000; i++){
		if(V[i] == 0) P[cnt++] = i;
		for(long long j = 0; i * P[j] <= 100000; j++){
			long long t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0) break;
		}
	}
}