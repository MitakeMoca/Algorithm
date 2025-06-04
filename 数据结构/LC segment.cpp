#include <bits/stdc++.h>
using namespace std;

#define lc (t << 1)
#define rc (lc | 1)

struct line {
	double k, b;
}p[100005];
int tr[160000] = {0};
int high[40005] = {0};
int ans[400005] = {0};
int cnt = 0;

const int Px = 39989;
const int Py = 1e9;
const double eps = 1e-5;

double calc(line a, int x)
{
	return a.k * x + a.b;
}

int cmp(double a, double b)
{
	if (a - b > eps) return 1;
	if (b - a > eps) return -1;
	return 0;
}

void insert(int t, int l, int r, int x, int y, int id)
{
	int m = l + r >> 1;
	if (x <= l && y >= r) {
		int cp0 = cmp(calc(p[id], m), calc(p[tr[t]], m));
		if (cp0 == 1 || (cp0 == 0 && id < tr[t])) swap(id, tr[t]);
		int cp1 = cmp(calc(p[id], l), calc(p[tr[t]], l));
		if (cp1 == 1 || (cp1 == 0 && id < tr[t])) insert(lc, l, m, x, y, id);
		int cp2 = cmp(calc(p[id], r), calc(p[tr[t]], r));
		if (cp2 == 1 || (cp2 == 0 && id < tr[t])) insert(rc, m + 1, r, x, y, id);
		return;
	}

	if (x <= m) insert(lc, l, m, x, y, id);
	if (y > m) insert(rc, m + 1, r, x, y, id);
}

int max(int a, int b, int pos)
{
	int cp = cmp(calc(p[a], pos), calc(p[b], pos));
	if (cp == 1) return a;
	if (cp == -1) return b;
	if (cp == 0) return min(a, b);
}

int query(int t, int l, int r, int pos)
{
	if (l == r) return tr[t];
	int m = l + r >> 1, mx = tr[t];

	if (pos <= m) mx = max(mx, query(lc, l, m, pos), pos);
	else mx = max(mx, query(rc, m + 1, r, pos), pos);
	return mx;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	int last = 0;
	int op, x1, y1, x2, y2;

	for (int i = 0; i < n; i++) {
		cin >> op;
		if (op == 1) {
			++cnt;
			cin >> x1 >> y1 >> x2 >> y2;
			x1 = (x1 + last - 1) % Px + 1;
			x2 = (x2 + last - 1) % Px + 1;
			y1 = (y1 + last - 1) % Py + 1;
			y2 = (y2 + last - 1) % Py + 1;

			if (x1 == x2) {	
				p[cnt].k = 0;
				p[cnt].b = max(y1, y2);
			}
			else {
				p[cnt].k = 1.0 * (y1 - y2) / (x1 - x2);
				p[cnt].b = y1 - p[cnt].k * x1;
			}
			insert(1, 1, Px, min(x1, x2), max(x1, x2), cnt);
		}
		else {
			cin >> x1;
			x1 = (x1 + last - 1) % Px + 1;
			last = query(1, 1, Px, x1);
			cout << last << '\n';
		}
	}
	return 0;
}