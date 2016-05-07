for q in range(int(input())):
    k, c, s = map(int, input().split())
    print("Case #" + str(q + 1) + ": " + " ".join(str(1 + i * (k ** (c - 1))) for i in range(k)))
