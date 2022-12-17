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

map<char, int> m, v;

struct user
{
    vector<pii> cards;
    string name;
    user(){}
    int combination = 0;
    vector<int> mxx;

    void add(string& s)
    {
        pii card = {0, m[s.back()]};
        if (s[0] != ' ')
            card.first = 10;
        else if (s[1] >= '2' && s[1] <= '9')
            card.first = s[1] - '0';
        else
            card.first = v[s[1]];
        cards.pb(card);
    }

    void calc()
    {
		int mx = 0;
		int mmx = 0;
        map<int, int> c;
        for (pii& p: cards)
            c[p.first]++,
            mx = max(mx, p.first);
        bool flash = true;
        bool street = true;
        vector<pii> sets;
        vector<pii> fours;
        vector<pii> pairs;
        for (auto& [k, v]: c)
            if (v == 4)
                fours.pb({k, v});
            else if (v == 3)
                sets.pb({k, v});
            else if (v == 2)
                pairs.pb({k, v});
                
        sort(all(cards));
        sort(all(pairs));
        fori1(5)
            flash &= cards[i - 1].second == cards[i].second,
            street &= cards[i - 1].first + 1 == cards[i].first;
        //fori(5)
            //cerr << " " << cards[i].first << " " << cards[i].second;
        //cerr << "\n";
        if (flash && street) {
            combination = 0;
			mxx = {-mx};
            //cerr << "FLASH" << " " << mx << endl;
        }
        else if (fours.size()) {
            combination = 1;
            mx = fours[0].first;
			mxx = {-mx};
            //cerr << "CARE" << " " << mx << endl;
        }
        else if (sets.size() && pairs.size()) {
            combination = 2;
            mx = sets[0].first;
			mxx = {-mx};
            //cerr << "FH" << " " << mx << endl;
        }
        else if (flash) {
            combination = 3;
			ROF(i, 4, 0)
				mxx.pb(-cards[i].first);
            //cerr << "FLASH" << " " << mx << endl;
        }
        else if (street) {
            combination = 4;
			mxx = {-mx};
            //cerr << "STREET" << " " << mx << endl;
        }
        else if (sets.size()) {
            combination = 5;
            mx = sets[0].first;
			mxx = {-mx};
            //cerr << "SET" << " " << mx << endl;
        }
        else if (pairs.size() == 2) {
            combination = 6;
            mx = pairs[1].first;
			mmx = pairs[0].first;
			mxx = {-mx, -mmx};
            //cerr << "TWO PAIRS" << " " << mx << endl;
        }
        else if (pairs.size() == 1) {
            combination = 7;
            mx = pairs[0].first;
			mxx = {-mx};
            //cerr << "PAIR" << " " << mx << endl;
        }
        else {
            combination = 8;
			mxx = {-mx};
            //cerr << "KIKER" << " " << mx << endl;
        }
    }

    bool operator<(const user& other) const
    {
        return tuple(combination, mxx, name) < tuple(other.combination, other.mxx, other.name);
    }
};

vector<string>split(string&s,string_view d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}

void run()
{
    m['H'] = 1;
    m['D'] = 2;
    m['S'] = 3;
    m['C'] = 4;
    v['J'] = 11;
    v['Q'] = 12;
    v['K'] = 13;
    v['A'] = 14;
    string s;

    while (true)
    {
        vector<user> users;
        bool eof = false;
        getline(cin, s);
        getline(cin, s);
        vector<string> cards = split(s, "|");
        while (true)
        {
            getline(cin, s);
            eof = !getline(cin, s);
            if (eof || s == "")
                break;
            user u;
            vector<string> cur = split(s, "|");
            u.name = cur[1];
            while (u.name.back() == ' ') u.name.pop_back();
            fori(cur.size())
                if (cur[i] == " 1 ")
                    u.add(cards[i]);
            u.calc();
            users.pb(u);
        }

        sort(all(users));

        vector<string> winners;
        fori(users.size())
            if (users[i].combination == users[0].combination && users[i].mxx == users[0].mxx)
                winners.pb(users[i].name);
        writeln(winners);
        if (eof) break;
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
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"  "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
