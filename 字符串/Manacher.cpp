#include <bits/stdc++.h>
using namespace std;

void manacher(string t);

int main()
{
	string s, m;
	cin >> s;

	m = "$#";
	for(int i = 0; i < s.size(); i++){
		m += s[i], m += "#";
	}

	manacher(m);
	return 0;
}

void manacher(string t)
{
	int mx = 0;
	vector<int> z(t.size(), 0);
	for(int i = 1, l, r = -1; i < t.size(); i++){
		if(i <= r) z[i] = min(z[l + r - i], r - i + 1);
		while(t[i - z[i]] == t[i + z[i]]) z[i]++;
		if(r < i + z[i] - 1) r = i + z[i] - 1, l = i - z[i] + 1;
		mx = max(mx, z[i] - 1);
	}
	cout << mx;
}