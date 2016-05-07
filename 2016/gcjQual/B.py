for q in range(int(input())):
    s = input()
    for i in range(len(s)):
        if s[-1] == '+':
            s = s[:-1]
    ans = 1 if len(s) > 0 else 0
    for i in range(len(s) - 1):
        if s[i] != s[i + 1]:
            ans += 1
    print("Case #" + str(q + 1) + ": " + str(ans))
