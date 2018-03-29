#include <bits/stdc++.h>
#include <writeln.h>

using namespace std;

#define SZ(container) int(container.size())

template<typename T, size_t B = numeric_limits<T>::max()>
struct bigint;

// Ostream operator << {{{
template<typename T, size_t B>
std::ostream & operator<<(std::ostream &os, bigint<T, B> b)
{
    return os << b.toString();
} // }}}

// Istream operator >> {{{
template<typename T, size_t B>
std::istream & operator>>(std::istream &is, bigint<T, B>& b)
{
    string s;
    is >> s;
    b = bigint<T, B>(s);
    return is;
} // }}}

template<typename T, size_t B>
struct bigint
{
private:
    vector<T> a = {0};
    int sign = 1;

    // Friend stream operators {{{
    friend std::ostream & operator<< <>(std::ostream &os, bigint<T, B> b);
    friend std::istream & operator>> <>(std::istream &os, bigint<T, B>& b);
    // }}}

    static vector<int> toVectorInt(T t) // {{{
    {
        vector<int> temp;
        while (t)
            temp.push_back(t % 10),
            t /= 10;
        return temp;
    } // }}}

    static void addVectors(vector<int>& x, vector<int> y, int index = 0) // {{{
    {
        for (int i = 0, carry = 0; i < SZ(y) || carry; ++i)
        {
            int value = getDigit(x, i + index) + getDigit(y, i) + carry;
            carry = value > 9;
            if (carry) value -= 10;
            setDigit(x, i + index, value);
        }
    } // }}}

    static void mul(vector<int>& x, vector<int>& y) // {{{
    {
        vector<int> temp;
        for (int i = 0; i < SZ(y); ++i)
            if (y[i])
                for (int j = 0; j < y[i]; ++j)
                    addVectors(temp, x, i);
            else
                temp.push_back(0);
        x = temp;
    } // }}}

    string toString() // {{{
    {
        auto base = toVectorInt(B);

        stringstream os;
        if (sign == -1 && (a.size() != 1 || a[0]))
            os << '-';
        vector<int> temp = {0};
        for (int i = SZ(a) - 1; i >= 0; --i)
            mul(temp, base),
            addVectors(temp, toVectorInt(a[i]));
        trimZeroes(temp);
        reverse(temp.begin(), temp.end());
        for (int& x : temp)
            os << x;
        return os.str();
    } // }}}

    // Secure add/sub {{{
    static pair<T, T> add(T x, T y)
    {
        if (x >= B - y)
            return {x - (B - y), 1};
        else
            return {x + y, 0};
    }

    static pair<T, T> sub(T x, T y)
    {
        if (x < y)
            return {x + (B - y), 1};
        else
            return {x - y, 0};
    } // }}}

    // Calc {{{
    template<typename F>
    void calc(bigint<T, B>& x, F f)
    {
        for (int i = 0, carry = 0; i < max(SZ(a), SZ(x.a)) || carry; ++i)
        {
            auto [value, currCarry] = f(get(i), x.get(i) + carry);
            setDigit(a, i, value);
            carry = currCarry;
        }
    } // }}}

    //Secure get by index {{{
    T get(unsigned i) { return getDigit(a, i); }

    template<typename C>
    static T getDigit(C& c, unsigned i)
    {
        return i >= c.size() || i < 0 ? T(0) : c[i];
    } // }}}

    //Secure set by index {{{
    template<typename C>
    static void setDigit(C& c, unsigned i, T value)
    {
        if (i >= c.size())
            c.push_back(value);
        else
            c[i] = value;
    } // }}}

    // Trim leading zeroes {{{
    template<typename C>
    void trimZeroes(C& c)
    {
        while (c.size() > 1 && !c.back())
            c.pop_back();
    }

    void trimZeroes()
    {
        trimZeroes(a);
    } // }}}

    bigint abs() // {{{
    {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    } // }}}

    static bool cmp(string& x, int index, string& y) // {{{
    {
        if (index && x[index - 1] > '0')
            return true;
        for (int i = 0; i < SZ(y); ++i)
            if (x[index + i] != y[i])
                return x[index + i] > y[i];
        return true;
    } // }}}

    static bool substruct(string& x, int index, string& y) // {{{
    {
        bool ge = cmp(x, index, y);
        if (ge)
            for (int i = SZ(y) - 1, carry = 0; i >= 0 || carry; --i)
            {
                x[index + i] = x[index + i] - carry - (i >= 0 ? y[i] - '0' : 0);
                if (x[index + i] < '0')
                    carry = 1,
                    x[index + i] += 10;
                else
                    carry = 0;
            }
        return ge;
    } // }}}

    static pair<T, string> divide(string& x, string& y) // {{{
    {
        string ans;
        int yz = SZ(y);
        int xz = SZ(x);
        for (int i = 0; i + yz <= xz; ++i)
        {
            ans.push_back('0');
            while (substruct(x, i, y))
                ans.back()++;
        }
        while (ans.size() && ans[0] == '0') ans.erase(ans.begin());
        return {stoll(x.substr(max(0, xz - yz), yz)), ans};
    } // }}}

public:
    // Constuctors {{{
    bigint() {}

    bigint(string s)
    {
        string base = to_string(B);
        a.clear();
        if (s[0] == '-')
            sign = -1,
            s.erase(s.begin());

        do
        {
            auto [rem, div] = divide(s, base);
            a.push_back(rem);
            s = div;
        }
        while (s.size());

        trimZeroes();
    }
    // }}}

    void operator=(const bigint &v) { // {{{
        sign = v.sign;
        a = v.a;
    } // }}}

    T operator[](int i) { return a[i]; }

    // ?= operators {{{
    bigint& operator+=(bigint x) // {{{
    {
        if (sign == x.sign)
            calc(x, bigint::add),
            trimZeroes();
        else
            *this -= -x;
        return *this;
    } // }}}

    bigint& operator-=(bigint x) // {{{
    {
        if (sign == x.sign)
        {
            if (abs() < x.abs())
            {
                swap(*this, x);
                *this -= x;
                sign *= -1;
                return *this;
            }
            calc(x, bigint::sub);
            trimZeroes();
        }
        else
            *this += -x;
        return *this;
    } // }}}
    // }}}

    // Binary operators {{{
    bigint operator+(const bigint &v)
    {
        bigint<T, B> sum = *this;
        return sum += v;
    }

    bigint operator-(const bigint &v)
    {
        bigint<T, B> sum = *this;
        return sum -= v;
    }
    // }}}
    
    bigint operator-() const // {{{
    {
        bigint res = *this;
        res.sign = -sign;
        return res;
    } // }}}

    // Compare operators {{{
    bool operator<(const bigint &v) const
    {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * sign;
        for (int i = SZ(a) - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const bigint &v) const { return v < *this; }
    bool operator<=(const bigint &v) const { return !(v < *this); }
    bool operator>=(const bigint &v) const { return !(*this < v); }
    bool operator==(const bigint &v) const { return !(*this < v) && !(v < *this); }
    bool operator!=(const bigint &v) const { return *this < v || v < *this; }
    // }}}

    template<typename T2, size_t B2>
    explicit operator bigint<T2, B2>() {
        return bigint<T2, B2>(toString());
    }

    void write()
    {
        for (auto&& x : *this)
            cout << x << " ";
        writeln();
    }

    auto begin() const { return a.crbegin(); }
    auto end() const { return a.crend(); }
};

int main()
{
    bigint<long long> a, b;
    readln(a, b);
    writeln(a + b);
    writeln(a - b);
    return 0;
}
