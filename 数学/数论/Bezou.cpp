#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b);

int main()
{
	int n, a = 0, b;
	cin >> n;
	while(n--){
		cin >> b;
		a = gcd(a, abs(b));
	}
	cout << a;
	return 0;
}

int gcd(int a, int b)
{
	if(a == 0) return b;
	return gcd(b % a, a);
}