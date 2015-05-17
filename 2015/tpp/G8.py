readints = ',[>,]<'
goleft = '[<]>'
goright = '[>]<'
pr = '.'
aplusb = '>[-<+>]<'
bplusa = '[->+<]'
aitov = '!'
vtoai = '?'
aminusb = '>[-<->]<'
pause = '#'
swap = ''.join(['>', aitov, '=<', vtoai])

def i(s):
    return '(' + s + ')'

def wh(s):
    return '[' + s + ']'

print(''.join([
    '>+[>=+]|>[0+>]|',
    ',',
    wh(''.join([
        wh(''.join([
            swap,
            '>',
            i(
                '<+>'
            ),
            '-'
        ])),
        '<',
        wh(''.join([
            swap,
            '<'
        ])),
        '|,'
    ])),
    '|>-',
    wh(''.join([
        '>-',
        aitov,
        '<',
        aminusb,
        '>',
        vtoai,
        '<$',
        wh(
            '^-'
        ),
        '>'
    ]))
]))

