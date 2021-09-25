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
//sparseTable
//0-indexed, [l, r)
template<typename T>
struct sparseTable
{
    int n;
    vector<vector<T>> st;
    vector<int> logs;
    typedef function<T (T, T)> F;
    F f;

    int highestBit(int x) const { return 31 - __builtin_clz(x); }

    sparseTable() {}

    sparseTable(vector<T>& a, F g)
    {
        n = a.size();
        f = g;

        logs.push_back(0);
        logs.push_back(0);
        FOR(i, 2, n + 1) logs.push_back(logs[i / 2] + 1);
        int L = logs.back() + 1;
        st.resize(L, vector<T>(n));
        fori(n)
            st[0][i] = a[i];
        FOR(k, 1, L)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = f(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    T get(int l, int r)
    {
        int len = highestBit(r - l);
        return f(st[len][l], st[len][r - (1 << len)]);
    }
};

//}}}

void run()
{
    ints(n, m, k, q);
    cerr << n << " " << m << " " << k << " " << q << endl;
    vector<string> s(n);
    readln(s);
    s.insert(s.begin(), string(m, '.'));
    s.pb(string(m, '.'));
    
    ll sum = 0;
    auto ss = [&]() {
        reverse(all(s));
        k = n - k + 1;
    };

    vector<vector<vector<int>>> below(2, vector<vector<int>>(n + 2, vector<int>(m, 0)));
    vector<vector<int>> temps(2, vector<int>(n + 2, 0));
    vector<vector<int>> answers(2, vector<int>(n + 2, m));

    auto calcBelow = [&](int order) {
        FOR(i, k + 1, s.size())
            forj(m)
                below[order][k + 1][j] += s[i][j] == 'X';
        ROF(i, k, 0)
        {
            temps[order][i] = k - i;
            forj(m)
            {
                below[order][i][j] = below[order][i + 1][j];
                if (s[i][j] == 'X')
                    temps[order][i]++,
                    below[order][i][j]++;
                else
                    temps[order][i] += below[order][i][j] >= (n - k + 1);
            }
            answers[order][i] = min(answers[order][i + 1], temps[order][i]);
        }
        ss();
    };

    calcBelow(0);
    calcBelow(1);

    auto get = [&](int r, int c) {
        int fill = s[r][c] == '.' ? 1 : -1;
        s[r][c] ^= 'X' ^ '.';

        auto calc = [&](int order) {
            int row = min(k, r);

            ROF(i, row, 0)
            {
                if (s[i][c] == '.')
                {
                    if (r == i)
                        temps[order][i]--;
                    else
                        temps[order][i] -= below[order][i][c] >= (n - k + 1);
                    below[order][i][c] += fill;
                    temps[order][i] += below[order][i][c] >= (n - k + 1);
                }
                else
                {
                    below[order][i][c] += fill;
                    if (r == i)
                        temps[order][i]++;
                }
                answers[order][i] = min({m, answers[order][i + 1], temps[order][i]});
            }
            ss();
            r = n - r + 1;
            return answers[order][0];
        };

        int ans = calc(0);
        int ans2 = calc(1);
        return min(ans, ans2);
    };
    fori(q)
    {
        if (i % 1000 == 0)
            cerr << i << "/" << q << endl;
        ints(r, c); --c;
        int ans = get(r, c);
        //writeln(s);
        //writeln(below[0]);
        //writeln("--------------");
        //writeln(below[1]);
        //writeln("--------------");
        //writeln(temps[0]);
        //writeln("--------------");
        //writeln(temps[1]);
        //writeln("--------------");
        //writeln(answers[0]);
        //writeln("--------------");
        //writeln(answers[1]);
        //writeln("--------------");
        //writeln(ans);
        sum += ans;
    }
    writeln(sum);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t);
    fori(t)
        cout << "Case #" << (i + 1) << ": ",
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
