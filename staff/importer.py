#!/usr/bin/env python3
import sys

'''
Primitive linker. Takes source, splits by pattern. After first pattern inserts functions, which are described in library files and are used in source. If source doesn't contain pattern, deletes all code(feature!!!). Library file should have this structure:
//patternNameOfBlock (NO SPACE AFTER PATTERN)

function1 of block NameOfBlock

function2 of block NameOfBlock
...
functionN of block NameOfBlock

//patternOtherNameOfBlock

function of block OtherNameOfBlock
...

If source contains 'NameOfBlock', everything between NameOfBlock and OtherNameOfBlock is inserted in source. For not duplicating before each block in source '//NameOfBlock' is added

For example see my library.h and main.cpp
'''

pattern = '//Igorjan'
libr    = '#include <library.h>'
comment = '//'

def main(i):
    library = [x.split('\n', 1) for x in ''.join(open(sys.argv[i], 'r').readlines()).split(pattern)]
    source = ''.join(open(sys.argv[1], 'r').readlines())
    toAppend = []
    for i in range(len(library)):
        if len(library[i]) == 2 and library[i][0] in source and not (comment + library[i][0] in source):
            toAppend.append(''.join(['\n', comment, library[i][0], '\n', library[i][1][:-1]]))
    source = source.replace(libr, '').split(pattern, 1)
    if len(source) == 2:
        open(sys.argv[1], 'w').write(source[0] + pattern + ''.join(toAppend) + source[1])

if __name__ == '__main__':
    if len(sys.argv) <= 2:
        print('Usage: ./importer.py source.ext library1 [library2 ...]')
        sys.exit()
    for i in range(2, len(sys.argv)):
        main(i)
