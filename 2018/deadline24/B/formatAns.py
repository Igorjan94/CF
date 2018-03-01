import sys
import re

lines = []

def printAns():
    cc = 0
    for i in range(len(lines)):
        lines[i] = list(map(int, lines[i].split()))
        cc = max(cc, max(lines[i]) // 100)
    ans = [[(-1, -1) for j in range(100)] for i in range(cc)]
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if (lines[i][j] < 0):
                lines[i][j] *= -1
            pipe = lines[i][j] // 100 - 1
            index = lines[i][j] % 100
            ans[pipe][index] = (i, j)

    print(cc)
    for i in range(cc):
        sss = ''
        for j in range(len(ans[i])):
            if ans[i][j + 1] == (-1, -1):
                break
            if ans[i][j][0] + 1 == ans[i][j + 1][0]:
                sss += 'E'
            if ans[i][j][0] - 1 == ans[i][j + 1][0]:
                sss += 'W'
            if ans[i][j][1] + 1 == ans[i][j + 1][1]:
                sss += 'S'
            if ans[i][j][1] - 1 == ans[i][j + 1][1]:
                sss += 'N'
        print(sss)


for line in sys.stdin:
    if len(re.sub(r'\s', '', line)) == 0:
        printAns()
        lines = []
    else:
        lines.append(line)

printAns()
