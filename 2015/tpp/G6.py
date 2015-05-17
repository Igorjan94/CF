readints = ',[>,]<'
goleft = '[<]>'
goright = '[>]<'
pr = '.'
aplusb = '>[-<+>]<'
bplusa = '[->+<]'
aminusb = '>[-<->]<'
bminusa = '[->-<]'
aitov = '!'
vtoai = '?'
pause = '#'

def i(s):
    return '(' + s + ')'

def wh(s):
    return '[' + s + ']'

print('<<<<+>>>>' + ''.join([
    readints,
    wh(''.join([
        aitov,
        '0<',
        i(''.join([
            goleft,
            '<<',
            vtoai,
            '>=>',
            aitov,
            '<<<',
            vtoai,
            aminusb,
            '>=<0>>',
            aminusb,
            '<',
            aplusb,
            i(
                '0<<->>'
            ),
            '<=<0>>>>>',
            goright
        ]))
    ])),
    '<<<',
    pr
]))
