#include <bits/stdc++.h>
using namespace std;

int ne[20000005];

void getNext(string sub);
void KMP(string s, string sub);
void exKMP(string s, string sub);

int main()
{
	string s, sub;
	cin >> s >> sub;

	// getNext(sub);

	// KMP(s, sub);

	// for(int i = 0; i < sub.size(); i++){
	// 	cout << ne[i] + 1 << ' ';
	// }

	exKMP(s, sub);
	return 0;
}

void getNext(string sub)
{
	ne[0] = -1;
	for(int i = 1, j = -1; i < sub.size(); i++){
		while(j != -1 && sub[i] != sub[j + 1]) j = ne[j];
		if(sub[i] == sub[j + 1]) j++;
		ne[i] = j;
	}
}

void KMP(string s, string sub)
{
	for(int i = 0, j = -1; i < s.size(); i++){
		while(j != -1 && s[i] != sub[j + 1]) j = ne[j];
		if(s[i] == sub[j + 1]) j++;
		if(j == sub.size() - 1) cout << i - sub.size() + 2 << endl;
	}
}

void exKMP(string s, string sub)
{
	vector<int> z(sub.size(), 0);
	vector<int> p(s.size(), 0);
	z[0] = sub.size();
	long long ans1 = 0, ans2 = 0;

	for(int i = 1, l, r = -1; i < sub.size(); i++){
		if(i <= r) z[i] = min(z[i - l], r - i + 1);
		while(sub[z[i]] == sub[i + z[i]]) z[i]++;
		if(r < i + z[i] - 1) l = i, r = i + z[i] - 1;
		ans1 = (ans1 ^ (1ll * (i + 1) * (z[i] + 1)));
	}

	for(int i = 0, l, r = -1; i < s.size(); i++){
		if(i <= r) p[i] = min(z[i - l], r - i + 1);
		while(p[i] < sub.size() && sub[p[i]] == s[i + p[i]]) p[i]++;
		if(r < i + p[i] - 1) l = i, r = i + p[i] - 1;
		ans2 = (ans2 ^ (1ll * (i + 1) * (p[i] + 1)));
	}

	cout << (ans1 ^ (z[0] + 1)) << endl << ans2;
}