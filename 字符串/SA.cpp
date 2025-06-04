#include <bits/stdc++.h>
using namespace std;

int x[2000005] = {0};
int y[2000005] = {0};
int sa[2000005] = {0};
int c[2000005] = {0};

void get_sa(string s);

int main()
{
	string s;
	cin >> s;
	get_sa(s);
	return 0;
}

void get_sa(string s)
{
	int len = s.size();
	int m = 128, i, j, k;

	for(i = 1; i <= len; i++) x[i] = s[i - 1];
	for(i = 1; i <= len; i++) c[x[i]]++;
	for(i = 1; i <= m; i++) c[i] += c[i - 1];
	for(i = len; i > 0; i--) sa[c[x[i]]--] = i;

	for(k = 1; k <= len; k <<= 1){
		
		memset(c, 0, sizeof(c));
		for(i = 1; i <= len; i++) y[i] = sa[i];
		for(i = 1; i <= len; i++) c[x[y[i] + k]]++;
		for(i = 1; i <= m; i++) c[i] += c[i - 1];
		for(i = len; i > 0; i--) sa[c[x[y[i] + k]]--] = y[i];
		
		memset(c, 0, sizeof(c));
		for(i = 1; i <= len; i++) y[i] = sa[i];
		for(i = 1; i <= len; i++) c[x[y[i]]]++;
		for(i = 1; i <= m; i++) c[i] += c[i - 1];
		for(i = len; i > 0; i--) sa[c[x[y[i]]]--] = y[i]; 
		
		memset(c, 0, sizeof(c));
		for(i = 0; i <= len; i++) y[i] = x[i];
		for(m = 0, i = 1; i <= len; i++){
			if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]){
				x[sa[i]] = m;
			}
			else{
				x[sa[i]] = ++m;
			}
		}
		if(m == len){
			break;
		}
	}
	for(i = 1; i <= len; i++){
		printf("%d ", sa[i]);
	}
}