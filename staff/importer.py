#!/usr/bin/env python3
import sys

pattern = '//Igorjan'
libr    = '#include <library.h>'

def main():
    library = [x.split('\n', 1) for x in ''.join(open(sys.argv[2], 'r').readlines()).split(pattern)]
    source = ''.join(open(sys.argv[1], 'r').readlines())
    toAppend = []
    for i in range(len(library)):
        if len(library[i]) == 2 and library[i][0] in source and not ('//' + library[i][0] in source):
            toAppend.append(''.join(['\n', '//', library[i][0], '\n', library[i][1][:-1]]))
    source = source.replace(libr, '').split(pattern, 1)
    open(sys.argv[1], 'w').write(source[0] + ''.join(toAppend) + pattern + source[1])

if __name__ == '__main__':
    main()
