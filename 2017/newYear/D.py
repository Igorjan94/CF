import sys

def get(c):
    if c <= 9:
        return chr(48 + c)
    elif c <= 35:
        return chr(97 + c - 10)
    else:
        return chr(65 + c - 36)

x = int(input())
n = int(input())
a = list(map(int, input().split()))
deg = [1] * n
ans = ''

for i in range(1, n):
    deg[i] = a[i - 1] * deg[i - 1]

for i in range(n):
    count = x // deg[n - i - 1]
    if count >= a[n - i - 1]:
        count = a[n - i - 1] - 1
    ans += get(count)
    x -= count * deg[n - i - 1]

if x != 0:
    print('Error')
else:
    index = 0
    while ans[index] == '0':
        index += 1
    print(ans[index:])
