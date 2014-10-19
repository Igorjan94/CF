//template igorjan94 version from 05 June 2014
#include <bits/stdc++.h>
#include <iomanip>

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

string s, t;

int atoi(string &s, int &i)
{
    int temp = s[i++] - '0';
    while (s[i] - '0' <= 9 && s[i] - '0' >= 0)
        temp = temp * 10 + s[i++] - '0';
    i--;
    return temp;
}

int updateC(string &s, int i, int temp, int inb, bool b)
{
    int c1 = 0;
    if (s[i - 1] >= '0' && s[i - 1] <= '9')
        c1 = temp * (b ? inb : 1);
    return c1;
}

void parse(string s, int &x1, int &y1, int &c1)
{
    int temp = 1, inb = 1, sig = 1;
    bool b = false;
    for (int i = 0; i < s.size(); ++i)
        switch (s[i])
    {
        case '(' :
            b = true;
            inb = 1;
            break;
        case '=' :
            sig = -1;
        case ')' :
            c1 += updateC(s, i, temp, inb, b);
            b = false;
            temp = sig;
            inb = 1;
            break;

        case 'x' :
            x1 += temp * (b ? inb : 1);
            inb = 1;
            break;

        case 'y' :
            y1 += temp * (b ? inb : 1);
            inb = 1;
            break;

        case '-' :
            c1 += updateC(s, i, temp, inb, b);
            if (b)
                inb = -1;
            else
                temp = sig * -1;
//            (b ? inb : temp) = -1;
            break;

        case '+' :
            c1 += updateC(s, i, temp, inb, b);
            inb = 1;
            if (!b)
                temp = sig;
            break;

        default :
            (b ? inb : temp) *= atoi(s, i);
    }
}

void run()
{
    readln(s, t);
    s += ')';
    t += ')';
    int aa, bb, cc, dd, ee, ff;
    aa = bb = cc = dd = ee = ff = 0;
    parse(s, aa, bb, cc);
    parse(t, dd, ee, ff);
//    writeln(a, "x +", b, "y =", -c);
//    riteln(d, "x +", e, "y =", -f);
    double x, y;
    double a, b, c, d, e, f;
    a = aa;
    b = bb;
    c = cc;
    d = dd;
    e = ee;
    f = ff;
    y = f * a - c * d;
    y /= b * d - e * a;
    x = b * f - c * e;
    x /= a * e - b * d;
    cout << fixed;
    cout << setprecision(9) << x << "\n";
    cout << setprecision(9) << y << "\n";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
