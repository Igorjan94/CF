#pragma comment(linker, "/STACK:16000000")
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#define INF 1000000000
using namespace std;
 
vector<bool> used_glob;
vector<vector<int>> edges;
vector<int> diams;
 
int dfs1(int v, int d, vector<bool>& used) {
    if (used[v])
        return 0;
    int max_deep = d;
    used[v] = 1;
    for (int i = 0; i < edges[v].size(); i++) {
        max_deep = max(max_deep, dfs1(edges[v][i], d + 1, used));
    }
    return max_deep;
}
 
void dfs2(int v, int depth, int cur_d, int &new_v, vector<bool>& used) {
    if (used[v])
        return;
    used[v] = 1;
    if (depth == cur_d) {
        new_v = v;
        return;
    }
    for (int i = 0; i < edges[v].size(); i++) {
        dfs2(edges[v][i], depth, cur_d + 1, new_v, used);
    }
}
 
void find_d(int v) {
    vector<bool> used = vector<bool>(edges.size(), false);
    int deep1 = dfs1(v, 0, used);
    used = vector<bool>(used.size(), false);
    int new_v;
    dfs2(v, deep1, 0, new_v, used);
    int ans = dfs1(new_v, 0, used_glob);
    diams.push_back(ans);
}
void main(){
    //ifstream in("in.txt"); 
    //ofstream out("out.txt");
    int n, l;
    cin >> n >> l;
    edges = vector<vector<int>>(n);
    for (int i = 0; i < l; i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    used_glob = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!used_glob[i])
            find_d(i);
    }
    if (diams.size() == 1) {
        cout << diams[0];
        return;
    } 
    if (diams.size() == 2) {
        int a = diams[0];
        int b = diams[1];
        cout << max(a, a / 2 + a % 2 + b / 2 + b % 2 + 1);
    } else {
        sort(diams.begin(), diams.end());
        int a = diams[diams.size() - 1];
        int b = diams[diams.size() - 2];
        int c = diams[diams.size() - 3];
        int ans = max(a, a / 2 + a % 2 + b / 2 + b % 2 + 1);
        ans = max(ans, b / 2 + b % 2 + c / 2 + c % 2 + 2);
        cout << ans;
    }
}
