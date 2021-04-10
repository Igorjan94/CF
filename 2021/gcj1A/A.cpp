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

bool cmp(const string& s, const string& t)
{
    if (s.size() != t.size())
        return s.size() < t.size();
    fori(SZ(s))
        if (s[i] != t[i])
            return s[i] < t[i];
    return false;
}

int run()
{
    ints(n);
    vector<string> a(n);
    readln(a);
    int ans = 0;
    fori1(n)
        if (!cmp(a[i - 1], a[i]))
        {
            int l = SZ(a[i]);
            while (SZ(a[i]) < SZ(a[i - 1]))
                a[i].pb('0'), ans++;
            if (cmp(a[i - 1], a[i]))
                continue;
            bool fail = false;
            forj(l)
                if (a[i][j] < a[i - 1][j])
                {
                    fail = true;
                    ans++;
                    a[i].pb('0');
                    break;
                }
            if (!fail)
            {
                int last = l - 1;
                FOR(j, l, SZ(a[i - 1]))
                {
                    a[i][j] = a[i - 1][j];
                    if (a[i - 1][j] != '9')
                        last = j;
                }
                if (last >= l)
                {
                    a[i][last]++;
                    FOR(j, last + 1, SZ(a[i - 1]))
                        a[i][j] = '0';
                    fail = true;
                }
            }
            if (!fail)
            {
                for (int j = l; j < SZ(a[i - 1]); ++j)
                    a[i][j] = '0';
                a[i].pb('0');
                ans++;
            }
        }
    return ans;
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t); fori(t) cout << "Case #" << (i + 1) << ": " << run() << endl;
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
