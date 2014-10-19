#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
int matrix[300][300];
 
void run()
{
    int n, r, c;
    cin >> n >> r >> c;
    matrix[0][0] = 1;
    //n--;
    int ans = 1, u = n / 2, rc = 0;
    for (int i = 1; i <= u; ++i){
        if (ans + 2 > n)
            break;
        if (i >= min(r, c))
            break;
        matrix[i][0] = 1;
        matrix[0][i] = 1;
        ans += 2;
        rc++;
    //    cout << ans << " " << n << " " << i << " " << min(r, c) << endl;
    }
  //  n++;
    cout << rc + 1<< endl;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j){
     //       cout << i << " " << j << " " << ans << endl;
            if (matrix[i][j] == 0 && ans < n){
                matrix[i][j] = 1;
                ans++;
            }
        }
 
    for (int i = 0; i < r; i++, cout << "\n")
        for (int j = 0; j < c; ++j)
            cout << (matrix[i][j] ? '#' : '.');
}
 
int main()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
    run();
    return 0;
}