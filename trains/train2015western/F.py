n = int(input())
a = []
for i in range(n):
    a.append(input())
ok = True
for i in range(n):
    for j in range(n):
        if a[i][j] == '*':
            if a[n - i - 1][n - j - 1] == '*' or a[j][n - i - 1] == '*' or a[n - j - 1][i] == '*':
                ok = False
print('YES' if ok else 'NO')
