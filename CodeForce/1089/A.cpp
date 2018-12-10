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
    ints(a, b);
    vector<pii> scores = {{3, 0}, {3, 1}, {3, 2}, {2, 3}, {1, 3}, {0, 3}};
    for (auto& [f, s]: scores)
    {
        int cf = 0;
        int cs = 0;
        int n = f + s;
        vector<pii> score(n);
        if (s > f)
        {
            fori(f) score[i] = {25, 0}, cf += 25;
            fori(s) score[i + f] = {0, 25}, cs += 25;
        }
        else
        {
            fori(s) score[i] = {0, 25}, cs += 25;
            fori(f) score[i + s] = {25, 0}, cf += 25;
        }
        if (n == 5)
        {
            auto& [lf, ls] = score.back();
            if (lf) lf -= 10, cf -= 10;
            else ls -= 10, cs -= 10;
        }
        auto check = [&a, &b, &n](vector<pii> currScore, int cf, int cs, int index) {
            if (index < n)
            {
                if (currScore[index].first)
                    currScore[index].second = currScore[index].first - 2,
                    cs += currScore[index].second;
                else
                    currScore[index].first = currScore[index].second - 2,
                    cf += currScore[index].first;
                auto diff = max(min(a - cf, b - cs), 0);
                currScore[index].first += diff,
                currScore[index].second += diff,
                cf += diff,
                cs += diff;
            }

            fori(n)
                while (cf < a && currScore[i].first + 2 < currScore[i].second)
                    currScore[i].first++,
                    cf++;
            fori(n)
                while (cs < b && currScore[i].second + 2 < currScore[i].first)
                    currScore[i].second++,
                    cs++;
            //printf("%d  %d:%d\n", index, cf, cs);
            //fori(n)
                //printf("%d:%d%c", currScore[i].first, currScore[i].second, " \n"[i == n - 1]);

            if (cf == a && cs == b)
                return currScore;
            else
                return vector<pii>();
        };
        forj(n + 1)
            if (auto currScore = check(score, cf, cs, j); currScore.size())
            {
                printf("%d:%d\n", f, s);
                fori(n)
                    printf("%d:%d%c", currScore[i].first, currScore[i].second, " \n"[i == n - 1]);
                return;
            }
    }
    
    writeln("Impossible");
}

//{{{
int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    //ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    ints(t);
    fori(t)
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
