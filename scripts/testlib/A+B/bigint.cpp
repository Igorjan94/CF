#include <bits/stdc++.h>
#include <writeln.h>

using namespace std;

#define SZ(container) int(container.size())

template<typename T, typename F>
T binSearch(T l, T r, F f, T eps)
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

static constexpr int binpow(int x, int d) {
    int ret = 1;
    for (int i = 0; i < d; ++i)
        ret *= x;
    return ret;
};
static const int BASE = 10;
static const int POW = 9;
template<typename T = int, size_t B = binpow(BASE, POW)>
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

public:
    auto begin() const { return a.crbegin(); }
    auto end() const { return a.crend(); }

private:
    // Friend stream operators {{{
    friend std::ostream & operator<< <>(std::ostream &os, bigint<T, B> b);
    friend std::istream & operator>> <>(std::istream &os, bigint<T, B>& b);
    // }}}

    template<typename X, typename F>
    static void addVectors(vector<X>& x, const vector<X>& y, F f = bigint::add, int index = 0) // {{{
    {
        for (int i = 0, carry = 0; i < SZ(y) || carry; ++i)
        {
            const auto& [value, currentCarry] = f(getDigit(x, i + index), getDigit(y, i) + carry);
            setDigit(x, i + index, value);
            carry = currentCarry;
        }
    } // }}}

    template<typename X>
    static vector<X> mulVectorDigit(const vector<X>& x, X y) // {{{
    {
        vector<X> temp(SZ(x));
        X carry = 0;
        for (int i = 0; i < SZ(x) || carry; ++i)
        {
            const auto& [value, residue] = mul(getDigit(x, i), y);
            const auto& [summ, currentCarry] = add(residue, carry);
            setDigit(temp, i, summ);
            carry = value + currentCarry;
        }
        return move(temp);
    } // }}}

    template<typename X>
    static void mulVectors(vector<X>& x, const vector<X>& y) // {{{
    {
        vector<X> temp(SZ(x) + SZ(y) - 1);
        for (int i = 0; i < SZ(y); ++i)
            addVectors(temp, mulVectorDigit<X>(x, y[i]), bigint::add, i);
        x = temp;
    } // }}}

    pair<bigint, bigint> divmod(const bigint& x, const bigint& z) // {{{
    {
        bigint zero = bigint(0);
        if (z == zero)
            throw "Division by zero!";
        int xs = x.sign;
        int ys = z.sign;
        bigint y = z.abs();

        if (x.abs() < y)
            return {zero, x};

        bigint div, mod;
        div.a.clear();
        mod.a.clear();
        for (int i = SZ(a) - 1; i >= 0; --i)
        {
            mod.a.insert(mod.a.begin(), a[i]);
            mod.trimZeroes();
            T xxx = binSearch(T(0), T(B), [&](T m) { return bigint(m) * y > mod; }, T(1));
            if (xxx)
            {
                --xxx;
                mod -= bigint(xxx) * y;
                div.a.insert(div.a.begin(), xxx);
                div.trimZeroes();
            }
        }
        div.sign = xs * ys;
        mod.sign = xs;
        return {div, mod};
    } // }}}}

    //Secure arithmetics {{{
    static pair<T, T> add(T x, T y)
    {
        if (x >= B - y)
            return {x - (B - y), 1};
        return {x + y, 0};
    }

    static pair<T, T> sub(T x, T y)
    {
        if (x < y)
            return {x + (B - y), 1};
        return {x - y, 0};
    }

    static pair<T, T> mul(T x, T y)
    {
        long long m = x * 1ll * y;
        return {m / B, m % B};
    }
    // }}}

    //Secure get by index {{{
    T get(unsigned i) { return getDigit(a, i); }

    template<typename C>
    static T getDigit(C& c, unsigned i)
    {
        return c[i];
        //return i >= c.size() || i < 0 ? T(0) : c[i];
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
        if (c.size() == 0)
            c.push_back(T(0));
    }

    void trimZeroes()
    {
        trimZeroes(a);
    } // }}}

    bigint abs() const // {{{
    {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    } // }}}
    
    //Shift-unshift {{{
    void shift(int d)
    {
        int sz = min(size(), ::abs(d));
        if (d > 0)
            a.erase(a.begin() + size() - sz, a.end());
        else
            a.erase(a.begin(), a.begin() + sz);
        trimZeroes();
    }

    void unshift(int d)
    {
        vector<T> temp(d, 0);
        copy(a.begin(), a.end(), back_inserter(temp));
        a = temp;
    }
    // }}}

    //Karatsuba multiply {{{
    void fastMul(const bigint& y)
    {
        int xs = size();
        int ys = y.size();
        int m = max(xs, ys) / 2;
        bigint a0(*this);
        bigint a1(*this);
        bigint b0(y);
        bigint b1(y);

        a0.shift(max(0, xs - m));
        a1.shift(-m);
        b0.shift(max(0, ys - m));
        b1.shift(-m);

        bigint&& a0b0 = a0 * b0;
        bigint&& a1b1 = a1 * b1;
        bigint&& temp = (a0 + a1) * (b0 + b1) - a0b0 - a1b1;

        temp.unshift(m);
        a1b1.unshift(2 * m);

        *this = a0b0 + temp + a1b1;
    } // }}}

    string toString() // {{{
    {
        stringstream os;
        int l = a.size();
        if (sign == -1 && (l != 1 || a[0]))
            os << '-';
        for (int i = 0; i < a.size(); ++i)
        {
            string temp = to_string(a[l - i - 1]);
            if (i && temp.size() != POW) os << string(POW - temp.size(), '0');
            os << temp;
        }
        return os.str();
    } // }}}

