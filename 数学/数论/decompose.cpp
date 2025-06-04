#include <bits/stdc++.h>
using namespace std;

bool V[100005] = {0};
int P[100005] = {0};
int T[100005] = {0};

int cnt = 0;

void init();
void add(int t);

int main()
{
	int t;
	init();
	cin >> t;
	for(int i = 2; i <= t; i++){
		add(i);
	}

	for(int i = 0; i < cnt; i++){
		if(T[i]) cout << P[i] << ' ' << T[i] << endl;
	}
	return 0;
}

void init()
{
	for(long long i = 2; i <= 100000; i++){
		if(V[i] == 0) P[cnt++] = i;
		for(int j = 0; i * P[j] <= 100000; j++){
			int t = i * P[j];
			V[t] = 1;
			if(i % P[j] == 0) break;
		}
	}
}

void add(int t)
{
	for(int i = 0; P[i] <= t; i++){
		while(t % P[i] == 0) T[i]++, t /= P[i];
	}
}