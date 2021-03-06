//Igorjan94, template version from 16 February 2015
#include <bits/stdc++.h>
/*
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_cxx;
using namespace __gnu_pbds;
typedef tree<int, int/null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedMap;
*/

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define     fst      first
#define     snd      second
#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      eb      emplace_back
#define      vs      vector<string>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int>>
#define     pll      pair<long long, long long>
#define   elohw(a)   a.rbegin(), a.rend()
#define   whole(a)   a.begin(), a.end()
#define    next      _next
#define    prev      _prev

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())
#define wr(args...)  err(split(#args,',').begin(),args)

#define FILENAME "input"
#define INF 1000000009

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T&);
ttti void priws(T);
ttti void print(T);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

#define  ints(args...) int args; readln(args)
#define   lls(args...)  ll args; readln(args)
#define vints(args...)  vi args; readln(args)

///-------------------------------------------------------------------------------------------------------------------------------------

struct node
{
    int x, y, v;

    node(int x, int y, int v)
    {
        this->x = x;
        this->y = y;
        this->v = v;
    }

    bool operator<(node const& b) const
    {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }

    node(){}

};

bool cmp(node const& a, node const& b)
{
    return a.v < b.v;
}

int x, y, v;
map<pii, int> a;
set<node, bool(*)(node const&, node const&)> values(cmp);

bool check(pii const& p)
{
#define x first
#define y second
    for (int i = p.x - 1; i < p.x + 2; i++)
        if (a.find({i, p.y + 1}) != a.end())
        {
            int ok = 0;
            for (int j = i - 1; j < i + 2; j++)
                if (a.find({j, p.y}) != a.end())
                    ok++;
            if (ok == 1)
                return false;
        }
#undef x
#undef y
    return true;
}

void run()
{
    ints(n);
    fori(n)
        readln(x, y),
        a[{x, y}] = i;
    for (auto p : a)
        if (check(p.first))
            values.insert(node(p.first.first, p.first.second, p.second));
    ll answer = 0;
    fori(n)
    {
        if (values.size() == 0)
        {
            writeln("FUUUUUU");
            return;
        }
        auto temp = i & 1 ? *values.begin() : *values.rbegin();
        answer = (answer * n + temp.v) % INF;
        values.erase(temp);
        a.erase({temp.x, temp.y});
        auto it = a.begin();
        for (int j = temp.x - 1; j < temp.x + 2; j++)
            if ((it = a.find({j, temp.y - 1})) != a.end())
                if (check({j, temp.y - 1}))
                    values.insert(node(j, temp.y - 1, it->second));
        for (int j = temp.x - 2; j < temp.x + 3; j++)
            if ((it = a.find({j, temp.y})) != a.end())
                if (!check({j, temp.y}))
                    values.erase(node(j, temp.y, it->second));
    }
    writeln(answer);
}

int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}























#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
