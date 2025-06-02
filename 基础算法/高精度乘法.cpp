#include <vector>
#include <algorithm> // for reverse
using namespace std;

void remove_leading_zeros(vector<int>& num) {
    while (num.size() > 1 && num.back() == 0) 
        num.pop_back();
}

bool is_zero(vector<int>& A) {
    return A.size() == 1 && A[0] == 0;
}

vector<int> mul(vector<int>& A, vector<int>& B) {
    if(is_zero(A) || is_zero(B))
        return {0};
    
    int m = A.size(), n = B.size();
    vector<int> C(m + n, 0); 
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i + j] += A[i] * B[j];  // 累加到对应位置
        }
    }
    
    // 统一处理进位
    int carry = 0;
    for (int i = 0; i < m + n; i++) {
        int total = C[i] + carry;
        C[i] = total % 10;  
        carry = total / 10;   
    }
    
    if (carry) 
        C.push_back(carry);
    
    while (C.size() > 1 && C.back() == 0) 
        C.pop_back();
    return C;
}