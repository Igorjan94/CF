// Igorjan94, template version from 13 October 2017. C++17 version {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

typedef vector<long long> vll;
typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) a.begin(), a.end()
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline
                    
const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();
                    
void writeln(){cout<<"\n";}ttti void print(T a);ttti void priws(T a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H h,T...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}
///-------------------------------------------------------------------------------------------------------------------------------------

struct sign
{
    int d, a, b;
    sign() {}
};

ostream& operator<<(ostream& os, sign s) { return os << s.d << " " << s.a << " " << s.b; }
istream& operator>>(istream& is, sign& s) { return is >> s.d >> s.a >> s.b; }

pii run()
{
    map<int, int> m;
    ints(n);
    vector<sign> a(n);
    readln(a);
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
        {
            vector<int> pr, pl;
            for (int k = i; k <= j; ++k)
                pr.pb(a[k].d + a[k].a),
                pl.pb(a[k].d - a[k].b);
            for (auto& r : pr)
                for (auto& l : pl)
                {
                    bool found = true;
                    for (int k = i; k <= j && found; ++k)
                        found &= a[k].d + a[k].a == r || a[k].d - a[k].b == l;
                    if (found)
                    {
                        m[j - i + 1]++;
                        goto ok;
                    }
                }
            ok:;
        }
    return *m.rbegin();
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t);
    fori(t)
    {
        auto temp = run();
        cout << "Case #" << (i + 1) << ": " << temp.first << " " << temp.second;
        if (i != t - 1) cout << "\n";
    }
    return 0;
}

#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
