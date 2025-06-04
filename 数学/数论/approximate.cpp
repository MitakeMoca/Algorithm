#include <bits.stdc++.h>
using namespace std;

#define N 100001

bool V[N] = {0};
int P[N] = {0};
int a[N] = {0};
int d[N] = {0};
int g[N] = {0};
int f[N] = {0};
int cnt = 0;

void init();

void init()
{
	d[1] = 1;
	f[1] = 1;
	for(long long i = 2; i < N; i++){
		if(V[i] == 0){
			P[cnt++] = i, a[i] = 1, d[i] = 2;
			g[i] = f[i] = i + 1;
		}
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0){
				a[t] = a[i] + 1;
				d[t] = d[i] / a[t] * (a[t] + 1);
				g[t] = g[i] * P[j] + 1;
				f[t] = f[i] / g[i] * g[t];
				break;
			}
			else{
				a[t] = 1, d[t] = d[i] * 2;
				g[t] = P[j] + 1;
				f[t] = f[i] * g[t];
			}
		}
	}
}