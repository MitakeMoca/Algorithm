#include <bits/stdc++.h>
using namespace std;

vector<int> p[100005];
int C[100005] = {0};

bool judge(int t, int c);

int main()
{
	int n, m;
	cin >> n >> m;

	int u, v;
	while(m--){
		cin >> u >> v;
		p[u].push_back(v);
		p[v].push_back(u);
	}

	for(int i = 1; i <= n; i++){
		if(C[i] == 0){
			if(judge(i, 1)){
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	return 0;
}

bool judge(int t, int c)
{
	C[t] = c;

	for(auto i: p[t]) {
		if(C[i] == 0) {
			if(judge(i, 3 - c)) return true;
		}
		else if(C[i] == c) return true;
	}
	return false;
}