def readln():
    return list(map(int, input().split()))


def run():
    [n, c] = readln()
    c -= n - 1

    a = [str(i + 1) for i in range(n)]
    b = [False for i in range(n)]
    for i in range(n - 1):
        if c >= n - i - 1:
            c -= n - i - 1
            b[i] = True

    if c != 0: return 'Impossible'

    for i in range(n - 1, -1, -1):
        if b[i]:
            a[i:n] = reversed(a[i:n])

    return ' '.join(a)


[t] = readln()
for q in range(1, t + 1):
    print(f'Case #{q}: {run()}')
