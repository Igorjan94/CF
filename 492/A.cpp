//template igorjan94 version from 24 November 2014
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
#define fst first
#define cnd second

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

template <class Head, class... Tail> inline void writeln(Head head, Tail... tail);
template <class Head, class... Tail> inline void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> inline void readln(Head& head, Tail&... tail);
template <class Head, class... Tail> inline void read(Head& head, Tail&... tail);
template <class Head, class... Tail> inline void print(Head& head, Tail&... tail);
template <class Type1, class Type2>  inline void print(pair<Type1, Type2>& p);
template <class Type1, class Type2>  inline void print_no_space(pair<Type1, Type2>& p);
template <class Head, class... Tail> inline void print_no_space(Head& head, Tail&... tail);
void inline writeln(){printf("\n");}void inline writeln2(){printf("\n");}void inline readln(){}

///----------------------------------------------------------------------------------------------------------------------------

void run()
{   
    int n;
    readln(n);
    int count = 0;
    int i = 1;
    for (; count + i * (i + 1) / 2 <= n; count += i * (i + 1) / 2, i++);
    writeln(i - 1);
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

























inline void print(double a){printf(" " DOUBLEFORMAT,a);}
inline void print(int a){printf(" %d",a);}
inline void print(const char* a){printf(" %s",a);}
inline void print(string a){printf(" %s",a.c_str());}
inline void print(long long a){printf(" %lld",a);}
inline void print(unsigned long a){printf(" %ld",a);}
inline void print(unsigned int a){printf(" %d",a);}
inline void print(char a){printf(" %c",a);}
inline void print_no_space(double a){printf(DOUBLEFORMAT, a);}
inline void print_no_space(int a){printf("%d", a);}
inline void print_no_space(const char* a){printf("%s", a);}
inline void print_no_space(string a){printf("%s", a.c_str());}
inline void print_no_space(long long a){printf("%lld", a);}
inline void print_no_space(unsigned long a){printf("%ld", a);}
inline void print_no_space(unsigned int a){printf("%d", a);}
inline void print_no_space(char a){printf("%c", a);}

template<class Type> inline void print(vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type> inline void print(vector<vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type> inline void print_no_space(vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type> inline void print_no_space(vector<vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}

template<class Type1, class Type2> inline void print_no_space(pair<Type1, Type2>&a){print_no_space(a.first); writeln2(a.second);}
template<class Type1, class Type2> inline void print(pair<Type1, Type2>& a)        {print_no_space(a.first); writeln2(a.second);}

template <class Head, class... Tail> inline void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail> inline void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

inline void read(double &a){scanf("%lf",&a);}
inline void read(int &a){scanf("%d",&a);}
inline void read(string &a){cin>>a;}
inline void read(long long &a){scanf("%lld",&a);}
inline void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2> inline void read(pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type> inline void read(vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail> inline void readln(Head& head,Tail&... tail){read(head);readln(tail...);}
