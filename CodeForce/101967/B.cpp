// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
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
#define whole(a) begin(a), end(a)
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

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

void run()
{
    ints(n, m, k);
    vector<vector<int>> likes(n), dislikes(n), whoLikes(m + 1), whoDislikes(m + 1);
    vector<char> used(m + 1, 0);
    vector<int> diff;

    fori(k)
    {
        ints(a, b); --a;
        if (b > 0)
            likes[a].pb(b),
            whoLikes[b].pb(a);
        else
            dislikes[a].pb(-b),
            whoDislikes[-b].pb(a);
    }

    auto start = [&](int u, int p) {
        diff.clear();
        function<bool(int, int)> dfs = [&](int u, int p) {
            if (used[u] + p == 3)
                return false;
            if (used[u])
                return true;
            used[u] = p;
            diff.emplace_back(u);
            if (used[u] == 1)
                for (int& h: whoDislikes[u])
                {
                    for (int& s: likes[h]) if (!dfs(s, 1)) return false;
                    for (int& s: dislikes[h]) if (s != u && !dfs(s, 2)) return false;
                }
            if (used[u] == 2)
                for (int& h: whoLikes[u])
                {
                    for (int& s: likes[h]) if (s != u && !dfs(s, 1)) return false;
                    for (int& s: dislikes[h]) if (!dfs(s, 2)) return false;
                }
            return true;
        };
        return dfs(u, p);
    };

    fori1(m + 1)
        if (!used[i])
            if (!start(i, 1))
            {
                for (auto& u: diff) used[u] = 0;
                if (!start(i, 2))
                {
                    writeln(-1);
                    return;
                }
            }
    vector<int> ans;
    fori1(m + 1)
        if (used[i] == 1)
            ans.pb(i);
    writeln(ans.size());
    writeln(ans);
}

//{{{
int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
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
ttti void print(T&& a){cout<<" "<<a;}
ttti void priws(T&& a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