public:
    // Constuctors {{{
    bigint() {}

    bigint(long long x)
    {
        if (x < 0)
            sign = -1,
            x *= -1;
        a.clear();
        while (x)
            a.push_back(x % B),
            x /= B;
        a.push_back(0);
        trimZeroes();
    }

    bigint(const string& s)
    {
        a.resize(SZ(s) / POW, 0);
        bool ok = s[0] == '-';
        int exs = (SZ(s) - ok) % POW;
        if (exs)
            a.push_back(stoi(s.substr(ok, exs)));
        for (int i = exs + ok; i < SZ(s); i += POW)
            a.push_back(stoi(s.substr(i, POW).c_str()));
        reverse(a.begin(), a.end());
        if (ok) sign = -1;
        trimZeroes();
    }
    // }}}

    void operator=(const bigint& v) { // {{{
        sign = v.sign;
        a = v.a;
    } // }}}

    template<typename T1>
    void operator=(const T1& v) {
        *this = bigint(v);
    };

    T operator[](int i) { return a[i]; }

    int size() const { return SZ(a); }

    // ?= operators {{{
    bigint& operator+=(const bigint& x) // {{{
    {
        if (sign == x.sign)
            addVectors(a, x.a, bigint::add),
            trimZeroes();
        else
            *this -= -x;
        return *this;
    } // }}}

    bigint& operator-=(const bigint& x) // {{{
    {
        if (sign == x.sign)
        {
            if (abs() < x.abs())
            {
                bigint temp = x;
                temp -= *this;
                *this = -temp;
                return *this;
            }
            addVectors(a, x.a, bigint::sub);
            trimZeroes();
        }
        else
            *this += -x;
        return *this;
    } // }}}

    bigint& operator*=(const bigint& x) // {{{
    {
        int resSign = sign * x.sign;
        sign = 1;
        if (x.size() * size() <= 3000)
            mulVectors(a, x.a);
        else
            fastMul(x);
        sign = resSign;
        return *this;
    }
    // }}}

    bigint& operator/=(const bigint& x) // {{{
    {
        *this = divmod(*this, x).first;
        return *this;
    }
    // }}}

    bigint& operator%=(const bigint& x) // {{{
    {
        *this = divmod(*this, x).second;
        return *this;
    }
    // }}}
    // }}}

    // Binary operators {{{
    bigint operator+(const bigint& v) const { return bigint(*this) += v; }
    bigint operator-(const bigint& v) const { return bigint(*this) -= v; }
    bigint operator/(const bigint& v) const { return bigint(*this) /= v; }
    bigint operator%(const bigint& v) const { return bigint(*this) %= v; }
    bigint operator*(const bigint& v) const { return bigint(*this) *= v; }
    bigint operator-() const { bigint res = *this; res.sign = -sign; return res; }
    // }}}

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

    // Cast {{{
    template<typename T2, size_t B2>
    operator bigint<T2, B2>() {
        typedef bigint<T2, B2> bigint2;
        bigint2 temp(0);
        bigint2 deg(1);
        bigint2 base(B);
        for (T& x : a)
            temp += deg * bigint2(x),
            deg *= base;
        if (sign == -1)
            temp *= bigint2(-1);
        return temp;
    }
    // }}}

    void write() const
    {
        for (auto&& x : *this)
            cout << x << " ";
        writeln();
    }
};

int main()
{
    bigint c, d;
    readln(c, d);
    writeln(c + d);
    writeln(c - d);
    writeln(c * d);
    writeln(c / d, c % d);
    return 0;
}
