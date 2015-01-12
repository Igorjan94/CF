//Igorjan94, template version from 11 January 2015
#include <bits/stdc++.h>

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
#define INF 1000000007

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T &a);
ttti void priws(T a);
ttti void print(T a);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){priws(*f);for(auto i=++f;i!=s;++i)print(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

#define ints(args...) int args; readln(args)
#define lll (args...) ll  args; readln(args)
#define FORI(n) for (unsigned i = 0; i < n; ++i)
#define FORJ(n) for (unsigned j = 0; j < n; ++j)

template<class Type> Type powbin(Type a, int n);

template <typename T> class Matrix
{
public:
    std::vector<std::vector<T> > a;
    unsigned n;
    unsigned m;

    Matrix(unsigned n, unsigned m, const T& initial);
    virtual ~Matrix();

    Matrix<T> operator^(int deg);
    Matrix<T> operator*(const Matrix<T>& rhs);
    Matrix<T>& operator*=(const Matrix<T>& rhs);
    std::vector<T>& operator[](int i);
};


template<typename T>
std::vector<T>& Matrix<T>::operator[](int i)
{
    return a[i];
}

template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned m, const T& initial)
{
    this->n = n;
    this->m = m;
    a.resize(n);
    FORI(n)
        a[i].resize(m, initial);
}

template<typename T>
Matrix<T>::~Matrix() {}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
    unsigned nn = this->n;
    unsigned mm = rhs.m;
    Matrix result(nn, mm, (T) 0);
    FORI(nn)
        FORJ(mm)
            for (unsigned k = 0; k < this->m; k++)
                (result.a[i][j] += this->a[i][k] * rhs.a[k][j]) %= 6;
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
Matrix<T> Matrix<T>::operator^(int i)
{
    Matrix temp = *this;
    temp = powbin(temp, i);
    return temp;
}

template<class Type>
Type powbin(Type a, int n)
{
    Type result = a;
    --n;
    while (n)
    {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}

///-------------------------------------------------------------------------------------------------------------------------------------

bool run()
{ 
    ints(n, m);
    if (n + m == 0)
        return false;
    Matrix<ll> A(n, m, 0);
    Matrix<ll> B(m, n, 0);
    readln(A.a, B.a);
    Matrix<ll> C = A * ((B * A) ^ (n * n - 1)) * B;
    ll ans = 0;
    fori(n)
        forj(n)
            ans += C[i][j];
    writeln(ans);
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    while (run());
    return 0;
}























#define a _a
#define n _n
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){os<<a[0];for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
