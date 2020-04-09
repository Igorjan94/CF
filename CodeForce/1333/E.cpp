// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//}}}

void run()
{
    ints(n);
    if (n <= 2)
        return writeln(-1);
    if (n == 3)
    {
        vector<vector<int>> e = {{1, 2, 4}, {5, 3, 8}, {9, 6, 7}};
        return writeln(e);
        vector<int> a(9);
        iota(all(a), 1);
        do
        {
            int q = 0;
            int r = 0;
            auto get = [&](int i, int j) {
                return a[i * 3 + j];
            };
            vector<vector<bool>> rook(3, {false, false, false});
            vector<vector<bool>> queen(3, {false, false, false});
            auto getMin = [&](vector<vector<bool>>& used) {
                pii ans = {-1, -1};
                int mn = 100;
                fori(n)
                    forj(n)
                        if (!used[i][j] && mn > get(i, j))
                            mn = get(i, j),
                            ans = {i, j};
                return ans;
            };
            auto getRook = [&](vector<vector<bool>>& used, int x, int y) {
                int mn = 100;
                pii ans = {-1, -1};
                fori(n)
                    if (!used[x][i] && get(x, i) < mn)
                        mn = get(x, i), ans = {x, i};
                fori(n)
                    if (!used[i][y] && get(i, y) < mn)
                        mn = get(i, y), ans = {i, y};
                return ans;
            };
            auto getQueen = [&](vector<vector<bool>>& used, int x, int y) {
                int mn = 100;
                pii ans = {-1, -1};
                fori(n)
                    if (!used[x][i] && get(x, i) < mn)
                        mn = get(x, i), ans = {x, i};
                fori(n)
                    if (!used[i][y] && get(i, y) < mn)
                        mn = get(i, y), ans = {i, y};
                fori(n)
                    forj(n)
                        if (i - j == x - y)
                            if (!used[i][j] && get(i, j) < mn)
                                mn = get(i, j), ans = {i, j};
                fori(n)
                    forj(n)
                        if (i + j == x + y)
                            if (!used[i][j] && get(i, j) < mn)
                                mn = get(i, j), ans = {i, j};
                return ans;
            };
            while (true)
            {
                auto [i, j] = getMin(rook);
                if (i == -1)
                    break;
                rook[i][j] = true;
                r++;
                do
                {
                    auto [ni, nj] = getRook(rook, i, j);
                    if (ni == -1)
                        break;
                    i = ni;
                    j = nj;
                    rook[i][j] = true;
                }
                while (true);
            }
            writeln(a);
            while (true)
            {
                auto [i, j] = getMin(queen);
                if (i == -1)
                    break;
                queen[i][j] = true;
                q++;
                do
                {
                    auto [ni, nj] = getQueen(queen, i, j);
                    if (ni == -1)
                        break;
                    i = ni;
                    j = nj;
                    queen[i][j] = true;
                    writeln(queen);
                }
                while (true);
            }

            if (q > r)
            {
                writeln(q, r);
                writeln(a);
                return;
            }
        }
        while (next_permutation(all(a)));
        return writeln(a);
    }
    vector<vector<int>> a = {
        {4, 3, 6, 12},
        {7, 5, 9, 15},
        {14, 1, 11, 10},
        {13, 8, 16, 2}
    };
    if (n == 4)
        return writeln(a);
    vector<vector<int>> b(n, vector<int>(n));
    int c = 1;
    forn(q, n - 4)
    {
        if ((n - q) % 2 == 1)
        {
            ROF(j, n - 1, q)
                b[q][j] = c++;
            FOR(i, q + 1, n)
                b[i][q] = c++;
        }
        else
        {
            ROF(j, n - 1, q)
                b[j][q] = c++;
            FOR(i, q + 1, n)
                b[q][i] = c++;
        }

        if (q == n - 5)
            swap(b[n - 1][q], b[n - 2][q]);
    }
    fori(4)
        forj(4)
            b[i + n - 4][j + n - 4] = a[i][j] + (n * n - 16);

    writeln(b);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
