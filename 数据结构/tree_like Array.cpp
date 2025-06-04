#include <bits/stdc++.h>
using namespace std;

long long sum[500005] = {0};

int lowbit(int x)
{
	return x & -x;
}

void change(int x, long long k, int n)
{
	while(x <= n) sum[x] += k, x += lowbit(x);
}

long long query(int x)
{
	long long ans = 0;
	while(x != 0) ans += sum[x], x -= lowbit(x);
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	long long k;
	for(int i = 1; i <= n; i++){
		cin >> k;
		change(i, k, n);
	}
	
	int op, l, r;
	while(m--){
		cin >> op;
		if(op == 1) {
			cin >> l >> k;
			change(l, k, n);
		}
		else{
			cin >> l >> r;
			cout << query(r) - query(l - 1) << '\n';
		}
	}
	return 0;
}