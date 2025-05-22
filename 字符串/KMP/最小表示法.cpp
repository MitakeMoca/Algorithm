/*
    求字符串 s 的最小表示的起始位置
        1. 可先将 s 复制一份在它的结尾，得到的字符串为 ss，有 B[i] = ss[i ~ i + n - 1]
        2. 在比较 B[i] 与 B[j] 的过程中，如果在 i + k 与 j + k 处发现不相等
           假设 ss[i+k] > ss[j+k]，那么显然 B[i] 不是 s 的最小表示
           此外还可以知道 B[i+1], B[i+2], ..., B[i+k] 也不是 S 的最小表示。
        3. 同理，如果 ss[i+k] < ss[j+k]
           那么 B[j], B[j+1], ..., B[j+k] 都不是 S 的最小表示。
    时间复杂度：O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n;
char s[N];

// nxt 数组，以及字符串都从 1 开始
void min_presentation() {
	// 字符串从 1 开始
    int n = strlen(s + 1);
    for(int i = 1; i <= n; i++)
        s[n + i] = s[i];
    int i = 1, j = 2, k;
    while(i <= n && j <= n) {
        for(k = 0; k < n && s[i + k] == s[j + k]; k++);
        if(k == n)
            break;
        if(s[i + k] > s[j + k]) {
            i = i + k + 1;
            if(i == j) i++;
        } else {
            j = j + k + 1;
            if(i == j) j++;
        }
    }
    int ans = min(i, j);
}