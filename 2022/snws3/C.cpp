// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

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
//prefixFunction
vector<int> z_function (string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}
//}}}

int bf(string s)
{
    int n = s.size();
    int ans = 0;
    fori1(n)
    {
        int temp = 0;
        int first = stoi(s.substr(0, i));
        int second = stoi(s.substr(i));
        int sum = first + second;
        while (sum && sum % 10 == 0)
            temp++,
            sum /= 10;
        ans = max(ans, temp);
    }

    return ans;
}

void run()
{

    auto trim = [&](vector<int>& z, int skip, int n) {
        vector<int> ans(n, 0);
        fori(n)
            if (skip + i < SZ(z))
                ans[i] = z[skip + i];

        reverse(all(ans));
        z = ans;
    };
    auto get = [&](string s) {
        int n = s.size();
        int ans = 0;
        if (s[n - 1] + s[n - 2] == 10 + '0' + '0')
        {
            ++ans;
            ROF(i, n - 3, 0)
                if (s[i] == '9')
                    ++ans;
                else
                    break;
        }
        return ans;
    };
    string s;
    while (cin >> s)
    {
        int last = get(s);
        //int forces = bf(s);
        int zeroes = 0;
        while (s.size() && s.back() == '0') zeroes++, s.pop_back();
        if (s.size() == 1)
        {
            writeln(zeroes - 1);
            continue;
        }

        reverse(all(s));
        int n = s.size();
        string t = s + "@" + s;
        t.erase(t.begin());
        fori(n - 1) t[i] = '9' - t[i] + '0';
        fori(n) t.pb('0');
        //writeln(t);

        string q(n, '0');
        q += "@" + s;
        auto how_much = z_function(q);
        trim(how_much, n + 1, n);

        auto p = z_function(t);
        trim(p, n + 1, n);
        //writeln(p);
        //writeln(how_much);

        reverse(all(s));

        int mxz = *max_element(all(how_much));
        int ans = max(0, zeroes - (zeroes > mxz));
        fori(n - 1)
            if (s[i] + s.back() == 10 + '0' + '0')
                if (zeroes == 0 || (i + zeroes < n && how_much[i + zeroes] == zeroes))
                {
                    int mx = n - i - 1;
                    ans = max(ans, min(mx, 1 + p[i]) + zeroes);
                }
        writeln(max(last, ans));
    }
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
