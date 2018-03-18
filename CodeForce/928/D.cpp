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

vector<vector<int>> transitions = {vector<int>(52, -1)};
vector<vector<int>> count = {vector<int>(52, 0)};

vector<int> cc = {0};

int getSymbol(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 26;
    return -1;
}

int addTransition(int root, int x, bool updateCount = false)
{
    auto t = transitions[root][x];
    if (t == -1)
    {
        t = transitions.size();
        transitions.pb(vi(52, -1));
        count.pb(vi(52, 0));
        cc.pb(0);
    }
    if (updateCount)
        cc[root]++,
        count[root][x]++;
    transitions[root][x] = t;
    return t;
}

int get(string& word, int b, int e)
{
    if (b == e)
        return 0;
    int root = 0;
    bool newWord = false;
    bool failed = false;
    int ones = 0;
    for (int i = b; i < e; ++i)
    {
        int x = getSymbol(word[i]);
        if (transitions[root][x] == -1)
        {
            newWord = true;
            if (cc[root])
                failed = true;
        }
        if (count[root][x] == 1)
            ones++;
        root = addTransition(root, x);
    }
    int ans = cc[root] || failed ? 0 : max(0, ones - 2);
    //writeln(word.substr(b, e - b), ans);

    if (newWord || cc[root])
        for (int i = b, root1 = 0; i < e; ++i)
            root1 = addTransition(root1, getSymbol(word[i]), true);
    return ans;
}

void run()
{
    int ans = 0;
    string s;
    while (getline(cin, s))
    {
        s.pb('#');
        ans += s.size();
        int b = 0;
        while (b < int(s.size()) && getSymbol(s[b]) == -1) ++b;
        for (int j = b; j < int(s.size()); ++j)
            if (auto x = getSymbol(s[j]); x == -1)
            {
                ans -= get(s, b, j);
                b = j + 1;
            }
    }
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
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
