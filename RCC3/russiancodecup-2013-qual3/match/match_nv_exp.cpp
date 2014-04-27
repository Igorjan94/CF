#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
vector<int> a;
long long sum, cnt;
int c[30], d[30];

void gen(int pos, int b)
{
	if (b == k)
	{
		vector<bool> used(n);
		for (int i = 0; i < k; i++)
			used[c[i]] = true; 
		int kk = 0;
		for (int i = n - 1; i >= 0; i--)
			if (!used[i]) d[kk++] = i;
		/*for (int i = 0; i < k; i++)
			cerr << c[i] << " " << d[i] << " " << a[c[i]] - a[d[i]] << "\n"; 
		cerr << "\n"; */
		int cur_sum = 0;
		for (int i = 0; i < k; i++)
			sum += abs(a[c[i]] - a[d[i]]), cur_sum += abs(a[c[i]] - a[d[i]]); 
        // cerr << cur_sum << " ";
		cnt++;
		return;
	}
	for (int i = pos + 1; i < n; i++)
	{
		c[b] = i;
		gen(i, b + 1);
	}
}

int main()
{
	int t;   
	scanf("%d\n", &t);
	while (t--)
	{
		scanf("%d\n", &n); 
		k = n / 2;
		a.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a.begin(), a.end());
		gen(-1, 0);
		double ans = sum;
		ans /= cnt;
		printf("%.9lf\n", ans);
		a.clear();
	}
}


