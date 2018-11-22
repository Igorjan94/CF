// Igorjan94, template version from 13 October 2017. C++17 version {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

typedef vector<long long> vll;
typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) a.begin(), a.end()
#define   next   next__
#define   prev   prev__
#define  count   count__
#define   SZ(a)  (int(a.size()))
#define contains(s, value) (s.find(value) != s.end())

#define ints(a...)  int a; readln(a)
#define strings(a...) string a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline
                    
const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();
                    
void writeln(){cout<<"\n";}ttti void print(T a);ttti void priws(T a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H h,T...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}
///-------------------------------------------------------------------------------------------------------------------------------------

void run()
{
    ints(n, s, c, h, u);
    strings(pattern, bottles);
    cerr.precision(7);
    cerr << fixed;
    vector<int> next(2 * n);

    { //{{{
        string dpattern = pattern + pattern;
        map<char, int> last;
        fori(n * 2)
        {
            if (contains(last, dpattern[i]))
                next[last[dpattern[i]]] = i;
            last[dpattern[i]] = i;
        }
    } //}}}
    auto getPatternColor = [&](int position) {
        return pattern[position % n];
    };
    auto getNextColor = [&](int index) {
        int mod = index % n;
        int real = index - mod;
        return real + next[mod];
    };

    auto getAnswer = [&](int runNumber) {
        double time = clock();
        set<int> hams;
        map<int, int> numbers;
        fori(u) hams.insert(i), numbers[i] = i;
        string currentBottles = bottles.substr(0, h);
        int nextBottle = h;
        vector<pair<int, char>> actions;

        auto getNextBottle = [&]() {
            if (nextBottle >= SZ(bottles))
                return '*';
            return bottles[nextBottle++];
        };
        auto useBottle = [&](int index) {
            auto temp = getNextBottle();
            if (temp == '*')
                currentBottles.erase(index);
            else
                currentBottles[index] = temp;
        };
        auto getFreePlace = [&](int position, char color) {
            position++;
            while (getPatternColor(position) != color) ++position;
            while (contains(hams, position)) position = getNextColor(position);
            return position;
        };
        auto getFreeHams = [&](int position, char color) {
            set<int> ans = hams;
            ans.erase(position);
            position++;
            while (getPatternColor(position) != color) ++position;
            while (contains(hams, position)) ans.erase(position), position = getNextColor(position);
            return ans;
        };

        auto shoot = [&](int position, int bottle, int nextPlace) {
            hams.erase(position);
            actions.emplace_back(numbers[position], currentBottles[bottle]);
            hams.insert(nextPlace);
            numbers[nextPlace] = numbers[position];
            numbers.erase(position);
            useBottle(bottle);
        };
        auto getBottleIndex = [&](int position, bool force) -> pii {
            set<char> used = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
            int mx = 0;
            int index = -1;
            int i = 0;
            for (char c: currentBottles)
            {
                if (contains(used, c))
                    if (int nextPlace = getFreePlace(position, c); nextPlace > mx)
                        mx = nextPlace,
                        index = i;
                ++i;
                used.erase(c);
            }
            //if (false)
            if (!force && nextBottle < SZ(bottles))
            {
                int iii = 2;//runNumber % 3 + 1;
                    //runNumber % 15 < 3  ? 1 :
                    //runNumber % 15 < 13 ? 2 :
                    //(1 + rand() % 2);
                string&& temp = bottles.substr(nextBottle, iii);
                for (char c: temp)
                    if (contains(used, c))
                        if (int nextPlace = getFreePlace(position, c); nextPlace > mx)
                            return {-1, c};
            }
            return {index, mx};
        };

        fori(s)
        {
            int bottleIndex, nextPlace;
            int found = -1;
            for (int ham: hams)
            {
                tie(bottleIndex, nextPlace) = getBottleIndex(ham, false);
                if (bottleIndex != -1)
                {
                    found = ham;
                    break;
                }
            }
            if (found == -1)
            {
                int first = *hams.begin();
                auto [bi, color] = getBottleIndex(first, false);
                auto free = getFreeHams(first, color);

                if (SZ(free) == 0)
                {
                    int index = rand() % SZ(hams);
                    found = *hams.begin();
                    index %= 2;
                    for (auto it = hams.begin(); index-- > 0; found = *(++it));
                    tie(bottleIndex, nextPlace) = getBottleIndex(found, true);
                }
                else
                {
                    int index = rand() % SZ(free);
                    found = *free.begin();
                    index %= 4;
                    for (auto it = free.begin(); index-- > 0; found = *(++it));
                    tie(bottleIndex, nextPlace) = getBottleIndex(found, true);
                }
            }
            shoot(found, bottleIndex, nextPlace);
        }
        double in = clock() - time;
#ifndef ONLINE_JUDGE
        //cerr << "Done in " << in / CLOCKS_PER_SEC << " secs (" << *hams.begin() << ")\n";
#endif
        return tuple(in, *hams.begin(), actions);
    };

    double time = clock();
    double TL = 15;
    int runNumber = 0;
    auto [tm, ans, actions] = getAnswer(runNumber++);

    while ((clock() - time + tm * 2) / CLOCKS_PER_SEC < TL)
        if (auto [_, tempAns, tempActions] = getAnswer(runNumber++); tempAns > ans)
            ans = tempAns,
            actions = tempActions;
    cerr << ans << "\n";
#ifdef ONLINE_JUDGE
    writeln(actions);
#endif
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
