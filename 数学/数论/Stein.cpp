#include <bits/stdc++.h>
using namespace std;

vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i ++ )
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || t; i ++ )
    {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    return C;
}

vector<int> div(vector<int> &A, int b, int &r) {
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i -- )
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

bool is_zero(vector<int> &A) {
    return (A.size() == 1) && (A[0] == 0);
}

int big_cmp(const vector<int>& A, const vector<int>& B) {
    if (A.size() > B.size()) return 1;
    if (A.size() < B.size()) return -1; 
    
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] > B[i]) return 1;  
        if (A[i] < B[i]) return -1; 
    }
    
    return 0;
}

vector<int> Stein(vector<int> A, vector<int> B) {
    // 记录有多少个 2 因子
    int shift = 0;
    while(!is_zero(A) && !is_zero(B)) {
        bool f1 = (A[0] % 2) == 0;
        bool f2 = (B[0] % 2) == 0;
        int r1, r2;

        if(f1 && f2) {
            A = div(A, 2, r1);
            B = div(B, 2, r2);
            shift++;
        } else if(f1)
            A = div(A, 2, r1);
        else if(f2) 
            B = div(B, 2, r2);
        else {
            if(big_cmp(A, B) >= 0)
                A = sub(A, B);
            else
                B = sub(B, A);
        }
    }

    vector<int> result = is_zero(A) ? B : A;
    for (int i = 0; i < shift; i++) 
        result = mul(result, 2);
    
    return result;
}

char str[10005];
vector<int> a, b;

int main() {
    scanf("%s", str);
    int len = strlen(str);
    for(int i = 0; i < len; i++)
        a.push_back(str[i] - '0');
    scanf("%s", str);
    len = strlen(str);
    for(int i = 0; i < len; i++)
        b.push_back(str[i] - '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int> c = Stein(a, b);
    for(int i = c.size() - 1; i >= 0; i--)
        printf("%d", c[i]);

    return 0;
}