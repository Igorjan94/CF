#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int t;   
	scanf("%d\n", &t);
	vector<int> a;
	while (t--)
	{
		int n;
		scanf("%d\n", &n); 
		a.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		nth_element(a.begin(), a.begin() + n / 2, a.end());
		long long min_sum = 0, max_sum = 0;
		for (int i = 0; i < n / 2; i++)
			min_sum += a[i];
		for (int i = n / 2; i < n; i++)
			max_sum += a[i];
		printf("%.9lf\n", (double)(max_sum - min_sum));
		a.clear();
	}
}


