import requests

a = []
for i in range(4):
    a.append(input())

def get(names):
    return requests.request('MEW', 'http://127.0.0.1:7777/', headers={'X-Cat-Variable': ','.join(names)}).headers.get('X-Cat-Value').split(', ')

values = []

three = get(a[:-1])
s = set(three)
if len(s) == 1: #000
    fourth = get([a[3]])[0]
    values = [three[0], three[1], three[2], fourth]
elif len(s) == 3:#012
    zero, one, two = three
    ad = get([a[0], a[3]])
    if ad[0] == ad[1]:
        if ad[0] == zero:
            if get([a[1]])[0] == one:
                values = [zero, one, two, zero]
            else:
                values = [zero, two, one, zero]
        elif ad[0] == one:
            if get([a[1]])[0] == zero:
                values = [one, zero, two, one]
            else:
                values = [one, two, zero, one]
        else:
            if get([a[1]])[0] == one:
                values = [two, one, zero, two]
            else:
                values = [two, zero, one, two]
    elif ad[0] == zero and ad[1] == one:
        cd = get([a[2], a[3]])
        if cd[0] == cd[1] and cd[0] == zero:
            values = [one, two, zero, zero]
        elif cd[0] == cd[1] and cd[0] == one:
            values = [zero, two, one, one]
        elif cd[0] == one:
            values = [zero, one, two, one]
        else:
            values = [one, zero, two, zero]
    elif ad[0] == zero and ad[1] == two:
        cd = get([a[2], a[3]])
        if cd[0] == cd[1] and cd[0] == zero:
            values = [two, one, zero, zero]
        elif cd[0] == cd[1] and cd[0] == two:
            values = [zero, one, two, two]
        elif cd[0] == zero:
            values = [two, zero, one, zero]
        else:
            values = [zero, two, one, two]
    elif ad[0] == one and ad[1] == two:
        cd = get([a[2], a[3]])
        if cd[0] == cd[1] and cd[0] == one:
            values = [two, zero, one, one]
        elif cd[0] == cd[1] and cd[0] == two:
            values = [one, zero, two, two]
        elif cd[1] == one:
            values = [two, one, zero, one]
        else:
            values = [one, two, zero, two]
    else:
        first = ad[0] if ad[0] in s else ad[1]
        forth = ad[1] if ad[0] in s else ad[0]
        s.remove(first)
        second = get([a[1]])[0]
        s.remove(second)
        third = s.pop()
        values = [first, second, third, forth]


else:#001
    zero = three[1]
    one = three[2] if three[0] == three[1] else three[0]
    tf = get([a[2], a[3]])
    if tf[0] == tf[1]:#001 + ??yy
        if tf[0] == zero:#??00
            if get([a[0]])[0] == one:#1000
                values = [one, zero, zero, zero]
            else:#0100
                values = [zero, one, zero, zero]
        else:#0011
            values = [zero, zero, one, one]
    else:
        if set(tf) == s:#??01
            ad = get([a[0], a[3]])
            if ad[0] == ad[1] and ad[0] == zero:
                values = [zero, zero, one, zero]
            elif ad[0] == ad[1] and ad[1] == one:
                values = [one, zero, zero, one]
            else:
                values = [zero, one, zero, one]
        else:#??(0/1)2
            third = tf[0] if tf[0] in s else tf[1]
            forth = tf[1] if tf[0] in s else tf[0]
            if third == one:#??12
                values = [zero, zero, third, forth]
            else:#??02
                if get([a[0]])[0] == zero:
                    values = [zero, one, zero, forth]
                else:
                    values = [one, zero, zero, forth]


print(*values, sep='\n')



