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
//umax
template<typename T1, typename T2>
T1 umax(T1& a, T2 b)
{
    return a < T2(b) ? a = b : a;
}
 
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
//}}}
 
int ROUND_UP(int x, int y) // {{{
{
    return (x + y - 1) / y;
}
 
int NON_TOP_MACHINE = 1;
int NON_TOP_DISK = 1;
struct task;
struct disk;
struct machine;
 
struct machine
{
    int id;
    int p;
    int t = 0;
 
    int get(int sz)
    {
        return ROUND_UP(sz, p);
    }
 
    machine() {}
};
 
istream& operator>>(istream& is, machine& m) {
    is >> m.id >> m.p; --m.id;
    return is;
}
 
struct disk
{
    int id;
    int s;
    int c;
    int used = 0;
 
    int get(int dt)
    {
        return ROUND_UP(dt, s);
    }
 
    disk() {}
};
 
istream& operator>>(istream& is, disk& d) {
    is >> d.id >> d.s >> d.c; --d.id;
    return is;
}
 
typedef bitset<10001> bs;
 
struct task
{
    int id;
    int sz;
    int dt;
    int importance = 1;
    int ind = 0;
 
    vector<int> availableMachines;
 
    vector<int> gData;
    vector<int> gTask;
    vector<int> g;
    vector<int> rev;
    bs r;
 
    vector<int> rData;
    vector<int> rTask;
 
    int x = -1;
    int y = -1;
    int z = -1;
 
    int a = -1;
    int b = -1;
    int c = -1;
    int d = -1;
 
    int getDataRead();
 
    void assign(int x, int y, int z);
 
    task() {}
 
    bool operator<(const task& other) const 
    {
        return importance < other.importance;
        //return sz > other.sz;
        //return tuple(-sz, -importance) < tuple(-other.sz, -other.importance);
    }
};
 
istream& operator>>(istream& is, task& t) {
    int nn, x;
    is >> t.id >> t.sz >> t.dt >> nn; --t.id;
    fori(nn)
    {
        is >> x; --x;
        t.availableMachines.pb(x);
    }
    return is;
}
 
ostream& operator<<(ostream& os, const task& t) {
    os << t.id + 1 << " " << t.x << " " << t.y + 1 << " " << t.z + 1;
    //os << "Task: [" << t.id << " " << t.sz << " " << t.dt << " " << t.gData.size() << " " << t.gTask.size() << " " << t.availableMachines.size() << "]";
    return os;
} // }}}
 
int c = 4;
 
void shuffleOrder(vector<int>& order, int S)
{
    int n = SZ(order);
    for (int i = 0; i < n; )
    {
        int step = S;
        shuffle(order.begin() + i, order.begin() + min(n, i + step), rng);
        i += S;
    }
}
 
void sortOrder(const vector<task>& edges, vector<int>& order, int step)
{
    function<bool(int, int)> f = [&](const int& a, const int& b) {
        return edges[a] < edges[b];
    };
    //int test = rng() % c;
    //if (test % c == 0)
    //{
        //f = [&](const int& a, const int& b) {
            //return tuple(edges[a].sz, edges[a].importance) > tuple(edges[b].sz, edges[b].importance);
        //};
    //}
    //else if (test % c == 1)
    //{
        //f = [&](const int& a, const int& b) {
            //return tuple(edges[a].importance, edges[a].sz) > tuple(edges[b].importance, edges[b].sz);
        //};
    //}
    //else if (test % c == 2)
    //{
        //f = [&](const int& a, const int& b) {
            //return tuple(edges[a].importance, -edges[a].sz) > tuple(edges[b].importance, -edges[b].sz);
        //};
    //}
    //else if (test % c == 3)
    //{
        //f = [&](const int& a, const int& b) {
            //return tuple(edges[a].importance) > tuple(edges[b].importance);
        //};
    //}
    sort(all(order), f);
    shuffleOrder(order, step);
}
 
