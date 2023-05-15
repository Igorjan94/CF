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
//}}}

template<typename T>
struct query
{
    int l;
    int r;
    int i;
    int updates;
    T q;

    int lb;
    int rb;

    query(int b, int l, int r, int i, int updates, const T& q) : l(l), r(r), i(i), updates(updates), q(q) 
    {
        this->lb = l / b;
        this->rb = r / b;
    }
};

template<typename S, typename T, typename U>
struct MOWithUpdates
{
    int n;
    int b = 0;
    vector<query<T>> queries;
    vector<U> updates;
    vector<S> answers;

    const void f(int);
    void (*addLeft)(int);
    void (*addRight)(int);
    void (*delLeft)(int);
    void (*delRight)(int);
    void (*update)(int, int, int, bool, const U&);
    S (*getAnswer)(int, int, const T&);

    void addQuery(int l, int r, const T& t) {
        int i = queries.size();
        queries.push_back(query(b, l, r, i, updates.size(), t));
    }

    void addUpdate(const U& u) {
        updates.push_back(u);
    }

    MOWithUpdates(
        unsigned int maxN,
        unsigned int maxQ,
        void addLeft(int),
        void addRight(int),
        void delLeft(int),
        void delRight(int),
        void update(int, int, int, bool, const U&),
        S getAnswer(int, int, const T&)
    ) {
        queries.reserve(maxQ);
        updates.reserve(maxQ);
        n = maxN;
        b = pow(n, 2. / 3);
        this->addLeft = addLeft;
        this->addRight = addRight;
        this->delLeft = delLeft;
        this->delRight = delRight;
        this->update = update;
        this->getAnswer = getAnswer;
    }

    vector<S> go(
    ) {
        answers.resize(queries.size());
        sort(all(queries), [&](const auto& a, const auto& b) {
            if (a.lb != b.lb)
                return a.lb < b.lb;
            if (a.rb != b.rb)
                return a.lb & 1 ? a.rb < b.rb : a.rb > b.rb;
            return a.lb & 1 ^ a.rb & 1 ? a.updates < b.updates : a.updates > b.updates;
        });

        int L = 0;
        int R = -1;
        int E = 0;

        for (const auto& [l, r, id, t, q, _, __]: queries) 
        {
            while (E < t) { update(E, L, R, true, updates[E]); ++E; }
            while (E > t) { --E; update(E, L, R, false, updates[E]); }
            while (L > l) addLeft(--L);
            while (R < r) addRight(++R);
            while (L < l) delLeft(L++);
            while (R > r) delRight(R--);
            answers[id] = getAnswer(l, r, q);
        }
        return answers;
    }
};

map<int, int> coords;
vector<int> a;
vector<int> m;
vector<int> diffsCNT;

void er(int x) {
    --diffsCNT[x];
}

void ad(int x) {
    ++diffsCNT[x];
}

void add(int id) {
    int x = a[id];
    er(m[x]);
    ad(++m[x]);
}

void del(int id) {
    int x = a[id];
    er(m[x]);
    ad(--m[x]);
}

void update(int index, int L, int R, bool forward, const array<int, 3>& update) {
    auto [i, from, to] = update;
    if (!forward) to = from;
    if (L <= i && i <= R)
        del(i);
    a[i] = to;
    if (L <= i && i <= R)
        add(i);
}

int get(int x) {
    auto it = coords.find(x);
    if (it != coords.end())
        return it->second;
    int sz = coords.size();
    return coords[x] = sz;
}

int answer(int l, int r, const int&) {
    for (int mex = 1; ; ++mex)
        if (diffsCNT[mex] == 0)
            return mex;
    return -1;
}

//MO with updates
void run()
{
    ints(n, q);
    a.resize(n);
    m.resize(n + q + 10);
    diffsCNT.resize(n);
    
    readln(a);
    for (int& x: a)
        x = get(x);

    MOWithUpdates<int, int, array<int, 3>> MO(n, q, add, add, del, del, update, answer);
    fori(q)
    {
        ints(type, l, r); --l;
        if (type == 1)
            MO.addQuery(l, --r, 0);
        else
        {
            r = get(r);
            MO.addUpdate({l, a[l], r});
            a[l] = r;
        }
    }
    for (int i = SZ(MO.updates) - 1; i >= 0; --i)
        a[MO.updates[i][0]] = MO.updates[i][1];

    auto ans = MO.go();
    for (int& x: ans)
        writeln(x);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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
