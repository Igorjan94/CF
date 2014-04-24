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

int n, m, k;

const int trivial_limit = 50;
int p[1000];

ll gcd (ll a, ll b) {
	return a ? gcd (b%a, a) : b;
}

ll powmod (ll a, ll b, ll m) {
	ll res = 1;
	while (b)
		if (b & 1)
			res = (res * 1ll * a) % m,  --b;
		else
			a = (a * 1ll * a) % m,  b >>= 1;
	return res;
}

bool miller_rabin (ll n) {
	ll b = 2;
	for (ll g; (g = gcd (n, b)) != 1; ++b)
		if (n > g)
			return false;
	ll p=0, q=n-1;
	while ((q & 1) == 0)
		++p,  q >>= 1;
	ll rem = powmod (b, q, n);
	if (rem == 1 || rem == n-1)
		return true;
	for (ll i=1; i<p; ++i) {
		rem = (rem * 1ll * rem) % n;
		if (rem == n-1)  return true;
	}
	return false;
}

ll jacobi (ll a, ll b)
{
	if (a == 0)  return 0;
	if (a == 1)  return 1;
	if (a < 0)
		if ((b & 2) == 0)
			return jacobi (-a, b);
		else
			return - jacobi (-a, b);
	ll a1=a,  e=0;
	while ((a1 & 1) == 0)
		a1 >>= 1,  ++e;
	ll s;
	if ((e & 1) == 0 || (b & 7) == 1 || (b & 7) == 7)
		s = 1;
	else
		s = -1;
	if ((b & 3) == 3 && (a1 & 3) == 3)
		s = -s;
	if (a1 == 1)
		return s;
	return s * jacobi (b % a1, a1);
}

bool bpsw (ll n) {
	if ((ll)sqrt(n+0.0) * (ll)sqrt(n+0.0) == n)  return false;
	ll dd=5;
	for (;;) {
		ll g = gcd (n, abs(dd));
		if (1<g && g<n)  return false;
		if (jacobi (dd, n) == -1)  break;
		dd = dd<0 ? -dd+2 : -dd-2;
	}
	ll p=1,  q=(p*p-dd)/4;
	ll d=n+1,  s=0;
	while ((d & 1) == 0)
		++s,  d>>=1;
	long long u=1, v=p, u2m=1, v2m=p, qm=q, qm2=q*2, qkd=q;
	for (ll mask=2; mask<=d; mask<<=1) {
		u2m = (u2m * v2m) % n;
		v2m = (v2m * v2m) % n;
		while (v2m < qm2)   v2m += n;
		v2m -= qm2;
		qm = (qm * qm) % n;
		qm2 = qm * 2;
		if (d & mask) {
			long long t1 = (u2m * v) % n,  t2 = (v2m * u) % n,
				t3 = (v2m * v) % n,  t4 = (((u2m * u) % n) * dd) % n;
			u = t1 + t2;
			if (u & 1)  u += n;
			u = (u >> 1) % n;
			v = t3 + t4;
			if (v & 1)  v += n;
			v = (v >> 1) % n;
			qkd = (qkd * qm) % n;
		}
	}
	if (u==0 || v==0)  return true;
	long long qkd2 = qkd*2;
	for (ll r=1; r<s; ++r) {
		v = (v * v) % n - qkd2;
		if (v < 0)  v += n;
		if (v < 0)  v += n;
		if (v >= n)  v -= n;
		if (v >= n)  v -= n;
		if (v == 0)  return true;
		if (r < s-1) {
			qkd = (qkd * 1ll * qkd) % n;
			qkd2 = qkd * 2;
		}
	}
	return false;
}

bool prime (ll n) { // эту функцию нужно вызывать для проверки на простоту
	for (int i=0; i<trivial_limit && p[i]<n; ++i)
		if (n % p[i] == 0)
			return false;
	if (p[trivial_limit-1]*p[trivial_limit-1] >= n)
		return true;
	if (!miller_rabin (n))
		return false;
	return bpsw (n);
}

void prime_init() { // вызвать до первого вызова prime() !
	for (int i=2, j=0; j<trivial_limit; ++i) {
		bool pr = true;
		for (int k=2; k*k<=i; ++k)
			if (i % k == 0)
				pr = false;
		if (pr)
			p[j++] = i;
	}
}

void run()
{
    ll n;
    int T;
    cin >> T;
    prime_init();
    forn(qqqq, T)
    {
    cin >> n;

    ll pmax = n, pmax1 = n + 1;
    while (!prime(pmax))
        pmax--;
    while (!prime(pmax1))
        pmax1++;
    ll ans1 = (pmax - 2) * pmax1 + (n - pmax + 1) * 2;
    ll ans2 = 2 * pmax * pmax1;
    if (ans1 % 2 == 0)
    {
        ans1 /= 2;
        ans2 /= 2;
    }
    if (ans1 % pmax == 0)
    {
        ans1 /= pmax;
        ans2 /= pmax;
    }
    if (ans1 % pmax1 == 0)
    {
        ans1 /= pmax1;
        ans2 /= pmax1;
    }
    cout << ans1 << "/" << ans2 << endl;
    }
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
