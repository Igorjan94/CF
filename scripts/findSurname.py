#!/usr/bin/env python3
import sys
import re
from pathlib import Path
home = Path.home()

surnames = {}
zhistory = home.joinpath('.zhistory')
surnamesPath = home.joinpath('.cache').joinpath('clonerep')
if surnamesPath.is_file():
    surnamesFile = open(surnamesPath, 'r')
    print('cache exists, reading')
else:
    surnamesFile = open(surnamesPath, 'w')
    print('NO')

    for line in open(zhistory, 'r', encoding='cp1251').readlines():
        if re.match(': \d{10}:0;', line) != None:
            line = line.split(';', 1)[1]
            m = re.search('git clone https://github.com/(.*?)/.*? (\w+)', line)
            if m != None:
                surnames[m.group(1)] = m.group(2)
                surnamesFile.write(m.group(1) + " " + m.group(2) + "\n")

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
