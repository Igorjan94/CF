#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#define ULL unsigned long long
using namespace std;
 
ULL F[18];
 
ULL num_by_perm(vector<int> v) {
    if (v.size() == 2) {
        return 0;
    }
    int n = v.size() / 2;
    ULL ans = (v[1] - 2) * F[n - 1];
    vector<int> cut;
    for (int i = 2; i < v.size(); i++) {
        if (v[i] > v[1])
            cut.push_back(v[i] - 2);
        else
            cut.push_back(v[i] - 1);
    }
    return ans + num_by_perm(cut);
}
 
vector<int> perm_by_num(ULL num, int n) {
    vector<int> ans(2 * n);
    if (n == 1) {
        ans[0] = 1;
        ans[1] = 2;
        return ans;
    }
    ans[0] = 1;
    ans[1] = num / F[n - 1] + 2;
    vector<int> cut = perm_by_num(num - (ans[1] - 2) * F[n - 1], n - 1);
    for (int i = 0; i < cut.size(); i++) {
        if (cut[i] + 1 < ans[1])
            ans[i + 2] = cut[i] + 1;
        else
            ans[i + 2] = cut[i] + 2;
    }
    return ans;
}
 
void main(){
    ifstream in("pairings.in");
    ofstream out("pairings.out");
    F[0] = 1;
    for (int i = 1; i < 18; i++) {
        F[i] = F[i - 1] * (2 * i - 1);
    }
    int n;
    in >> n;
    vector<int> v(2 * n);
    for (int i = 0; i < n * 2; i++) {
        in >> v[i];
    }
    ULL number = num_by_perm(v);
    number = 2 * number + 1;
    if (number >= F[n]) {
        out << "Already finished!";
        return;
    }
    v = perm_by_num(number, n);
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }
}