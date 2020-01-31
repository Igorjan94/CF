n = int(input())

commands = ('( ' + input() + ' )').split()
stack = [[]]
add = 0
mod = 998244353

for c in commands:
    if c == '(':
        add += 1
        stack.append([])
    elif c == ')':
        add += 1
        x = stack.pop()
        temp = x[0]
        for i in range(1, len(x)):
            if add % 2 == 0:
                temp += x[i]
            else:
                temp *= x[i]
            temp %= mod
        stack[-1].append(temp)
    else:
        stack[-1].append(int(c))


print(stack[0][0])
