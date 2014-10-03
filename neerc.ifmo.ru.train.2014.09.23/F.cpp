#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;

vector <int> a;
int main(){
    cin >> n;
    int x, y, ans = 0;
    for (int i = 0; i < n; ++i){
        cin >> y >> x;
        int c = a.size();
        if (c == 0 || x > a[c - 1]){
            a.push_back(x);
            ans++;
        }
        else{
            while (a.size() && x < a[a.size() - 1]){
                a.pop_back();
            }
            if (!(a.size() && x == a[a.size() - 1])){
                a.push_back(x);
                ans++;
            }
        }
    }
    cout << ans;

}
