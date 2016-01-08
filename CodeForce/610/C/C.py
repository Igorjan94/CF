import sys
x = 2 ** int(input())

ss = []
ss.append("*")
for i in range(x):
    t = []
    for j in range(i):
        print(j)
        print(ss)
        print(ss[j])
        sys.stdout.flush()
        q = ""
        for k in range(i):
            if ss[j][k] == "+":
                q += "++"
            else:
                q += "--"
        t.append(q)
        q = ""
        for k in range(i):
            if ss[j][k] == "+":
                q += "-+"
            else:
                q += "-+"
        t.append(q)
    print("t", t)
    # ss = t
for i in range(x):
    print(s[i].replace('-', '*'))
