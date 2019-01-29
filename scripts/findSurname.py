#!/usr/bin/env python3
import sys
import re

surnames = {}

for line in open('/home/igorjan/.zhistory', 'r', encoding='cp1251').readlines():
    if re.match(': \d{10}:0;', line) != None:
        line = line.split(';', 1)[1]
        m = re.search('git clone https://github.com/(.*?)/.*? (\w+)', line)
        if m != None:
            surnames[m.group(1)] = m.group(2)
            # print(m.group(1), m.group(2))

if len(sys.argv) == 1:
    print("Usage: cloneRep https://gitgub.com/username/repname")
    sys.exit()

rep = sys.argv[1]
m = re.search('https://github.com/(.*?)/', rep)
if m != None and m.group(1) in surnames:
    surname = surnames[m.group(1)]
else:
    sys.stderr.write('Surname is not found!\n')
    surname = input()

print(surname)
