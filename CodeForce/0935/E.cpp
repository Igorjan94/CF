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
                    
void writeln(){cout<<endl;}ttti void print(T a);ttti void priws(T a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H h,T...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}
///-------------------------------------------------------------------------------------------------------------------------------------
struct state;
vector<state> states;
string s;
int p, m;

#define mn first
#define mx second

struct state
{
    state() {}
    int ops = 0;
    int value = 0;
    int left;
    int right;
    int parent;
    int index;

    state(int index, int parent) : parent(parent), index(index) {}

    map<pii, pii> get()
    {
        map<pii, pii> ans;
        if (value)
            ans[{0, 0}] = {value, value};
        else
        {
            auto L = states[left].get();
            auto R = states[right].get();
            for (auto& [kx, x] : L)
                for (auto& [ky, y] : R) 
                {
                    int pp = kx.first + ky.first;
                    int mm = kx.second + ky.second;
                    if (pp + 1 <= p)
                    {
                        if (ans.find({pp + 1, mm}) == ans.end())
                            ans[{pp + 1, mm}] = {x.mn + y.mn, x.mx + y.mx};
                        else
                            ans[{pp + 1, mm}].first = min(ans[{pp + 1, mm}].first, x.mn + y.mn),
                            ans[{pp + 1, mm}].second = max(ans[{pp + 1, mm}].second, x.mx + y.mx);
                    }
                    if (mm + 1 <= m)
                    {
                        if (ans.find({pp, mm + 1}) == ans.end())
                            ans[{pp, mm + 1}] = {x.mn - y.mx, x.mx - y.mn};
                        else
                            ans[{pp, mm + 1}].first = min(ans[{pp, mm + 1}].first, x.mn - y.mx),
                            ans[{pp, mm + 1}].second = max(ans[{pp, mm + 1}].second, x.mx - y.mn);
                    }
                }
        }
        return ans;
    }
};

void run()
{
    readln(s, p, m);
    state curr(0, -1);
    states.pb(curr);
    for (char c : s)
        if (c == '(')
        {
            state l(states.size(), curr.index);
            states.pb(l);
            state r(states.size(), curr.index);
            states.pb(r);
            states[curr.index].left = l.index;
            states[curr.index].right = r.index;
            curr = l;
        }
        else if (c == '?')
        {
            states[curr.parent].ops++;
            curr = states[states[curr.parent].right];
        }
        else if (c == ')')
            curr = states[curr.parent];
        else if (c >= '0' && c <= '9')
            states[curr.index].value = c - '0';
    writeln(states[0].get()[{p, m}].mx);
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
ostream&operator<<(ostream&os,state&a){return a.value ? os << a.value : (os << "(" << states[a.left] << "?" << states[a.right] << ")");}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
