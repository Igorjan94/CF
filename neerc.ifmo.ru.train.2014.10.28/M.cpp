#define TASKNAME ""
 
#include <bits/stdc++.h>
 
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)a.size()
#define fst first
#define snd second
#define fori(n) for(int i = 0; i < n; ++i)
#define fori1(n) for(int i = 1; i < n; ++i)
#define forj(n) for(int j = 0; j < n; ++j)
 
using namespace std;
 
const double EPS = 1e-9;
const int INF = 1e9;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
 
struct tri
{
    int row, col, bal;
    tri(int bal, int row, int col)
    {
        this->bal = bal;
        this->row = row;
        this->col = col;
    }
};
 
int main() {
//    freopen("in.in.c", "r", stdin);
//    freopen(TASKNAME".out", "w", stdout);
    int n;
    cin >> n;
    vector<string> s(n);
    getline(cin, s[0]);
    fori(n)
        getline(cin, s[i]);
    vector<stack<tri> > a(27);
    int balance = 0;
    fori(n)
        forj(s[i].size())
            switch (s[i][j]) {
                case ' ' :
                    break;
                case '{' : {
                    balance++;
                    break;
                }
                case '}' : {
                    fori(26)
                        if (a[i].size() && a[i].top().bal == balance)
                            a[i].pop();
                    balance--;
                    break;
                }
                default :
                    if (a[s[i][j] - 'a'].size())
                        printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n",
                               i + 1, j + 1, s[i][j], a[s[i][j] - 'a'].top().row, a[s[i][j] - 'a'].top().col);
                    a[s[i][j] - 'a'].push(tri(balance, i + 1, j + 1));
            }
    return 0;
}