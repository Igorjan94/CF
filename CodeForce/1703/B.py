t = int(input())
for q in range(t):
    n = int(input())
    s = input()
    solved = set()
    ans = 0
    for c in s:
        ans += 1
        if c not in solved:
            ans += 1
        solved.add(c)
    print(ans)
