#include <bits/stdc++.h>
using namespace std;

int T[1000005][26] = {0};
int cnt[1000005] = {0};
int ne[1000005] = {0};
int id = 0;

void insert(string s);
int quiey(string s);
void build();

int main()
{
	int n;
	cin >> n;

	string s;
	for(int i = 0; i < n; i++){
		cin >> s;
		insert(s);
	}

	build();

	cin >> s;
	cout << quiey(s);
	return 0;
}

void insert(string s)
{
	int t = 0;
	for(int i = 0; i < s.size(); i++){
		if(!T[t][s[i] - 'a']) T[t][s[i] - 'a'] = ++id;
		t = T[t][s[i] - 'a'];
	}
	cnt[t]++;
}

void build()
{
	queue<int> q;
	for(int i = 0; i < 26; i++){
		if(T[0][i]) q.push(T[0][i]);
	}

	while(!q.empty()){
		int t = q.front();
		q.pop();

		for(int i = 0; i < 26; i++){
			int v = T[t][i];
			if(v) ne[v] = T[ne[t]][i], q.push(v);
			else T[t][i] = T[ne[t]][i];
		}
	}
}

int quiey(string s)
{
	int ans = 0;
	for(int i = 0, t = 0; i < s.size(); i++){
		t = T[t][s[i] - 'a'];
		for(int j = t; j && ~cnt[j]; j = ne[j]){
			ans += cnt[j], cnt[j] = -1;
		}
	}
	return ans;
}