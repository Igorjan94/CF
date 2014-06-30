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

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k;
int table[6][6];
int got[6][6];

int f(char c)
{
    switch(c)
    {
        case 'R': return 0;
        case 'G': return 1;
        case 'B': return 2;
        case 'W': return 3;
        case 'Y': return 4;
        return 5;
    }
}

void run()
{
    readln(n);
    char c, cc, d;
    readln(cc);
    fori(n)
        readln(c, d, cc),
        table[f(c)][d - '1'] = 1;
    int count = 0;
    set<int> color, ma;
    fori(5)
        forj(5)
            if (table[i][j])
                count++,
                color.insert(i),
                ma.insert(j);
    if (count == 1)
    {
        writeln(0);
        return;
    }
    if (count == 2)
    {
        writeln(1);
        return;
    }
    if (color.size() == 1)
    {
        writeln(ma.size() - 1);
        return;
    }
    if (ma.size() == 1)
    {
        writeln(color.size() - 1);
        return;
    }
    vi permut;
    m = 10;
    fori(m)
        permut.pb(i);
    int mn = INF;
    while (next_permutation(whole(permut)))
    {
        fori(5)
            forj(5)
                got[i][j] = 0;
        forn(q, m)
        {
            int temp = permut[q];
            if (temp >= m / 2)
                forj(5)
                    got[temp - m / 2][j]++;
            else
                fori(5)
                    got[i][temp]++;
            int cur = 0;
            int flag = 0;
            fori(5)
            {
                int currow = 0;
                forj(5)
                    if (table[i][j])
                    {
                        if (got[i][j] == 2)
                            cur++;
                        else
                            if (got[i][j] == 1)
                                currow++,
                                cur++;
                    }
                if (currow >= 2)
                {
                    flag = 1;
                    break;
                }
            }
            if (cur < count - 1)
                continue;
            forj(5)
            {
                int curcol = 0;
                fori(5)
                    if (table[i][j])
                        if (got[i][j] == 1)
                            curcol++;
                if (curcol >= 2)
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                mn = min(mn, q + 1);
                break;
            }
        }
    }
    writeln(mn);
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
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
