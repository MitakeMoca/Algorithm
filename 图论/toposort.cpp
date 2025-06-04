#include <bits/stdc++.h>
using namespace std;

int din[105] = {0};
vector<int> p[105];
vector<int> topo;

void Kahn(int n);

int main()
{
	int n, a;
	cin >> n;

	for(int i = 1; i <= n; i++){
		while(cin >> a){
			if(a == 0) break;
			din[a]++;
			p[i].push_back(a);
		}
	}

	Kahn(n);
	return 0;
}

void Kahn(int n)
{
	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(din[i] == 0) q.push(i);
	}

	while(!q.empty()){
		int t = q.front();
		q.pop();
		topo.push_back(t);

		for(auto i: p[t]){
			din[i]--;
			if(din[i] == 0) q.push(i);
		}
	}

	for(auto i: topo){
		cout << i <<' ';
	}
}