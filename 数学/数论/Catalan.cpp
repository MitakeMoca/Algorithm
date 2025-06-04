#include <bits/stdc++.h>
using namespace std;

long long C[20] = {0};

void init();

int main()
{
	init();
	int t;
	cin >> t;
	cout << C[t];
	return 0;
}

void init()
{
	C[0] = 1;
	for(int i = 1; i <= 18; i++){
		C[i] = C[i - 1] * (4 * i - 2) / (i + 1);
	}
}