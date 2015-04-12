import sys
import functools

def main():
    writeln_range(sorted(read_int_array()))







def read():
    return sys.stdin.readline().rstrip('\n')

def read_array(sep=None, maxsplit=-1):
    return read().split(sep, maxsplit)

def read_int():
    return int(read())

def read_int_array(sep=None, maxsplit=-1):
    return list(map(int, read_array(sep, maxsplit)))

def writeln(*args, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in args) + end)

def writeln_range(array, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in array) + end)

if __name__ == '__main__':
    main()

#@functools.lru_cache(None)
