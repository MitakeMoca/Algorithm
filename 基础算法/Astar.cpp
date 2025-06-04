#include <bits/stdc++.h>
using namespace std;

int gx[10] = {-1, 0, 0, 0, 1, 2, 2, 2, 1};
int gy[10] = {-1, 0, 1, 2, 2, 2, 1, 0, 0};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int f(string s);

int main()
{
	string s;
	string ed = "123804765";
	cin >> s;

	priority_queue<pair<int, string> > q;
	q.push({-f(s), s});
	unordered_map<string, int> mp;
	mp[s] = 0;

	while(!q.empty()){
		string t = q.top().second;
		q.pop();
		string tmp = t;

		if(t == ed) break;
		int pos = t.find('0');
		int x = pos / 3, y = pos % 3;
		for(int i = 0; i < 4; i++){
			int tx = x + dx[i], ty = y + dy[i];
			if(tx < 0 || tx >= 3 || ty < 0 || ty >= 3) continue;
			swap(tmp[pos], tmp[tx * 3 + ty]);
			if(!mp.count(tmp)) {
				mp[tmp] = mp[t] + 1;
				q.push({-mp[tmp] + f(tmp), tmp});
			}
			swap(tmp[pos], tmp[tx * 3 + ty]);
		}
	}
	cout << mp[ed];
	return 0;
}

int f(string s)
{
	int ans = 0;
	for(int i = 0; i < 9; i++){
		int t = s[i] - '0';
		if(t != 0) ans += abs(i / 3 - gx[t]) + abs(i % 3 - gy[t]);
	}
	return ans;
}