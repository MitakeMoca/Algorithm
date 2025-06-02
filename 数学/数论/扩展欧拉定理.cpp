#include <bits/stdc++.h>
using namespace std;

const int BASE = 10000; 
const int BASE_DIGITS = 4; 

struct Big {
    vector<int> digits;

    // 当前数 > other，返回 1；小于返回 -1；等于返回 0
    int cmp(const Big& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() > other.digits.size() ? 1 : -1;
        
        for (int i = digits.size() - 1; i >= 0; i--) 
            if (digits[i] != other.digits[i]) 
                return digits[i] > other.digits[i] ? 1 : -1;
        
        return 0;
    }

    Big() : digits({0}) {}

    Big(long long num) {
        if (num == 0) {
            digits = {0};
            return;
        }
        
        while (num > 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }

    Big(const string& str) {
        for (int i = str.size() - 1; i >= 0; i -= BASE_DIGITS) {
            int digit = 0;
            int end = max(0, i - BASE_DIGITS + 1);
            for (int j = end; j <= i; j++) {
                digit = digit * 10 + (str[j] - '0');
            }
            digits.push_back(digit);
        }
        
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }

    Big(const Big& other) : digits(other.digits) {}

    Big& operator=(const Big& other) {
        digits = other.digits;
        return *this;
    }

    Big operator+(const Big& other) const {
        Big result;
        result.digits.clear();

        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());
        
        for (int i = 0; i < maxSize || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            
            carry = sum >= BASE;
            if (carry) sum -= BASE;
            
            result.digits.push_back(sum);
        }
        
        return result;
    }

    // 假设当前数 >= other
    Big operator-(const Big& other) const {
        Big result;
        result.digits.clear();
        
        int borrow = 0;
        for (int i = 0; i < digits.size(); i++) {
            int diff = digits[i] - borrow;
            if (i < other.digits.size()) diff -= other.digits[i];
            
            borrow = 0;
            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            }
            
            result.digits.push_back(diff);
        }
        
        // 去除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
        
        return result;
    }

    Big operator*(const int& other) const {
        if (other == 0) return Big(0);
        
        Big result;
        result.digits.clear();
        
        long long carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i < digits.size()) carry += (long long)digits[i] * other;
            
            result.digits.push_back(carry % BASE);
            carry /= BASE;
        }
        
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
            
        return result;
    }

    Big operator*(const Big& other) const {
        if (other == 0) return Big(0);
        
        Big result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        
        for (int i = 0; i < digits.size(); i++) {
            long long carry = 0;
            for (int j = 0; j < other.digits.size() || carry; j++) {
                long long product = result.digits[i + j] + carry;
                if (j < other.digits.size()) 
                    product += (long long)digits[i] * other.digits[j];
                
                result.digits[i + j] = product % BASE;
                carry = product / BASE;
            }
        }
        
        // 去除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
            
        return result;
    }

    Big operator/(const int& divisor) const {
        Big result;
        result.digits.resize(digits.size());
        
        long long remainder = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            long long current = remainder * BASE + digits[i];
            result.digits[i] = current / divisor;
            remainder = current % divisor;
        }
        
        // 去除前导零
        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
            
        return result;
    }

    int operator%(const int& divisor) const {
        long long remain = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            remain = (remain * BASE + digits[i]) % divisor;
        }
        return remain;
    }

    Big operator^(long long exponent) const {
        Big base(*this);
        Big result(1);
        
        while (exponent > 0) {
            if (exponent & 1) 
                result = result * base;
            
            base = base * base;
            exponent >>= 1;
        }
        
        return result;
    }

    bool operator<(const Big& other) const { return cmp(other) == -1; }
    bool operator<=(const Big& other) const { return cmp(other) <= 0; }
    bool operator>(const Big& other) const { return cmp(other) == 1; }
    bool operator>=(const Big& other) const { return cmp(other) >= 0; }
    bool operator==(const Big& other) const { return cmp(other) == 0; }
    bool operator!=(const Big& other) const { return cmp(other) != 0; }
    
    bool operator<(long long num) const { return *this < Big(num); }
    bool operator>(long long num) const { return *this > Big(num); }
    bool operator<=(long long num) const { return *this <= Big(num); }
    bool operator>=(long long num) const { return *this >= Big(num); }
    bool operator==(long long num) const { return *this == Big(num); }
    bool operator!=(long long num) const { return *this != Big(num); }
    
    void print() const {
        cout << digits.back(); // 最高位不需要前导零
        
        for (int i = digits.size() - 2; i >= 0; i--) 
            cout << setw(BASE_DIGITS) << setfill('0') << digits[i];
    }
    
    string toString() const {
        string result;
        result += to_string(digits.back());
        
        for (int i = digits.size() - 2; i >= 0; i--) {
            string segment = to_string(digits[i]);
            result += string(BASE_DIGITS - segment.size(), '0') + segment;
        }
        return result;
    }
    
    friend ostream& operator<<(ostream& os, const Big& num) {
        os << num.digits.back();
        for (int i = num.digits.size() - 2; i >= 0; i--) 
            os << setw(BASE_DIGITS) << setfill('0') << num.digits[i];
        return os;
    }
};

int read() {
    int tem;
    scanf("%d", &tem);
    return tem;
}
char str[20000005];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int phi(int n) {
	int ans = n;
	for(int i = 2; i <= sqrt(n); i++) 
		if(n % i == 0) {
			ans = ans / i * (i - 1);
			while(n % i == 0)
				n /= i;
		}
	if(n > 1)
		ans = ans / n * (n - 1);
	return ans;
}
typedef long long ll;

ll quickPow(ll a, Big b, int mod) {
    ll exp = 0;
    string s = b.toString();
    for(auto i : s)
        exp = exp * 10 + i - '0';
    ll ret = 1;
    while(exp) {
        if(exp & 1)
            ret = ret * a % mod;
        a = a * a % mod;
        exp >>= 1;
    }
    return ret;
}

int ExEuler(int a, Big b, int n) {
    int phi_n = phi(n);
    if(gcd(a, n) == 1) 
        return quickPow(a, b % phi_n, n);
    else if(b < phi_n) 
        return quickPow(a, b, n);
    return quickPow(a, b % phi_n + phi_n, n);
}

int main() {
    int a = read();
    int n = read();
    scanf("%s", str);
    Big b = Big(str);
    cout << ExEuler(a, b, n);
}