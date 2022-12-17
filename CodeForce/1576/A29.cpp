// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast")
#endif
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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

[[maybe_unused]] const int GFL = 100;
[[maybe_unused]] const int NFL = 200;

struct edge // {{{
{
    int id;
    int g;
    int from;
    int to;
    int d;
    int c;
    int now = 0;

    int getTo(int u) const
    {
        return from ^ to ^ u;
    }

    edge() {}

    friend istream& operator>>(istream& in, edge& e) {
        return in >> e.id >> e.g >> e.from >> e.to >> e.d >> e.c;
    }
    
    friend ostream& operator<<(ostream& out, const edge& e) {
        return out << "Edge: " << e.id << ", g " << e.g << ", from " << e.from << ", to " << e.to << ", d " << e.d << ", c " << e.c << ", now " << e.now;
    }
};

struct node
{
    int id;
    vector<int> out;
    unordered_set<int> restrictions;
    int now = 0;

    node() {}

    void addRestriction(int fromEdge, int toEdge)
    {
        restrictions.insert(getHash(fromEdge, toEdge));
    }

    int getHash(int fromEdge, int toEdge) const
    {
        return (min(fromEdge, toEdge) << 16) + max(fromEdge, toEdge);
    }

    bool can(int fromEdge, int toEdge) const 
    {
        if (fromEdge == -1 || toEdge == -1) return true;
        return restrictions.count(getHash(fromEdge, toEdge)) == 0;
    }

    friend ostream& operator<<(ostream& out, const node& e) {
        return out << "Node " << e.id << ", out " << e.out.size() << ", restrictions " << e.restrictions.size() << ", now " << e.now;
    }

};

struct flow
{
    int id;
    int from;
    int to;
    int r;
    bool use = false;
    vector<int> path;

    flow() {}

    friend istream& operator>>(istream& in, flow& e) {
        return in >> e.id >> e.from >> e.to >> e.r;
    }
    
    friend ostream& operator<<(ostream& out, const flow& e) {
        return out << "Flow " << e.id << ", from " << e.from << ", to " << e.to << ", rate " << e.r;
    }

};

struct group
{
    int now = 0;

    group() {}
}; // }}}

void run()
{
    double time = clock();
    ints(n, m, c, F); int g = 4500;
    vector<node> nodes(n);
    fori(n) nodes[i].id = i;
    vector<edge> edges(m);
    vector<flow> flows(F);
    vector<group> groups(g + 1);

    { //READ INPUT
        readln(edges);
        for (const auto& e: edges)
            nodes[e.from].out.pb(e.id),
            nodes[e.to].out.pb(e.id);
        forn(q, c)
        {
            ints(id, u, v);
            nodes[id].addRestriction(u, v);
        }
        readln(flows);
        fori(n)
            shuffle(all(nodes[i].out), rng);


        //writeln(nodes);
        //writeln(edges);
        //writeln(flows);
    }

    auto checkCannotUseEdge = [&](int u, int v, int fromEdge, const flow& f, const edge& e) {
        return groups[e.g].now == GFL || nodes[v].now == NFL || e.now + f.r > e.c || !nodes[u].can(e.id, fromEdge);
    };

    vector<int> d(n, MOD);
    vector<pii> p(n, {-1, -1});
    vector<bool> used(n, false);
    auto getPath = [&](const flow& f) {
        fori(n)
            d[i] = MOD,
            p[i] = {-1, -1},
            used[i] = false;
        d[f.from] = 0;
        if (nodes[f.from].now == NFL) return vector<int>();
        if (nodes[f.to].now == NFL) return vector<int>();

        auto bfs = [&]() {
            queue<tuple<int, int, int>> s;
            s.push({0, f.from, -1});
            while (s.size())
            {
                auto [_, u, fromEdge] = s.front();
                s.pop();
                //s.erase(s.begin());
                used[u] = true;
                if (u == f.to) break;
                for (const int& eid: nodes[u].out)
                {
                    const auto& e = edges[eid];
                    int v = e.getTo(u);
                    if (used[v] || checkCannotUseEdge(u, v, fromEdge, f, e))
                        continue;
                    int cur = d[u] + 1;
                    if (cur < d[v])
                    {
                        d[v] = cur;
                        p[v] = {u, e.id};
                        s.push({d[v], v, e.id});
                    }
                }
            }
        };

        bfs();
        if (d[f.to] == MOD)
            return vector<int>();

        vector<int> path;
        int u = f.to;
        while (u != -1 && p[u].second != -1)
            path.pb(p[u].second),
            u = p[u].first;
        reverse(all(path));
        return path;
    };

    auto applyPath = [&](flow& f) {
        unordered_set<int> ggg;
        int u = f.from;
        for (int& eid: f.path)
        {
            edge& e = edges[eid];
            e.now += f.r;
            nodes[u].now++;
            u = e.getTo(u);
            ggg.insert(e.g);
        }
        for (int gg: ggg)
            groups[gg].now++;
        nodes[u].now++;
    };

    sort(all(flows), [](const flow& a, const flow& b) {
        return a.r < b.r;
    });
    fori((7 * F + 7) / 8)
        flows[i].use = true;
    shuffle(all(flows), rng);

    //int i = 0;
    for (auto& f: flows)
        if (f.use)
    {
    
        if (1000.0 * (clock() - time) / CLOCKS_PER_SEC > 1950)
            break;
        //if (++i % 100 == 99)
            //cerr << i << "/" << F << endl;
        const auto path = getPath(f);
        if (!path.size())
            continue;
        f.path = path;
        applyPath(f);
    }

    //writeln(nodes);
    //writeln(edges);
    int ans = 0;
    { //PRINT ANSWER
        for (const auto& f: flows) ans += f.path.size() != 0;
        writeln(ans);
        for (const auto& f: flows) if (f.path.size()) writeln(f.id, f.path);

    }

#ifndef ONLINE_JUDGE
    {
        vector<int> E(m);
        vector<int> N(n);
        vector<set<int>> G(g + 1);
        for (const auto& f: flows)
        {
            if (!f.path.size()) continue;
            set<int> nodesPerPath;
            set<int> edgesPerPath;
            int u = f.from;

            for (auto& eid: f.path)
            {
                auto e = edges[eid];
                E[eid] += f.r;
                N[u]++;
                if (!nodesPerPath.insert(u).second)
                    writeln("NODE", u, "ALREADY EXISTS IN FLOW", f.id);
                G[e.g].insert(f.id);
                if (!edgesPerPath.insert(eid).second)
                    writeln("EDGE", eid, "ALREADY EXISTS IN FLOW", f.id);
                u = e.getTo(u);
            }
            if (!nodesPerPath.insert(u).second)
                writeln("NODE", u, "ALREADY EXISTS IN FLOW", f.id);
            N[u]++;
        }
        fori(m)
            if (E[i] > edges[i].c)
                writeln("ERROR EDGE CAPACITY", i, "EXPECTED <=", edges[i].c, "FOUND", E[i]);
        fori(n)
            if (N[i] > NFL)
                writeln("ERROR NODE FLOW LIMIT", i, "EXPECTED <=", NFL, "FOUND", N[i]);
        fori(g + 1)
            if (G[i].size() > GFL)
                writeln("ERROR GROUP FLOW LIMIT", i, "EXPECTED <=", GFL, "FOUND", G[i].size());

        cerr << ans << endl;
        cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    }
#endif
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
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
