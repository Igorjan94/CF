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

public:
    auto begin() const { return a.crbegin(); }
    auto end() const { return a.crend(); }

private:
    // Friend stream operators {{{
    friend std::ostream & operator<< <>(std::ostream &os, bigint<T, B> b);
    friend std::istream & operator>> <>(std::istream &os, bigint<T, B>& b);
    // }}}

    template<typename X, typename F>
    static void addVectors(vector<X>& x, vector<X> y, F f = bigint::add, int index = 0) // {{{
    {
        for (int i = 0, carry = 0; i < SZ(y) || carry; ++i)
        {
            auto [value, currentCarry] = f(getDigit(x, i + index), getDigit(y, i) + carry);
            setDigit(x, i + index, value);
            carry = currentCarry;
        }
    } // }}}

    template<typename X>
    static vector<X> mulVectorDigit(vector<X> x, X y) // {{{
    {
        vector<X> temp;
        X carry = 0;
        for (int i = 0; i < SZ(x) || carry; ++i)
        {
            auto [value, residue] = mul(getDigit(x, i), y);
            auto [summ, currentCarry] = add(residue, carry);
            temp.push_back(summ);
            carry = value + currentCarry;
        }
        return move(temp);
    } // }}}

    template<typename X>
    static void mulVectors(vector<X>& x, vector<X>& y) // {{{
    {
        vector<X> temp;
        for (int i = 0; i < SZ(y); ++i)
            addVectors(temp, mulVectorDigit<X>(x, y[i]), bigint::add, i);
        x = temp;
    } // }}}

    pair<bigint, bigint> divmod(bigint& x, bigint& y)
    {
        bigint zero = bigint(0);
        if (y == zero)
            throw "Division by zero!";
        int xs = x.sign;
        int ys = y.sign;
        x.sign = y.sign = 1;

        if (x < y)
        {
            x.sign = xs;
            return {zero, x};
        }

        bigint div, mod;
        div.a.clear();
        mod.a.clear();
        for (int i = SZ(a) - 1; i >= 0; --i)
        {
            mod.a.insert(mod.a.begin(), a[i]);
            mod.trimZeroes();
            T xxx = binSearch(T(0), T(B), [&](T m) { return y * bigint(m) > mod; }, T(1));
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
    }

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
        T value = T(0);
        T residue = T(0);
        T currentCarry = T(0);
        while (y)
        {
            if (y & 1)
            {
                auto [summ, carry] = add(residue, x);
                residue = summ;
                value += currentCarry + carry;
            }
            auto [summ, carry] = add(x, x);
            x = summ;
            currentCarry = currentCarry * 2 + carry;
            y >>= 1;
        }
        return {value, residue};
    }
    // }}}

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
    
    string toString() // {{{
    {
        bigint<unsigned long long, 10> temp(*this);
        stringstream os;
        if (sign == -1 && (a.size() != 1 || a[0]))
            os << '-';
        for (auto&& x : temp)
            os << x;
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

    bigint(string s)
    {
        bool ok = false;
        if (s[0] == '-')
            ok = true,
            s.erase(s.begin());
        bigint ten(10);

        for (char& c : s)
            *this *= ten,
            *this += bigint(c - 48);
        if (ok) sign = -1;
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
            addVectors(a, x.a, bigint::add),
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
            addVectors(a, x.a, bigint::sub);
            trimZeroes();
        }
        else
            *this += -x;
        return *this;
    } // }}}

    bigint& operator*=(bigint x) // {{{
    {
        sign *= x.sign;
        mulVectors(a, x.a);
        return *this;
    }
    // }}}

    bigint& operator/=(bigint x) // {{{
    {
        *this = divmod(*this, x).first;
        return *this;
    }
    // }}}

    bigint& operator%=(bigint x) // {{{
    {
        *this = divmod(*this, x).second;
        return *this;
    }
    // }}}

    // Binary operators {{{
    bigint operator+(const bigint &v)
    {
        bigint sum = *this;
        return sum += v;
    }

    bigint operator-(const bigint &v)
    {
        bigint sum = *this;
        return sum -= v;
    }

    bigint operator/(const bigint &v)
    {
        bigint div = *this;
        return div /= v;
    }

    bigint operator%(const bigint &v)
    {
        bigint mod = *this;
        return mod %= v;
    }

    bigint operator*(const bigint &v)
    {
        bigint prod = *this;
        return prod *= v;
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

    // Cast {{{
    template<typename T2, size_t B2>
    explicit operator bigint<T2, B2>() {
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

    void write()
    {
        for (auto&& x : *this)
            cout << x << " ";
        writeln();
    }
};

int main()
{
    bigint<long long> a, b;
    readln(a, b);
    bigint<unsigned char, 2> x(a), y(b);
    bigint<int> u(x), v(y);
    bigint<short, 229> c(u), d(v);
    writeln(c + d);
    writeln(c - d);
    writeln(c * d);
    writeln(c / d, c % d);
    return 0;
}
