// Igorjan94, template version from 13 October 2017. C++17 version, modified 14 september 2019 (writeln<T>, main) {{{
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

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

bool is_op(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '=' || c == '?';
}

int st[100000];
int Index = 0;

void push(int x) {
    st[Index++] = x;
}
int get() {
    return st[--Index];
};

void process_op(char op) 
{
	int r = get();
	int l = get();
	switch (op) 
    {
		case '+': push(l + r); break;
		case '-': push(l - r); break;
		case '*': push(l * r); break;
		case '<': push(l < r); break;
		case '=': push(l == r); break;
        case '/': push(r != 0 ? l / r : 0); break;
		case '?':
            int cmp = get();
            push(cmp ? l : r);
            break;
	}
}
 
void run()
{
    ints(k);
    string t;
    getline(cin, t);
    getline(cin, t);
    stringstream ss(t);
    vector<string> s;
    while (ss >> t) s.pb(t);
    int l = s.size();
    vector<int> sss(l);
    fori(l)
        if (s[i].size() != 1 || (s[i][0] >= '0' && s[i][0] <= '9'))
            sss[i] = stoi(s[i]);
    ints(n);
    fori(n)
    {
        vector<int> a(k);
        readln(a);
        Index = 0;
        fori(l)
        {
            string& temp = s[i];
            if (temp.size() == 1 && is_op(temp[0]))
                process_op(temp[0]);
            else if (temp.size() == 1 && temp[0] >= 'a' && temp[0] <= 'z')
                push(a[temp[0] - 'a']);
            else if (temp.size() >= 1)
                push(sss[i]);
        }
        writeln(st[0]);
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
