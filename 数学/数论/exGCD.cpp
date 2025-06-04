#include <bits/stdc++.h>
using namespace std;

int exgcd(int a, int b, int &x, int &y);

int main()
{
	int a, b, x, y;
	cin >> a >> b;

	int t = exgcd(a, b, x, y);
	cout << x << ' ' << y;
	return 0;
}

int exgcd(int a, int b, int &x, int &y)
{
	//printf("f: %d %d\n", a, b);
	if(a == 0){
		x = 0, y = 1;
		return b;
	}
	int x1, y1;
	int t = exgcd(b % a, a, x1, y1);
	x = y1 - b / a * x1;
	y = x1;
	return t;
}