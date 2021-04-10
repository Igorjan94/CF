// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//}}}

void run()
{
    ints(n, q);
    auto stringify = [&](ll i) {
        string s;
        forj(q)
            s += ((1ll << j) & i) != 0 ? 'T' : 'F';
        return s;
    };
    auto maskify = [&](const string& s) {
        ll mask = 0;
        forj(q)
            if (s[j] == 'T')
                mask ^= 1ll << j;
        return mask;
    };

    auto invert = [&](const int& mask) {
        return mask ^ ((1ll << q) - 1);
    };

    auto getResult = [&](const int& answers, const int& mask) {
        return __builtin_popcount(invert(answers ^ mask));
    };

    vector<pair<ll, int>> s;
    fori(n)
    {
        string ss;
        int x;
        readln(ss, x);
        s.pb({maskify(ss), x});
    }
    for (auto& [answers, correct] : s)
        if (correct < q - correct)
        {
            correct = q - correct;
            answers = invert(answers);
        }
    if (n == 1)
    {
        cout << stringify(s[0].first) << " " << s[0].second << "/1" << endl;
    }
    else
    {
        vector<int> masks;
        fori(1 << q)
        {
            int ok = 0;
            for (const auto& [answers, correct]: s)
                ok += correct == getResult(answers, i);
            if (ok == 2)
                masks.pb(i);
        }

        int ms = 0;
        int answer = 0;
        fori(1 << q)
        {
            int cur = 0;
            for (int mask: masks)
                cur += getResult(i, mask);
            if (cur > ms)
                ms = cur,
                answer = i;
        }
        int g = gcd(ms, SZ(masks));
        cout << stringify(answer) << " " << ms / g << "/" << SZ(masks) / g << endl;
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t); fori(t) cout << "Case #" << (i + 1) << ": ", run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
