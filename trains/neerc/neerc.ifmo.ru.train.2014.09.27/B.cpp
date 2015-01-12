#include <bits/stdc++.h>
 
using namespace std;
 
const int MaxN = 1000239;
map <int, int> m;
int a[MaxN], t, n, m1, ht[MaxN], x;
pair<int, int> h[MaxN];
int main(){
    cin >> t;
    while (t --> 0){
        cin >> n >> m1;
        for (int i = 0; i < n; ++i){
            cin >> ht[i];
            h[i] = make_pair(ht[i], i);
        }
        sort (h, h + n);
        int cnt = 0;
        for (int i = n - 1; i >= 0; i--){
            int num = h[i].second, height = h[i].first, ssd = 0;
            if (num && ht[num - 1] >= height){
                ssd++;
            }
            if (num != n - 1 && ht[num + 1] > height){
                ssd++;
            }
            if (!ssd)
                cnt++;
            if (ssd == 2)
                cnt--;
            m[height] = cnt;
        }
        m[1000000009] = 0;
        while(m1 --> 0){
            cin >> x;
            int c = (m.upper_bound(x))->first;
            cout << m[c] << " ";
        }
        m.clear();
        cout << endl;
    }
}