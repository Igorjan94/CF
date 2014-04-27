#include <cstdio>
#include <algorithm>

#define MAX_SIZE 1000007

int a[MAX_SIZE];
int n, t, n2;
long long ans;

int main() {
	scanf("%d\n", &t);
	while (t--) {
		scanf("%d\n", &n); 
		for (int i = 0; i < n; ++i)
			scanf("%d", a + i);
		ans = 0, n2 = n >> 1;
		std::nth_element(a, a + n2, a + n);
		for (int i = 0; i < n; ++i)
			ans += (i < n2 ? -a[i] : a[i]);
		printf("%I64d\n", ans);
	}
}


