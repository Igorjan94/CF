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

static const int N = 1002001;
void run()
{
    int n, m, t;
    scanf("%d%d%d", &n, &m, &t);
    bitset<N> x;
    auto get = [&](const bitset<N>& x, int i, int j) {
        return x[i * m + j];
    };
    auto set = [&](bitset<N>& x, int i, int j, bool y) {
        if (y)
            x.set(i * m + j);
    };
    fori(n)
    {
        string s(m, '0');
        scanf("%s", s.data());
        forj(m)
            set(x, i, j, s[j] - '0');
    }
    unordered_map<bitset<N>, int> mp = {{x, 0}};
	vector<bitset<N>> v = {x};
    v.reserve(128);
    vector<pii> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int cycle = -1;
    int start = -1;
    int index = 1;
	while (true)
	{
		bitset<N> y;
		fori(n)
			forj(m)
			{
                int other = 0;
                bool color = get(x, i, j);
                for (const auto& [dx, dy]: d)
                    if (int u = i + dx, v = j + dy; u >= 0 && u < n && v >= 0 && v < m && other == 0)
                        other += get(x, u, v) == color;
                if (other == 0)
                    set(y, i, j, color);
                else
                    set(y, i, j, !color);
			}
        if (false)
        {
            writeln(index);
            fori(n)
            {
                forj(m)
                    priws(get(y, i, j));
                writeln();
            }
            writeln();
        }
        v.pb(y);
        if (auto it = mp.find(y); it != mp.end())
        {
            cycle = index - it->second;
            start = it->second;
            break;
        }
        mp[y] = index++;
        x = y;
	}
    forn(q, t)
    {
        ll p;
        ll index;
        int i, j;
        scanf("%d%d%lld", &i, &j, &p);
        if (p <= start)
            index = p;
        else
            index = (p - start) % cycle + start;
        //writeln(index);
        printf("%d\n", get(v[index], --i, --j));
    }
}

//{{{
int main()
{
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
