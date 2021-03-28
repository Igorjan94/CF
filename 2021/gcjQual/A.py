def readln():
    return list(map(int, input().split()))


def run():
    [n] = readln()
    a = readln()
    ans = 0
    for i in range(n - 1):
        mn = a[i]
        index = i
        for j in range(i, n):
            if a[j] < mn:
                mn = a[j]
                index = j
        ans += index - i + 1
        a[i:index + 1] = reversed(a[i:index + 1])

    return ans


[t] = readln()
for q in range(1, t + 1):
    print(f'Case #{q}: {run()}')