//topsort
//Returns empty vector if cycle is found
vi topsort(vector<int>& order, vector<task>& edges, int msz, int step, bool reversed = false)
{
    int n = edges.size();
    vector<int> ans;
    vector<int> used(n, 0);
    
    if (order.size() == 0)
    {
        order.resize(n);
        iota(all(order), 0);
        sortOrder(edges, order, step);
        //if (test % c <= 1)
        //if (rng() % 20 == 0)
        //{
            //vector<int> order2;
            //int C = n / msz;
            //for (int i = 0; i < C; i++)
                //for (int j = i; j < n; j += C)
                    //order2.pb(order[j]);
            //order = order2;
        //}
    }
    else
        shuffleOrder(order, step);
 
    if (rng() % 2)
    {
        queue<int> q;
        for (int i: order)
            if (edges[i].ind == 0)
                q.push(i);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            ans.pb(u);
            used[u] = 1;
            //sortOrder(edges, edges[u].g, step);
            for (const int& v: edges[u].g)
                if (--edges[v].ind == 0)
                    q.push(v);
        }
        if (reversed)
            reverse(ans.begin(), ans.end());
    }
    else 
    {
        auto dfs = [&](auto dfs, int u) -> void {
            used[u] = 1;
            //sortOrder(edges, edges[u].g, step);
            for (const int& v: edges[u].g)
                if (!used[v])
                    dfs(dfs, v);
            used[u] = 2;
            ans.pb(u);
        };
    
        for (int i: order)
            if (!used[i])
                dfs(dfs, i);
        if (!reversed)
            reverse(ans.begin(), ans.end());
    }
    return ans;
}
 
vector<disk> disks; // {{{
vector<machine> machines;
vector<task> tasks;
 
int task::getDataRead()
{
    return disks[z].get(dt);
}
 
void task::assign(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
 
    a = x;
    b = a;
    for (int pred: gData)
        b += tasks[pred].getDataRead();
    c = b + machines[y].get(sz);
    d = c + disks[z].get(dt);
 
    machines[y].t = d;
    disks[z].used += dt;
}
 
void reset()
{
    for (auto& t: tasks)
    {
        t.x = t.y = t.z = t.a = t.b = t.c = t.d = 0;
        shuffle(all(t.gData), rng);
        shuffle(all(t.gTask), rng);
        shuffle(all(t.rData), rng);
        shuffle(all(t.rTask), rng);
        shuffle(all(t.rev), rng);
        shuffle(all(t.g), rng);
        t.ind = SZ(t.rev);
    }
    for (auto& d: disks)
        d.used = 0;
    for (auto& m: machines)
        m.t = 0; 
} // }}}
 
auto run(vector<int>& order) // {{{
{
    reset();
    for (int tt: order)
    {
        task& t = tasks[tt];
        int time = 0;
        for (int dd: t.gData)
            umax(time, tasks[dd].d);
 
        int e = MOD;
        int x;
        int y;
        int ee = MOD;
        int xx;
        int yy;
        for (int M: t.availableMachines)
        {
            auto& m = machines[M];
            int start = max(time, m.t);
            for (int dt: t.gTask)
                umax(start, m.id == tasks[dt].y ? tasks[dt].d : tasks[dt].c);
 
            int cur = start + m.get(t.sz);
            if (cur < e)
                ee = e,
                xx = x,
                yy = y,
                e = cur,
                x = start,
                y = m.id;
        }
        int trash = 3;
        if (ee != MOD && t.importance < trash && rng() % 2)
            e = ee,
            x = xx,
            y = yy;
 
        int eee = MOD;
        int z;

        int eeee = MOD;
        int zz;
        for (auto& d: disks)
            if (d.used + t.dt <= d.c)
            {
                int cur = e + d.get(t.dt);
                if (cur < eee)
                    eeee = eee,
                    zz = z,
                    eee = cur,
                    z = d.id;
            }

        if (eeee != MOD && t.importance < trash && rng() % 2)
            z = zz;

        t.assign(x, y, z);
    }
    return tasks;
} // }}}
 
