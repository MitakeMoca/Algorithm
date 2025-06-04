#include <bits/stdc++.h>
using namespace std;

int T[3000005][65] = {0};
int cnt[3000005] = {0};

void solve();
int tonum(char ch);

int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}

int tonum(char ch)
{
	if(ch >= '0' && ch <= '9') return ch - '0';
	if(ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 36;
}

void solve()
{
	int n, k;
	cin >> n >> k;

	string s;
	int id = 0;

	while(n--){
		cin >> s;
		int t = 0;
		for(int i = 0; i < s.size(); i++){
			if(!T[t][tonum(s[i])]) T[t][tonum(s[i])] = ++id;
			t = T[t][tonum(s[i])];
			cnt[t]++;
		}
	}

	while(k--) {
		cin >> s;
		int t = 0, f = 0;
		for(int i = 0; i < s.size(); i++){
			if(!T[t][tonum(s[i])]){
				f = 1;
				cout << 0 << endl;
				break;
			}
			t = T[t][tonum(s[i])];
		}
		if(f == 1) f = 0;
		else cout << cnt[t] << endl;
	}

	for(int i = 0; i <= id; i++){
		for(int j = 0; j < 65; j++){
			T[i][j] = 0;
		}
		cnt[i] = 0;
	}
}