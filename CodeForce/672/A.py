n = int(input())
s = ''
i = 1
while len(s) < n:
    s += str(i)
    i += 1
print(s[n - 1])
