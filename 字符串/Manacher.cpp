#include <bits/stdc++.h>
using namespace std;

int d[40000005] = {0};

void manacher(string &s)
{
	int n = s.size();
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) d[i] = min(d[l + r - i], r - i + 1);
		while (s[i - d[i]] == s[i + d[i]]) d[i]++;
		if (i + d[i] - 1 > r) r = i + d[i] - 1, l = i - d[i] + 1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;

	string t = "$#";
	for (int i = 0; i < s.size(); i++) {
		t += s[i];
		t += "#";
	}

	manacher(t);

	int mx = 0;
	for (int i = 1; i < t.size(); i++) {
		mx = max(mx, d[i] - 1);
	}
	cout << mx << '\n';

	return 0;
}