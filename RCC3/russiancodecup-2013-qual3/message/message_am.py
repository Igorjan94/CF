MOD = 10**9 + 7

n = int(input())
for i in range(n):
	s = input().strip()
	quest = sum(int(c == '?') for c in s)
	result = pow(2, quest, MOD)
	tandem = 1
	for j in range(len(s) // 2):
		if s[j] == '?':
			if s[len(s)//2:][j] == '?':
				tandem = (tandem * 2) % MOD
		else:
			if s[len(s)//2:][j] != '?' and s[j] != s[len(s)//2:][j]:
				tandem = 0
				break
	print((result - tandem) % MOD)
