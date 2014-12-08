#include <bits/stdc++.h>

#define enter printf("\n")
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;
int INF = 1000000007;
string FILENAME = "input";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

const int N = 50001;
int n, m, k;

//copypasted from Megabyte777;
template <class Scalar>
struct range_t;
typedef range_t<double> range;
typedef range_t<float>  range_f;
typedef range_t<int>    range_i;
template <class Scalar>
struct range_t
{
  Scalar inf, sup, r;

  range_t(Scalar inf, Scalar sup, Scalar r)
     : inf(inf)
     , r(r)
     , sup(sup)
  {}

  range_t()
     : inf(0)
     , sup(-1)
  {}

  bool is_empty() const { return inf > sup; }

  bool contains(Scalar x) const { return (inf <= x) && (x <= sup); }

  static range_t maximal()
  {
     static const Scalar max_val = std::numeric_limits<Scalar>::max();
     return range_t(-max_val, max_val);
  }
};

template <class Scalar>
range_t<Scalar> const operator & (range_t<Scalar> const & a, range_t<Scalar> const & b)
{
  return range_t<Scalar>(std::max(a.inf, b.inf), std::min(a.sup, b.sup));
}

inline float center(range_f const & r)
{
  return .5f + r.inf / 2.f + r.sup / 2.f;
}

template <class Scalar>
Scalar size(range_t<Scalar> const & r)
{
  return r.sup - r.inf;
}

template <typename Scalar>
struct interval_tree
{
    ~interval_tree()
    {
        delete left_child;
        delete right_child;
    }

    interval_tree(std::vector<range_t<Scalar> > const &segments)
        : left_child(0)
        , right_child(0)
    {
        if (segments.size() == 0)
            return;
        std::vector<Scalar> coordinates;
        for (range_t<Scalar> const &r : segments)
        {
            coordinates.push_back(r.inf);
            coordinates.push_back(r.sup);
        }
        std::nth_element(coordinates.begin(), coordinates.begin() + coordinates.size() / 2, coordinates.end());
        mid = coordinates[coordinates.size() / 2];
        std::vector<range_t<Scalar> > left, right;
        for (range_t<Scalar> const &r : segments)
        {
            if (r.sup < mid)
                left.push_back(r);
            if (r.inf > mid)
                right.push_back(r);
            if (r.inf <= mid && r.sup >= mid)
            {
                left_segments.push_back(r);
                right_segments.push_back(r);
            }
        }
        std::sort(left_segments.begin(), left_segments.end(),
                [] (range_t<Scalar> const &a, range_t<Scalar> const &b)
                {
                    return a.inf < b.inf;
                }
        );
        std::sort(right_segments.begin(), right_segments.end(),
                [] (range_t<Scalar> const &a, range_t<Scalar> const &b)
                {
                    return a.sup > b.sup;
                }
        );
        left_child = new interval_tree(left);
        right_child = new interval_tree(right);
    }

    std::vector<range_t<Scalar> > get(Scalar q)
    {
        if (left_segments.empty())
            return std::vector<range_t<Scalar> >();
        std::vector<range_t<Scalar> > result;
        if (q < mid)
            result = left_child->get(q);
        if (q > mid)
            result = right_child->get(q);
        if (q < mid)
        {
            for (int i = 0; i < left_segments.size() && left_segments[i].inf <= q; ++i)
                result.push_back(left_segments[i]);
        }
        else
        {
            for (int i = 0; i < right_segments.size() && right_segments[i].sup >= q; ++i)
                result.push_back(right_segments[i]);
        }
        return std::move(result);
    }

private:
    interval_tree *left_child, *right_child;
    Scalar mid;
    std::vector<range_t<Scalar> > left_segments, right_segments;

    interval_tree()
        : left_child(0)
        , right_child(0)
    {}
};

vector<range_t<int>> segments;

void run()
{
    int l, r, q;
    readln(n, m);
    int e = 0;
    fori(n)
        readln(l, r, q),
        segments.pb(range_t<int>(r, r + q, l)),
        e = max(e, q);
    interval_tree<int> it(segments);
    int ans = 0;
    fori(m)
    {
        if (ans / 2 == e)
            break;
        readln(l, r, q);
        if (q * 2 < ans)
            continue;
        auto vec = it.get(r);
        for (auto seg : vec)
            if (!(l >= seg.r || l + q < seg.r || seg.sup - seg.inf < ans / 2))
                ans = max(ans, min(min(seg.sup - r, r - seg.inf), min(seg.r - l, l + q - seg.r)));
    }
    cout << ans << endl;
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
