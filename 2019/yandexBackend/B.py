import sys
import time

def is_op(c):
    return c == '+' or c == '-' or c == '*' or c == '/' or c == '<' or c == '>' or c == '=' or c == '?'

K = int(input())

S = input().split(' ')
I = 0
A = []

def push(x):
    global I
    global A
    A[I] = x
    I += 1

def pop():
    global I
    global A
    I -= 1
    return A[I]

def process_op(op):
    if len(op) == 0: return
    c = op[0]
    if len(op) == 1 and is_op(c):
        r = pop()
        l = pop()
        R = str(r)
        L = str(l)
        if type(l) == int and type(r) == int:
            if c == '+': push(l + r)
            if c == '-': push(l - r)
            if c == '*': push(l * r)
            if c == '/': push(0 if r == 0 else l // r)
            if c == '<': push(l < r)
            if c == '=': push(l == r)
            if c == '?':
                cmp = pop()
                if type(cmp) == bool:
                    push(l if cmp else r)
                else:
                    push(cmp); push(l); push(r); push('?')
        else:
            if c == '+': push(l); push(r); push('+')
            if c == '-': push(l); push(r); push('-')
            if c == '*':
                if l == 0 or r == 0:
                    push(0)
                else:
                    push(l); push(r); push('*')
            if c == '/': push(l); push(r); push('/')
            if c == '<': push(l); push(r); push('<')
            if c == '=': push(l); push(r); push('=')
            if c == '?':
                cmp = pop()
                if type(cmp) == bool:
                    push(l if cmp else r)
                else:
                    push(cmp); push(l); push(r); push('?')

    elif len(op) == 1 and ord(c) >= ord('a') and ord(c) <= ord('z'):
        push(op)
    else:
        push(int(op))


A = [0] * 10 ** 5
for ss in S:
    process_op(ss)

s = list(map(str, A[:I]))
# print(' '.join(s))

i = 0
a = []

def push(x):
    global i
    global a
    a[i] = x
    i += 1

def pop():
    global i
    global a
    i -= 1
    return a[i]

def process_op2(alpabet, op):
    if len(op) == 0: return
    c = op[0]
    if len(op) == 1 and is_op(c):
        r = pop()
        l = pop()
        if c == '+': push(l + r)
        if c == '-': push(l - r)
        if c == '*': push(l * r)
        if c == '/': push(0 if r == 0 else l // r)
        if c == '<': push(l < r)
        if c == '=': push(l == r)
        if c == '?':
            cmp = pop()
            push(l if cmp else r)
    elif len(op) == 1 and ord(c) >= ord('a') and ord(c) <= ord('z'):
        push(alphabet[ord(c) - ord('a')])
    elif len(op) == 1 and ord(c) >= ord('A') and ord(c) <= ord('Z'):
        push(alphabet[ord(c) - ord('A')])
    else:
        push(int(op))


n = int(input())
for ___ in range(n):
    alphabet = list(map(int, input().split()))
    a = [0] * 10 ** 5
    i = 0
    for ss in s:
        process_op2(alphabet, ss)
    print(a[0])
