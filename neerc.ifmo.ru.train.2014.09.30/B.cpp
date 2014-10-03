#include <iostream>
#include <cstdio>
#include <vector>
 
using namespace std;
 
int n;
 
vector <pair<int, int> > ans;
 
int main(){
    freopen("beautifulgraph.in", "r", stdin);
    freopen("beautifulgraph.out", "w", stdout);
    cin >> n;
    if (n == 1){
        cout << "1 0";
        return 0;
    }
    if (n == 4){
        cout << "4 4" << endl;
        cout << "1 2" << endl;
        cout << "2 3" << endl;
        cout << "3 4" << endl;
        cout << "4 1" << endl;
        return 0;
    }
    if (n <= 3)
    ans.push_back({1, 2});
    for (int i = 3; i <= n; ++i){
        ans.push_back({1, i});
        ans.push_back({2, i});
    }
    cout << n << " " << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i].first << " " << ans[i].second << endl;
}