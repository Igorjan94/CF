#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		int k = s.size() / 2;
		long long ans = 1, all = 1;
		for (int i = 0; i < 2 * k; i++)
			all *= (s[i] == '?') + 1, all %= MOD;
		int i = 0;
		while (i < k) {
			int cnt = (s[i] == '?') + (s[i + k] == '?');
			if (s[i] == s[i + k] && s[i] != '?') cnt++;
			ans *= cnt, ans %= MOD, i++;
		}
		cout << (all - ans + MOD) % MOD << "\n";
	}
}

