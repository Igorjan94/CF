// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); ++it)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     pll      pair<long long, long long>
#define   whole(a)   a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   count      count__
#define  argmax(a)   (max_element(whole(a)) - (a).begin())
#define  argmin(a)   (min_element(whole(a)) - (a).begin())

#define  ints(a...)  int a; readln(a)
#define  lls(a...)   ll a; readln(a)
#define wr(args...)  err(split(#args,',').begin(),args)
                    
#define  FILENAME    "input"
#define     INF      1000000007
                    
#define    tthti     template<typename Head, typename... Tail> inline
#define   ttt12i     template<typename T1, typename T2> inline
#define    ttti      template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T&);
ttti void priws(T);
ttti void print(T);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan

#define PACK_SIZE 10

struct problem
{
    int tl, count;
    problem() {}
    problem(int tl, int count) : tl(tl), count(count) {}
};
vector<problem> problems;
vector<vector<int>> ok;
vector<vector<int>> rj;
int count = 0;
int curTime = 0;
int gid = 0;

struct submission
{
    int pid, sid, testPointer, ok, rj, time, extime, gid;
    vector<int> testTime;
    submission() {}
    submission(int sid, int pid, int time) : pid(pid), sid(sid), time(time), testPointer(0), ok(0), rj(0), extime(0)
    {
        testTime.resize(problems[pid].count);
    }
};
vector<submission> submissions;

int TEST_COUNT = 40;
int TIME_DELTA = 12000;
int RJ_COUNT = 200;
int WEIGHTED_TESTS = 10;
struct cmp
{
    bool operator() (const int& i, const int& j) const
    {
        submission& a = submissions[i];
        submission& b = submissions[j];
        problem& pa = problems[a.pid];
        problem& pb = problems[b.pid];
        int exa = a.extime == 0 ? pa.tl : a.extime;
        int exb = b.extime == 0 ? pb.tl : b.extime;
        //if (a.pid == b.pid)
            //return a.time < b.time;// || a.testPointer > b.testPointer + TEST_COUNT;
        return false
            //|| (a.testPointer > b.testPointer + TEST_COUNT)
            //|| ((a.testPointer < b.testPointer) && (exa * 1ll * (pa.count - a.testPointer + WEIGHTED_TESTS) < exb * 1ll * (pb.count - b.testPointer)))
            //|| (a.time + TIME_DELTA < b.time)
            //|| ((a.rj / (a.rj + 0.0 + a.ok)) > (b.rj / (b.rj + 0.0 + b.ok)) + (RJ_COUNT + 0.0) / 100)
            //|| (a.rj > b.rj + RJ_COUNT)
            || (a.gid < b.gid)
            || false;
    }
};
priority_queue<int, vi, cmp> q;

void push_submission(int sid)
{
    submission& s = submissions[sid];
    s.gid = gid++;
    //if (s.testPointer % PACK_SIZE == 0)
    //{
        s.ok = s.rj = 0;
        FOR(i, s.testPointer, s.testPointer + PACK_SIZE)
            s.ok += ok[s.pid][i],
            s.rj += rj[s.pid][i];// * (PACK_SIZE - i) / 2;
    //} 
    //else
        //s.ok -= ok[s.pid][s.testPointer] * (PACK_SIZE - (s.testPointer % PACK_SIZE)) / 2,
        //s.rj -= ok[s.pid][s.testPointer] * (PACK_SIZE - (s.testPointer % PACK_SIZE)) / 2;
    q.push(sid);
}

int pop_submission()
{
    int temp = q.top();
    q.pop();
    return temp;
}

int launcher(int numInvokers)
{
    int use = 0;
    while (use < numInvokers && q.size()) 
    {
        submission& s = submissions[pop_submission()];
        if (s.testPointer < problems[s.pid].count)
        {
            while (use < numInvokers && s.testPointer < problems[s.pid].count)
                s.testTime[s.testPointer] = curTime,
                printf("%d %d\n", s.sid, s.testPointer++),
                ++use;
            if (s.testPointer < problems[s.pid].count)
                push_submission(s.sid);
        }
    }
    return use;
}

void result(int sid, int tid, bool verdict) {
    submission& s = submissions[sid];
    int pid = s.pid;
    if (verdict)
        ok[pid][tid] += 1,
        s.extime = max(s.extime, curTime - s.testTime[tid]);//((s.extime * (s.testPointer + 1)) + curTime - s.time) / (s.testPointer + 2);
    else
        rj[pid][tid] += 1,
        s.testPointer = INF;

    if (s.testPointer >= problems[pid].count)
        s.testPointer = INF;
}

void run()
{
    ints(numInvokers, numProblems);
    problems.resize(numProblems);
    ok.resize(numProblems);
    rj.resize(numProblems);
    int x, y;
    fori(numProblems) 
        scanf("%d%d", &x, &y),
        problems[i] = problem(x, y),
        ok[i].resize(y + PACK_SIZE, 0),
        rj[i].resize(y + PACK_SIZE, 0);
    int delta = 10;
    int pid, sid, tid;
    char verdict[100];
    int fir = 1, sec = 2;
    while (fir == 1 && sec == 2)
    {
        while (fir == 1)
        {
            fir = scanf("%d", &pid);
            if (pid == -1)
                break;
            sid = submissions.size();
            submissions.push_back(submission(sid, pid, curTime));
            push_submission(sid);
        }
        while (sec == 2)
        {
            sec = scanf("%d %d", &sid, &tid);
            if (sid == -1 && tid == -1)
                break;
            scanf("%s", verdict);
            numInvokers++;
            result(sid, tid, string(verdict) == "OK");
        }
        if (numInvokers > 0)
        {
            int use = launcher(numInvokers);
            if (use > numInvokers)
                exit(2);
            numInvokers -= use;
        }

        curTime += delta;
        printf("-1 -1\n");
        fflush(stdout);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    //ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}























#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
