n = int(input())
for t in range(n):
    t1, t2, m = input().split()
    h1, m1, s1 = map(int, t1.split(':'))
    h2, m2, s2 = map(int, t2.split(':'))
    m = int(m) * 60
    SECSINDAY = 24 * 60 * 60
    exam = ((h2 - h1) * 60 * 60 + (m2 - m1) * 60 + (s2 - s1) - 1) % SECSINDAY + 1
    if m <= exam:
        print ('Perfect')
    elif m <= exam + 60 * 60:
        print ('Test')
    else:
        print ('Fail')

