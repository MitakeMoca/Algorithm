#include <bits/stdc++.h>
using namespace std;

#define P 1000000007

long long S[50005][250] = {{0}};
long long C[250][250] = {{0}};

void init();

int main()
{
	init();
	int n, a, b, t;
	cin >> t;
	while(t--){
		cin >> n >> a >> b;
		cout << S[n - 1][a + b - 2] * C[a + b - 2][a - 1] % P << endl;
	}
	return 0;
}

void init()
{
	S[0][0] = 1;
	for(int i = 1; i <= 50000; i++){
		for(int j = 1; j <= 200; j++){
			S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j]) % P;
		}
	}

	for(int i = 0; i <= 200; i++) C[i][0] = 1;
	for(int i = 1; i <= 200; i++){
		for(int j = 1; j <= 200; j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
		}
	}
}