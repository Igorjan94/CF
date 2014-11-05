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
 
vector <pair <int, int> > ans;
int a[1239];
 
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << "Yes" << endl;
    if (n == k)
        for (int i = 0; i < n; ++i){
            if (a[i] + 1)
                cout << a[i] << " " << i + 1;
            else
                cout << i + 1 << " " << i + 1;
            cout << endl;
        }
    else {
        for (int i = 0; i < n; ++i){
            if (a[i] + 1)
                cout << a[i] << " " << 1;
            else
                cout << 1 << " " << 1;
            cout << endl;
        }
    }
 
 
}