#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
void run()
{
    int x;
    cin >> x;
    if(!x){
        cout << 1;
        return;
    }
    if (x == 1){
        cout << 0;
        return;
    }
    if (x % 2){
        cout << 4;
        x--;
    }
    while (x >= 2){
        cout << 8;
        x -= 2;
    }
}
 
int main()
{
    freopen("holes.in", "r", stdin);
    freopen("holes.out", "w", stdout);
    run();
    return 0;
}