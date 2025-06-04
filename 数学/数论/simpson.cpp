#include <bits/stdc++.h>
using namespace std;

#define eps 1e-10

double a;

double f(double x);
double simpson(double l, double r);
double getAns(double l, double r, double ans);

int main()
{
	cin >> a;
	if(a < 0) puts("orz");
	else printf("%.5f", getAns(eps, 20.0, simpson(eps, 20)));
	return 0;
}

double f(double x)
{
	return pow(x, a / x - x);
}

double simpson(double l, double r)
{
	return (f(l) + f(r) + 4 * f((l + r) / 2)) * (r - l) / 6;
}

double getAns(double l, double r, double ans)
{
	double mid = (l + r) / 2;
	double m = simpson(l, mid), n = simpson(mid, r);
	if((fabs(m + n - ans)) < eps) return ans;
	return getAns(l, mid, m) + getAns(mid, r, n);
}