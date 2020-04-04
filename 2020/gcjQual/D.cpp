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
#define     SZ(a)    int(a.size())

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

void run(int n)
{
    auto ask = [&](int i) {
        writeln(i + 1);
        cout.flush();
        ints(x);
        cerr << "Asking " << i + 1 << ", got " << x << endl;
        return x;
    };
    string answer(n, '!');

    set<int> notAsked;
    fori(n / 2) notAsked.insert(i);

    vector<vector<int>> d(2, vector<int>(2, -1));
    for (int request = 0; !notAsked.empty(); request += 2)
    {
        cerr << answer << " Request " << request << endl;
        if (request % 10 == 0)
        {
            bool flipped = false;
            bool reversed = false;
            auto get = [&](int i, int j, int need) {
                request++;
                int x = d[i][j];
                int q = ask(x);
                return q != need;
            };
            if (d[0][0] != -1)
                flipped = get(0, 0, 0);
            else if (d[1][1] != -1)
                flipped = get(1, 1, 1);
            if (flipped)
            {
                for (char& c: answer)
                    c ^= 1;
                swap(d[0][0], d[1][1]);
                swap(d[0][1], d[1][0]);
            }
            if (d[0][1] != -1)
                reversed = get(0, 1, 0);
            else if (d[1][0] != -1)
                reversed = get(1, 0, 1);
            if (reversed)
            {
                reverse(all(answer));
                swap(d[0][1], d[1][0]);
            }
            if (request % 2 == 1)
                request++,
                ask(0);
            cerr << flipped << " " << reversed << endl;
            cerr << answer << endl;
        }
        int x;
        do
            x = rand() % (n / 2);
        while (!notAsked.count(x));
        int q = ask(x);
        int w = ask(n - x - 1);
        answer[x] = q + '0';
        answer[n - x - 1] = w + '0';
        d[q][w] = x;
        notAsked.erase(x);
        notAsked.erase(n - x - 1);
    }

    writeln(answer);
    string verdict;
    readln(verdict);
    if (verdict == "Y")
        return;
    else
        exit(29);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t, b);
    fori(t) run(b);
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
