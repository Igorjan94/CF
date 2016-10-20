def ok(n, m):
    if n == 1 or m == 1:
        return False
    if n == 2:
        return m % 3 == 0
    if m == 2:
        return n % 3 == 0

    if n % 2 == 0 and m % 3 == 0:
        return True
    if n % 3 == 0 and m % 2 == 0:
        return True
    if n % 6 == 0:
        return True
    if m % 6 == 0:
        return True
    return False


for T in range(int(input())):
    n, m = list(map(int, input().split()))
    print('Yes' if ok(n, m) else 'No')
