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
    vector<int> path;

    flow() {}

    friend istream& operator>>(istream& in, flow& e) {
        return in >> e.id >> e.from >> e.to >> e.r;
    }
    
    friend ostream& operator<<(ostream& out, const flow& e) {
        return out << "Flow " << e.id << ", from " << e.from << ", to " << e.to << ", rate " << e.r;
    }

}; // }}}

int n, m, c, F, g = 4500, TREES = 1;

vector<edge> edges; // {{{
vector<flow> flows;
vector<int> groups;
vector<node> nodes;
unordered_set<int> ggg;
vector<int> nnn;

bool checkCannotUseEdge(int u, int v, int fromEdge, const int& rate, const edge& e) {
    return e.now + rate > e.c || !nodes[u].can(e.id, fromEdge) || groups[e.g] == GFL || nodes[v].now == NFL;
};

struct tree
{
    vector<int> d;
    vector<pii> p;
    vector<bool> used;
    int root;
    int c = 12000;
    int fails = 0;
    int to = -1;

    tree()
    {
        d.resize(n, MOD);
        p.resize(n, {-1, -1});
        used.resize(n, false);
    }

    tree(int root, int c, int to) : root(abs(root) % n), to(to)
    {
        c = abs(c) % 12001;
        this->c = c;
        d.resize(n, MOD);
        p.resize(n, {-1, -1});
        used.resize(n, false);
        bfs(this->root, this->c, this->to);
    }

    void reset(int root, int c = 0, int to = -1)
    {
        fails = 0;
        if (!c)
            c = abs(int(rng())) % 12001;
        this->c = c;

        fori(n)
            d[i] = MOD,
            p[i] = {-1, -1},
            used[i] = false;
        this->root = abs(root) % n;
        this->to = to;
        bfs(this->root, this->c, this->to);
    }

    void bfs(int root, int rate, int to = -1)
    {
        queue<tuple<int, int, int>> s;
        d[root] = 0;
        s.push({0, root, -1});
        while (s.size())
        {
            auto [_, u, fromEdge] = s.front();
            s.pop();
            if (u == to) break;
            used[u] = true;
            for (const int& eid: nodes[u].out)
            {
                const auto& e = edges[eid];
                int v = e.getTo(u);
                if (used[v] || checkCannotUseEdge(u, v, fromEdge, rate, e))
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
    }

    vector<int> getPath(int from, int to)
    {
        if (nodes[from].now == NFL) return vector<int>();
        if (nodes[to].now == NFL) return vector<int>();
        if (d[from] == MOD) return vector<int>();
        if (d[to] == MOD) return vector<int>();

        vector<int> p1, p2;
        auto add = [&](vector<int>& path, int& u) {
            path.pb(p[u].second);
            u = p[u].first;
        };
        while (d[from] > d[to]) add(p1, from);
        while (d[from] < d[to]) add(p2, to);
        while (d[from] && from != to)
        {
            add(p1, from);
            add(p2, to);
        }
        reverse(all(p2));
        copy(all(p2), back_inserter(p1));
        return p1;
    }

    bool addPath(flow& f)
    {
        bool ok = addPathImpl(f);
        fails += !ok;
        if (fails >= 10)
            reset(root);
        return ok;
    }

    bool addPathImpl(flow& f)
    {
        vector<int> path = getPath(f.from, f.to);
        if (!path.size()) return false;

        ggg.clear();
        nnn.clear();

        int u = f.from;
        int fromEdge = -1;
        for (int& eid: path)
        {
            edge& e = edges[eid];
            int v = e.getTo(u);
            if (checkCannotUseEdge(u, v, fromEdge, f.r, e))
                return false;
            nnn.pb(u);
            ggg.insert(e.g);
            u = v;
            fromEdge = eid;
        }

        u = f.from;
        for (int& eid: path)
        {
            edge& e = edges[eid];
            e.now += f.r;
            u = e.getTo(u);
        }
        for (int gg: ggg)
            groups[gg]++;

        nodes[u].now++;
        for (int nn: nnn)
            nodes[nn].now++;
        f.path = path;
        return true;
    }

    friend ostream& operator<<(ostream& out, const tree& t)
    {
        out << "Tree: root " << t.root << ", d =";
        for (int x: t.d)
            out << " " << x;
        return out;
    }
}; // }}}

void run()
{
    double time = clock(); // {{{
    readln(n, m, c, F);
    nodes.resize(n);
    edges.resize(m);
    groups.resize(g + 1);
    flows.resize(F);
    fori(n) nodes[i].id = i;

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
            //sort(all(nodes[i].out), [&](int a, int b) {
                //return edges[a].c > edges[b].c;
            //});
    } // }}}

    tree t(0, 0, -1);
    shuffle(all(flows), rng);
    //sort(all(flows), [&](const flow& a, const flow& b) {
        //return tuple(t.d[a.from], a.r) < tuple(t.d[b.from], b.r);
        //return tuple(a.from, a.to) < tuple(b.from, b.to);
    //});
    vector<tree> trees(1);
    //fori(TREES)
        //trees.pb(tree(0, flows[0].r * 3));

    fori(F)
    {
        auto& f = flows[i];
        if (1000.0 * (clock() - time) / CLOCKS_PER_SEC > 1950)
            break;
        //if (++i % 100 == 99)
            //cerr << i << "/" << F << endl;
        if (!i || flows[i - 1].from != f.from)
            trees[0].reset(f.from, f.r, f.to);
        trees[0].addPath(f);
        continue;
        const int MXQ = 2;
        forn(q, MXQ)
        {
            bool found = false;
            forj(TREES)
                if (trees[j].addPath(f))
                {
                    found = true;
                    break;
                }
            if (found) break;
            if (!found && q + 1 != MXQ)
                forj(TREES)
                    trees[j].reset(f.from, f.r * (MXQ - q - 1));
        }
    }

    int ans = 0;
    { //PRINT ANSWER
        for (const auto& f: flows) ans += f.path.size() != 0;
        writeln(ans);
        for (const auto& f: flows) if (f.path.size()) writeln(f.id, f.path);
    }

#ifndef ONLINE_JUDGE //{{{
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
            if (u != f.to)
                writeln("END IN WRONG NODE", f.to, "EXPECTED", u, "FOUND");
            N[u]++;
        }
        fori(m)
            if (E[i] > edges[i].c)
                writeln("ERROR EDGE CAPACITY", i, "EXPECTED", edges[i].c, "FOUND", E[i]);
        fori(n)
            if (N[i] > NFL)
                writeln("ERROR NODE FLOW LIMIT", i, "EXPECTED", NFL, "FOUND", N[i]);
        fori(g + 1)
            if (G[i].size() > GFL)
                writeln("ERROR GROUP FLOW LIMIT", i, "EXPECTED", GFL, "FOUND", G[i].size());

        cerr << ans << endl;
        cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    }
#endif //}}}
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
