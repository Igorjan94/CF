import sys

cc = 0

for i in range(10):
    print(i)
    sys.stdout.flush()
    answer = input()
    fi = answer[:2]
    if answer == 'no':
        cc += 1
    if answer[-2:] == 'so' or answer == 'not bad' or answer == 'cool' or cc == 4 or fi == 'gr':
        print('normal')
        break
    if answer[-2:] == 'en' or answer == 'no way' or fi == 'te' or fi == 'wo' or fi == 'ar' or fi == 'go':
        print('grumpy')
        break
