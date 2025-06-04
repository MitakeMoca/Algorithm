#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc ((t << 1) | 1)

int A[100005];

int n, cnt = 0;

void up(int t)
{
	if((t >> 1) != 0 && A[t] < A[t >> 1]){
		swap(A[t], A[t >> 1]);
		up(t >> 1);
	}
}

void push(int x)
{
	A[++cnt] = x;
	up(cnt);
}

void down(int t)
{
	int v = t;
	if(lc <= cnt && A[lc] < A[v]) v = lc;
	if(rc <= cnt && A[rc] < A[v]) v = rc;
	if(v != t){
		swap(A[v], A[t]);
		down(v);
	}
}

void pop()
{
	A[1] = A[cnt--];
	down(1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, a;
	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> a;
		push(a);
	}

	for(int i = 0; i < n; i++){
		cout << A[1] << ' ';
		pop();
	}
	return 0;
}