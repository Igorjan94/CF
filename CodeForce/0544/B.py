n, k = map(int, input().split())
s = [['S'] * n for i in range(n)]
for i in range(n):
    for j in range(n):
        if k > 0 and (i + j) % 2 == 0:
            s[i][j] = 'L'
            k -= 1
print('NO' if k > 0 else 'YES\n' + '\n'.join(''.join(x) for x in s))
