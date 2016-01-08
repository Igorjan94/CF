import re
s = input()
ok = s.find('0') == -1

s = s.replace('-', '0')
t = re.sub(r'\d', 'd', s).split('|')
s = s.replace(' ', '')

ok &= len(t) == 12 and t[0] == '' and t[-1] == ''
t = t[1:-1]
dic = ['dd', 'd/', 'X ']
last = ['dd', 'd/d', 'd/X', 'Xdd', 'Xd/', 'XXd', 'XXX']

if ok:
    for i in range(9):
        ok &= len(t[i]) == 2 and t[i] in dic
if ok:
    ok &= (len(t[-1]) == 2 or len(t[-1]) == 3) and t[-1] in last

prev = 0
count = 0
values = []
for i in range(len(s)):
    if s[i] == 'X':
        values.append(10)
        prev = 0
    elif s[i] == '/':
        values.append(58 - ord(s[i - 1]))
        prev = 0
    elif s[i] == '|':
        prev = 0
    else:
        values.append(ord(s[i]) - 48)
        if prev >= 1 and prev <= 9 and values[-1] + prev >= 10:
            ok = False
        prev = values[-1]

ans = sum(values)
j = 0
for i in range(len(s)):
    if s[i] == '|':
        count += 1
    elif ok:
        if count <= 9:
            if s[i] == 'X':
                ans += values[j + 1] + values[j + 2]
            elif s[i] == '/':
                ans += values[j + 1]
        j += 1

print("YES\n" + str(ans) if ok else "NO")
