#include <bits/stdc++.h>
using namespace std;

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
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    Big(const string& str) {
        for (int i = str.size() - 1; i >= 0; i--) 
            digits.push_back(str[i] - '0');
    }

    Big(const Big& other) : digits(other.digits) {}

    Big& operator=(const Big& other) {
        digits = other.digits;
        return *this;
    }

    Big operator+(const Big& other) const {
        Big result;
        result.digits.clear();

        int t = 0;
        int maxSize = max(digits.size(), other.digits.size());
        
        for (int i = 0; i < maxSize; i++) {
            if (i < digits.size()) t += digits[i];
            if (i < other.digits.size()) t += other.digits[i];
            
            result.digits.push_back(t % 10);
            t /= 10;
        }

        if(t)
            result.digits.push_back(t);
        
        return result;
    }

    // 必须大 - 小
    Big operator-(const Big& other) const {
        Big result;
        result.digits.clear();
        
        for (int i = 0, t = 0; i < digits.size(); i++) {
            t = digits[i] - t;
            if (i < other.digits.size()) t -= other.digits[i];
            result.digits.push_back((t + 10) % 10);
            if(t < 0) t = 1;
            else t = 0;
        }

        while(result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
        
        return result;
    }

    Big operator*(const int& other) const {
        if(other == 0)
            return Big(0);
        Big result;
        result.digits.clear();
        for(int i = 0, t = 0; i < digits.size() || t; i++) {
            if(i < digits.size()) t += digits[i] * other;
            result.digits.push_back(t % 10);
            t /= 10;
        }
        return result;
    }

    Big operator*(const Big& other) const {
        if((*this) == 0 || other == 0) 
            return Big(0);
        int m = digits.size(), n = other.digits.size();
        Big result;
        result.digits = vector<int>(digits.size() + other.digits.size(), 0);

        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                result.digits[i + j] += digits[i] * other.digits[j];

        int carry = 0;
        for(int i = 0; i < m + n; i++) {
            int total = result.digits[i] + carry;
            result.digits[i] = total % 10;
            carry = total / 10;
        }

        if(carry)
            result.digits.push_back(carry);

        while(result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
        return result;
    }

    // other 不应该为 0
    Big operator/(const int& other) const {
        Big result;
        result.digits.clear();

        for(int i = digits.size() - 1, r = 0; i >= 0; i--) {
            r = r * 10 + digits[i];
            result.digits.push_back(r / other);
            r %= other;
        }
        reverse(result.digits.begin(), result.digits.end());
        while(result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();
        return result;
    }

    Big operator%(const int& other) const {
        Big a = *this / other;
        Big b = *this - a * other;
        return b;
    }

    Big operator^(long long other) const {
        Big result(1);
        Big base(*this);

        while (other > 0) {
            if(other & 1)
                result = result * base;
            base = base * base;
            other >>= 1;
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
        for (int i = digits.size() - 1; i >= 0; i--) 
            cout << digits[i];
    }
    
    string toString() const {
        string str;
        for (int i = digits.size() - 1; i >= 0; i--) 
            str += ('0' + digits[i]);
        return str;
    }
    
    friend ostream& operator<<(ostream& os, const Big& num) {
        for (int i = num.digits.size() - 1; i >= 0; i--) 
            os << num.digits[i];
        return os;
    }
};