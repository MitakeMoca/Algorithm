/*
    有插入和查找两种操作
    字典树通常还用在位运算相关的题目里，比如找异或值最大的两个数
*/

#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e5 + 5;

int trie[SIZE][26], tot = 1;
bool vis[SIZE];

void insert(char *str) {
    int len = strlen(str), p = 1;
    for(int k = 0; k < len; k++) {
        int ch = str[k] - 'a';
        if(trie[p][ch] == 0)
            trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    vis[p] = true;
}

bool search(char *str) {
    int len = strlen(str), p = 1;
    for(int k = 0; k < len; k++) {
        p = trie[p][str[k] - 'a'];
        if(p == 0)
            return false;
    }
    return vis[p];
}