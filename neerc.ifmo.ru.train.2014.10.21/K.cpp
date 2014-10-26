//template igorjan94 version from 05 June 2014
#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define forn1(i, n) for (int i = 1; i < n; ++i)
#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define fori(n) for (int i = 0; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj1(n) for (int j = 1; j < n; ++j)
#define vi vector<int>
#define vvi vector<vector<int> >
#define vll vector<long long>
#define pii pair<int, int>
#define whole(a) a.begin(), a.end()

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "kitchen"
#define INF 1000000007
#define DOUBLEFORMAT "%.14f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k;
double w, h, x, y;
double edges[100][100];
double dp[18][(1 << 18) + 1];

double dst(double x, double y, double a, double b)
{
    return sqrt((x - a) * (x - a) + (y - b) * (y - b));
}
#define fst first
#define snd second

void run()
{
    readln(w, h);
    readln(n);
    vector<pair<double, double> > a(n);
    readln(a);
    a.pb({0, 0});
    readln(x, y);
    edges[n][n] = INF;
    double w1, w2, h1, h2, x1, x2, y1, y2, t1, t2, r1, r2;
    fori(n)
        FOR(j, i, n)
            {
                w1 = a[i].fst;
                h1 = a[i].snd;
                w2 = a[j].fst;
                h2 = a[j].snd;
                x1 = (w2 * h1 + w1 * h2) / (h1 + h2);
                t1 = dst(x1, 0, w1, h1) + dst(x1, 0, w2, h2);
                x2 = (w2 * (- h1 + h) + w1 * (- h2 + h)) / (- h1 + 2 * h - h2);
                t2 = dst(x2, h, w1, h1) + dst(x2, h, w2, h2);
                y1 = (w2 * h1 + w1 * h2) / (w1 + w2);
                r1 = dst(0, y1, w1, h1) + dst(0, y1, w2, h2);
                y2 = ((- w2 + w) * h1 + (- w1 + w) * h2) / (- w1 + 2 * w - w2);
                r2 = dst(w, y2, w1, h1) + dst(w, y2, w2, h2);
                edges[i + 1][j + 1] = edges[j + 1][i + 1] = min(min(t1, t2), min(r1, r2));
            }
//    n = n + 2;
    fori(n)
        forj(1 << n)
            dp[i][j] = INF;

    fori(n)
        dp[i][1 << i] = edges[i][i] / 2;
    for (int mask = 0; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++)
            if ((mask & (1 << i)))
                for (int j = 0; j < n; j++)
                     if ((mask & (1 << j)))
                        dp[i][mask] = min(dp[i][mask], dp[j][mask ^ (1 << i)] + edges[j + 1][i + 1]);
    double res = INF;
    fori(n)
        res = min(res, dp[i][(1 << n) - 1] + dst(x, y, a[i].fst, a[i].snd));
    writeln(res);
}

int main()
{
    freopen(FILENAME".in", "r", stdin);
    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

























void print(double a){printf(" " DOUBLEFORMAT,a);}
void print(int a){printf(" %d",a);}
void print(string a){printf(" %s",a.c_str());}
void print(long long a){printf(" %lld",a);}
void print(unsigned long a){printf(" %ld",a);}
void print(unsigned int a){printf(" %d",a);}
void print(char a){printf(" %c",a);}
void print_no_space(double a){printf(DOUBLEFORMAT, a);}
void print_no_space(int a){printf("%d", a);}
void print_no_space(string a){printf("%s", a.c_str());}
void print_no_space(long long a){printf("%lld", a);}
void print_no_space(unsigned long a){printf("%ld", a);}
void print_no_space(unsigned int a){printf("%d", a);}
void print_no_space(char a){printf("%c", a);}

template<class Type>
void print_no_space(vector<Type>& a);
template<class Type>
void print(vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}

template<class Type>
void print_no_space(vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type>
void print_no_space(vector<vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}
template<class Type1, class Type2>
void print_no_space(pair<Type1, Type2>&a){print_no_space(a.first);print(a.second);}
template <class Head, class... Tail>
void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

void read(double &a){scanf("%lf",&a);}
void read(int &a){scanf("%d",&a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld",&a);}
void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2>
void read(pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type>
void read(vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail>
void readln(Head& head,Tail&... tail){read(head);readln(tail...);}
