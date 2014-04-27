MOD = 10**9 + 7

t = int(input())

for i in range(t):	
	s = input().strip()
	if not s:
		break
	quest = sum(int(c == '?') for c in s)
	result = pow(2, quest, MOD)
	tandem = 1
	for j in range(len(s) // 2):
		if s[j] == '?':
			if s[len(s)//2:][j] == '?':
				tandem *= 2
		else:
			if s[len(s)//2:][j] != '?' and s[j] != s[len(s)//2:][j]:
				tandem = 0
				break
	print((result - tandem) % MOD)
