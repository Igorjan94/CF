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

auto manaker(const string& s)
{
    int n = SZ(s);
    vector<vector<int>> p(2,vector<int>(n,0));
    for(int z=0,l=0,r=0;z<2;z++,l=0,r=0)
        for(int i=0;i<n;i++)
        {
            if(i<r) p[z][i]=min(r-i+!z,p[z][l+r-i+!z]);
            int L=i-p[z][i], R=i+p[z][i]-!z;
            while(L-1>=0 && R+1<n && s[L-1]==s[R+1]) p[z][i]++,L--,R++;
            if(R>r) l=L,r=R;
        }
    return p;
}

void run()
{
    string s;
    readln(s);
    auto get = [](const string& s) -> string {
        int n = SZ(s);
        auto p = manaker(s);
        vector<set<int>> forward(n);
        int l = 0;
        int r = n;
        int mx = 0;
        fori(n)
        {
            if (int len = p[0][i]; len)
                forward[i - len].insert(-i - len + 1);
            if (int len = p[1][i]; len)
                forward[i - len].insert(-i - len);
        }
        int i = -1;
        int j = n;
        do
        {
            int ci = i;
            auto it = forward[i + 1].upper_bound(-j);
            if (it != forward[i + 1].end())
                ci = -*it;
            else if (ci + 1 < j)
                ci++;
            //writeln(i, j, s.substr(0, ci + 1) + s.substr(j));
            if (int cur = ci + (n - j); cur > mx)
                mx = cur,
                l = ci,
                r = j;
            ++i;
            --j;
        }
        while (i < j && s[i] == s[j]);
        return s.substr(0, l + 1) + s.substr(r);
    };
    string first = get(s);
    reverse(all(s));
    string second = get(s);
    if (SZ(first) >= SZ(second))
        writeln(first);
    else
        writeln(second);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t); fori(t) run();
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