int main()
{
//{{{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ints(l);
    tasks.resize(l);
    readln(tasks);
    ints(n);
    machines.resize(n);
    readln(machines);
    ints(m);
    disks.resize(m);
    readln(disks);
    ints(dd);
    fori(dd)
    {
        ints(u, v); --u; --v;
        tasks[v].gData.pb(u);
        tasks[u].rData.pb(v);
    }
    ints(td);
    fori(td)
    {
        ints(u, v); --u; --v;
        tasks[v].gTask.pb(u);
        tasks[u].rTask.pb(v);
    }
 
    sort(all(tasks),    [&](const auto& a, const auto& b) { return a.id < b.id; });
    sort(all(disks),    [&](const auto& a, const auto& b) { return a.id < b.id; });
    sort(all(machines), [&](const auto& a, const auto& b) { return a.id < b.id; });
 
    for (auto& t: tasks)
    {
        t.g.insert(t.g.end(), all(t.gData));
        t.g.insert(t.g.end(), all(t.gTask));
        sort(all(t.g));
        t.g.resize(unique(all(t.g)) - t.g.begin());

        t.rev.insert(t.rev.end(), all(t.rData));
        t.rev.insert(t.rev.end(), all(t.rTask));
        sort(all(t.rev));
        t.rev.resize(unique(all(t.rev)) - t.rev.begin());

        if (t.sz > 500)
        {
            vector<pii> temp;
            for (int M: t.availableMachines)
                temp.pb({-machines[M].p, M});
            sort(all(temp));
            while (temp.size() > 1 && -temp.back().first < 10)
                temp.pop_back();
            vector<int> nxt;
            for (auto& [_, M]: temp)
                nxt.pb(M);
            t.availableMachines = nxt;
        }
        t.ind = SZ(t.rev);
    }
    vector<int> o;
    auto order = topsort(o, tasks, machines.size(), 1);
    reset();
    for (int tt: order)
    {
        task& t = tasks[tt];
        for (int dep: t.rData)
        {
            t.r[dep] = true;
            t.r |= tasks[dep].r;
        }
 
        for (int dep: t.rTask)
        {
            t.r[dep] = true;
            t.r |= tasks[dep].r;
        }
 
        t.importance = t.r.count();
    }
                
    auto start = clock();
    // }}}
#ifdef ONLINE_JUDGE
    auto TL = 14.6;
#else
    auto TL = 3.;
#endif
    auto makespan = MOD;
    vector<task> answer;
    vector<vector<int>> current;
    int test = 0;
    while ((clock() - start + 0.0) / CLOCKS_PER_SEC < TL)
    //while ((clock() - start + 0.0) / CLOCKS_PER_SEC < TL)
    {
        //if (test % 2 == 0)
        //{
            o.clear();
            o.resize(0);
        //}
        //run(1);
        int step = rng() % 77 + 1;
        auto ans = topsort(o, tasks, machines.size(), step, true);
        run(ans);
        int cur = 0;
        for (auto& t: tasks)
            umax(cur, t.d);
        if (cur < makespan)
            makespan = cur,
            current.pb(o),
            answer = vector<task>(all(tasks));
        ++test;
    }
    if (false) {
        reverse(all(current));
        current.resize(min(SZ(current), 10));
        int test2 = 0;
        while ((clock() - start + 0.0) / CLOCKS_PER_SEC < TL)
        {
            int step = rng() % 100 + 1;
            int index = rng() % SZ(current);
            auto ttt = current[index];
            auto ans = topsort(ttt, tasks, machines.size(), step, true);
            run(ans);
            int cur = 0;
            for (auto& t: tasks)
                umax(cur, t.d);
            if (cur < makespan)
                makespan = cur,
                current[index] = ttt,
                answer = vector<task>(all(tasks));
            ++test2;
        }
    }
    writeln(answer);
    cerr << makespan << " " << test << endl;
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
