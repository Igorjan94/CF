#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
string s1, s2, t1, t2;
bool used[3000];
void run()
{
    cin >> s1 >> s2 >> t1 >> t2;
    int n = s1.size();
    for (int i = 0; i < n; ++i){
        char ch = s1[i];
        bool f = false;
        for (int j = 0; j < n; ++j){
            if (t1[j] == ch && s2[n - i - 1] == t2[n - j - 1] && !used[j]){
                f = true;
                used[j] = true;
                break;
            }
        }
        if (!f){
            cout << "No";
            return;
        }
    }
    cout << "Yes";
}
 
int main()
{
    freopen("enchanted.in", "r", stdin);
    freopen("enchanted.out", "w", stdout);
    run();
    return 0;
}