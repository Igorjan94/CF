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

#define FILENAME "ref"
#define INF 1000000007
#define DOUBLEFORMAT "%.4f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------

template <typename T> class Matrix
{
public:
    std::vector<std::vector<T> > a;
    unsigned n;
    unsigned m;

    Matrix(unsigned n, unsigned m, const T& initial);
    Matrix(std::vector<std::vector<T> >& rhs);
    Matrix<T>& operator*=(const Matrix<T>& rhs);
    Matrix<T> operator*(const Matrix<T>& rhs);
};

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> >& rhs)
{
    this->n = rhs.size();
    this->m = rhs[0].size();
    this->a = rhs;
}

template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned m, const T& initial)
{
    this->n = n;
    this->m = m;
    a.resize(n);
    fori(n)
        a[i].resize(m, initial);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
    unsigned n = this->n;
    unsigned m = rhs.m;
    Matrix result(n, m, (T) 0);
    fori(n)
        forj(m)
            for (unsigned k = 0; k < this->m; k++)
                result.a[i][j] += this->a[i][k] * rhs.a[k][j];
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs)
{
    Matrix result = (*this) * rhs;
    (*this) = result;
    return *this;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& a, const Matrix<T>& rhs)
{
    std::vector<T> result(rhs.m, (T) 0);
    for (int i = 0; i < rhs.m; ++i)
        for (int j = 0; j < a.size(); ++j)
            result[i] += a[j] * rhs.a[j][i];
    return result;
}

int n, m;

void run()
{
    readln(m);
    int x1, x2, x3, y1, y2, y3, z1, z2, z3, a, b, c, d, e, f, nx, ny, nz, nn, D, coef = 1.;
    vector<vector<int> > ddd = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    Matrix<int> mtrx(ddd), temp(ddd);
    fori(m)
        readln(x1, y1, z1, x2, y2, z2, x3, y3, z3),
        a = x2 - x1, 
        b = y2 - y1, 
        c = z2 - z1, 
        d = x3 - x1, 
        e = y3 - y1, 
        f = z3 - z1,
        nx = b * f - c * e,
        ny = c * d - a * f,
        nz = a * e - b * d,
        nn = nx * nx + ny * ny + nz * nz,
        D = -(nx * x1 + ny * y1 + nz * z1),
        coef *= nn,
        temp.a ={{-2 * nx * nx + nn, -2 * nx * ny, -2 * nx * nz, 0 }, 
                 {-2 * ny * nx, -2 * ny * ny + nn, -2 * ny * nz, 0 }, 
                 {-2 * nz * nx, -2 * nz * ny, -2 * nz * nz + nn, 0 }, 
                 {-2 * nx * D , -2 * ny * D , -2 * nz * D      , nn}},
        mtrx *= temp;
    readln(n);
    vector<int> v(4);
    double x, y, z;
    fori(n)
        readln(v[0], v[1], v[2]),
        v[3] = 1,
        v = v * mtrx,
        x = v[0],
        y = v[1],
        z = v[2],
        writeln(x / coef, y / coef, z / coef);
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
