#include <bits/stdc++.h>
#define _USE_MATH_DEFINES

using namespace std;
const double EPS = 1E-9;
const double PI = M_PI;
 
struct pt {
	double x, y;
	pt()  { }
	pt (double x, double y) : x(x), y(y)  { }
	pt operator- (const pt & p) const {
		return pt (x-p.x, y-p.y);
	}
};
 
double dist (const pt & a, const pt & b) {
	return sqrt ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
 
double get_ang (const pt & a, const pt & b) {
	double ang = abs (atan2 (a.y, a.x) - atan2 (b.y, b.x));
	return min (ang, 2*PI-ang);
}
 
struct line {
	double a, b, c;
	line (const pt & p, const pt & q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = - a * p.x - b * p.y;
		double z = sqrt (a*a + b*b);
		a/=z, b/=z, c/=z;
	}
};
 
double det (double a, double b, double c, double d) {
	return a * d - b * c;
}
 
pt intersect (const line & n, const line & m) {
	double zn = det (n.a, n.b, m.a, m.b);
	return pt (
		- det (n.c, n.b, m.c, m.b) / zn,
		- det (n.a, n.c, m.a, m.c) / zn
	);
}
 
bool parallel (const line & n, const line & m) {
	return abs (det (n.a, n.b, m.a, m.b)) < EPS;
}
 
double get_h (const pt & p1, const pt & p2,
	const pt & l1, const pt & l2, const pt & r1, const pt & r2)
{
	pt q1 = intersect (line (p1, p2), line (l1, l2));
	pt q2 = intersect (line (p1, p2), line (r1, r2));
	double l = dist (q1, q2);
	double alpha = get_ang (l2 - l1, p2 - p1) / 2;
	double beta = get_ang (r2 - r1, p1 - p2) / 2;
	return l * sin(alpha) * sin(beta) / sin(alpha+beta);
}
 
struct cmp {
	bool operator() (const pair<double,int> & a, const pair<double,int> & b) const {
		if (abs (a.first - b.first) > EPS)
			return a.first < b.first;
		return a.second < b.second;
	}
};
 
#define pointtt template<typename T = int>
pointtt struct point
{
    T x, y;
    point(){}
    point(T _x, T _y) : x(_x), y(_y) {}
    point(const point& other) : x(other.x), y(other.y) {}
    point operator=(const point& b) { x = b.x; y = b.y; return *this; }
    point operator+(const point& b) const { return point(x + b.x, y + b.y); }
    point operator-(const point& b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    T operator*(const point& b) const { return x * b.x + y * b.y; }
    T operator^(const point& b) const { return x * b.y - y * b.x; }
    T operator!() const { return x * x + y * y; }
    bool operator<(const point& b) const { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,const point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(const point<T>&a,const point<T>&b){return!point<T>(a-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(const point<T>&a,const point<T>&b,const point<T>&c){return{abs((a-b)*c)+(a^b),dist(a,b)};}
static const int CW = 1;
static const int CCW = -1;
pointtt int orientation(const point<T>&a,const point<T>&b,const point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?CCW:q<0?CW:0;}
//reflects point C to line AB (in doubles)
pointtt point<T> reflect(const point<T>&a,const point<T>&b,const point<T>&c){
    T A = a.y - b.y;
    T B = b.x - a.x;
    T C = a ^ b;
    T D = A * A - B * B;
    T S = A * A + B * B;
    return {(-D * c.x - 2 * A * B * c.y - 2 * A * C) / S, (D * c.y - 2 * A * B * c.x - 2 * B * C) / S};
};

//IgorjanconvexHull
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define   all(a)     a.begin(), a.end()
#define      ll      long long
pointtt void convexHull(vector<point<T>>&a){sort(all(a));int n=size(a),j=-1,k=0;ROF(i,n-2,0)a.push_back(a[i]);fori(n){while(j>k&&orientation(a[j-1],a[j],a[i])!=1)--j;a[++j]=a[i];if(!k&&i==n-1)k=j;}a.resize(j);}

int main() {
    int q;
    cin >> q;
    vector<double> ks;
    for (int Q = 0; Q < q; Q++)
    {
        int n;
        cin >> n;
        vector<point<ll>> P;
        fori(n)
        {
            point<ll> ppp;
            cin >> ppp;
            P.push_back(ppp);
            while (P.size() >= 3)
            {
                int sz = P.size();
                if (orientation(P[sz - 3], P[sz - 2], P[sz - 1]) == 0)
                    P[sz - 2] = P[sz - 1],
                    P.pop_back();
                else
                    break;
            }

        }
        if (P.size() >= 3)
        {
            int sz = P.size();
            if (orientation(P[sz - 2], P[sz - 1], P[0]) == 0)
                P.pop_back();
        }
        if (P.size() >= 3)
        {
            int sz = P.size();
            if (orientation(P[sz - 1], P[0], P[1]) == 0)
                P.erase(P.begin());
        }
        n = P.size();
        vector<pt> p(n);
        for (int i = 0; i < n; ++i)
            p[i].x = P[i].x,
            p[i].y = P[i].y;
        
    
        vector<int> next (n), prev (n);
        for (int i=0; i<n; ++i) {
            next[i] = (i + 1) % n;
            prev[i] = (i - 1 + n) % n;
        }
    
        set < pair<double,int>, cmp > q;
        vector<double> h (n);
        for (int i=0; i<n; ++i) {
            h[i] = get_h (
                p[i], p[next[i]],
                p[i], p[prev[i]],
                p[next[i]], p[next[next[i]]]
            );
            q.insert (make_pair (h[i], i));
        }
    
        double last_time;
        while (q.size() > 2) {
            last_time = q.begin()->first;
            int i = q.begin()->second;
            q.erase (q.begin());
    
            next[prev[i]] = next[i];
            prev[next[i]] = prev[i];
            int nxt = next[i],   nxt1 = (nxt+1)%n,
                prv = prev[i],   prv1 = (prv+1)%n;
            if (parallel (line (p[nxt], p[nxt1]), line (p[prv], p[prv1])))
                break;
    
            q.erase (make_pair (h[nxt], nxt));
            q.erase (make_pair (h[prv], prv));
    
            h[nxt] = get_h (
                p[nxt], p[nxt1],
                p[prv1], p[prv],
                p[next[nxt]], p[(next[nxt]+1)%n]
            );
            h[prv] = get_h (
                p[prv], p[prv1],
                p[(prev[prv]+1)%n], p[prev[prv]],
                p[nxt], p[nxt1]
            );
    
            q.insert (make_pair (h[nxt], nxt));
            q.insert (make_pair (h[prv], prv));
        }
    
        ks.push_back(last_time);
    }
    int k;
    cin >> k;
    vector<int> a(k);
    fori(k)
        cin >> a[i];
    sort(all(ks));
    sort(all(a));
    int cnt = 0;
    int i = 0;
    for (auto x: a)
    {
        while (i < q && x > ks[i])
            ++i;
        if (i < q)
            ++i,
            ++cnt;
    }
    cout << cnt << endl;
}
