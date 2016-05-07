for q in range(int(input())):
    toPrint = "Case #" + str(q + 1) + ": "
    n = int(input())
    temp = n
    ok = False
    a = [0] * 10
    while n != 0:
        for j in str(temp):
            a[ord(j) - 48] = 1
        cur = True
        for j in range(10):
            cur = cur and (a[j] == 1)
        if cur:
            ok = True
            toPrint += str(temp)
            break
        temp += n
    if not ok:
        toPrint += "INSOMNIA"
    print(toPrint)
