#include <bits/stdc++.h>
using namespace std;

#define N 100005

int phi[N] ={0};
bool V[N] = {0};
int P[N] = {0};
int mu[N] = {0};

int cnt = 0;

void init();

void init()
{
	phi[1] = 1;
	mu[1] = 1;
	for(long long i = 2; i < N; i++){
		if(V[i] == 1) P[cnt++] = i, phi[i] = i - 1, mu[i] = -1;
		for(int j = 0; i * P[j] < N; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0){
				mu[t] = 0;
				phi[t] = phi[i] * P[j];
				break;
			}
			else phi[t] = phi[i] * (P[j] - 1), mu[t] = -mu[i];
		}
	}
}