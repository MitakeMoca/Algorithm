#include <bits/stdc++.h>
using namespace std;

int ne[2000005] = {0};
int z[40000007] = {0};

void get_prefunction(string s)
{
	int n = s.size();

	ne[0] = -1;
	for (int i = 1, j = -1; i < n; i++) {
		while (j != -1 && s[i] != s[j + 1]) j = ne[j];
		if (s[i] == s[j + 1]) j++;
		ne[i] = j;
	}
}

void get_zfunction(string s)
{
	int n = s.size();

	for (int i = 1, r = 0, l = 0; i < n; i++) {
		if (i <= r) z[i] = min(z[i - l], r - i + 1);
		while (s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s, t;
	cin >> s >> t;

	string tmp = t + "#" + s;

	get_zfunction(tmp);

	int n = tmp.size();
	int len1 = t.size(), len2 = s.size();
	z[0] = len1;

	long long ans1 = 0;
	for (int i = 0; i < len1; i++) {
		ans1 ^= 1ll * (i + 1) * (z[i] + 1);
	}
	cout << ans1 << '\n';

	long long ans2 = 0;
	for (int i = 0; i < len2; i++) {
		ans2 ^= 1ll * (i + 1) * (z[len1 + 1 + i] + 1);
	}
	cout << ans2 << '\n';
	
	return 0;
}