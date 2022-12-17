import sys

k = int(input())
s = input()
n = len(s)
for i in range(n):
    if s[i] == '1':
        for j in range(i + k + 1, n, k):
            if s[j] == '1':
                print(i + 1, j + 1)
                sys.exit()

print(0, 0)
