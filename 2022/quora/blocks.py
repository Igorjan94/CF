def get(n):
    n = int(n)
    ret = ['0'] * 8
    for i in range(8):
        if (1 << i) & n:
            ret[7 - i] = '1'
    return ''.join(ret)

n = int(input())
masks = []
for i in range(n):
    s, m = input().split('/')
    m = int(m)
    c = ''.join(map(get, s.split('.')))
    c = c[:m] + '*' * (32 - m)
    masks.append(c)

masks.sort()
ans = [masks[0]]
for mask in masks:
    ans.append(mask)
    while len(ans) >= 2:
        first = -1
        for j in range(32):
            if ans[-2][j] != ans[-1][j]:
                first = j
                break
        if first == -1 or ans[-2][first] == '*':
            ans.pop()
            break
        if first == 31 or (ans[-2][first + 1] == '*' and ans[-1][first + 1] == '*'):
            ans[-2] = ans[-2][:first] + '*' * (32 - first)
            ans.pop()
            continue
        break

for mask in ans:
    m = 32 - mask.count('*')
    mask = mask.replace('*', '0')
    print('.'.join(str(int(mask[i * 8 : (i + 1) * 8], 2)) for i in range(4)) + '/' + str(m))
