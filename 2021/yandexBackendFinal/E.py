categories = {}
offers = []

input()

category = {}
while True:
    s = input().strip()
    if s.startswith('-'):
        if 'id' in category:
            category['id'] = int(category['id'])
            categories[category['id']] = category
        category = {}
        s = s[2:]
    if s == 'offers:':
        category['id'] = int(category['id'])
        categories[category['id']] = category
        break
    s = s.split(':', 1)
    category[s[0]] = s[1].strip()

try:
    offer = {}
    while True:
        s = input().strip()
        if s.startswith('-'):
            if 'id' in offer:
                offer['price'] = int(offer['price'])
                categoryId = int(offer['categoryId'])
                del offer['categoryId']
                offer['id'] = int(offer['id'])
                category = categories[categoryId]
                if not 'minOffer' in category or category['minOffer']['price'] > offer['price']:
                    categories[categoryId]['minOffer'] = offer
                if not 'maxOffer' in category or category['maxOffer']['price'] < offer['price']:
                    categories[categoryId]['maxOffer'] = offer
            offer = {}
            s = s[2:]
        s = s.split(':', 1)
        offer[s[0]] = s[1].strip()
except:
    pass


def printOffer(offer, title):
    print(f'  {title}:')
    print('    id:', offer['id'])
    print('    name:', offer['name'])
    print('    description:', offer['description'])
    print('    price:', offer['price'])

for x in categories.values():
    if 'minOffer' in x:
        print('- id:', x['id'])
        print('  name:', x['name'])
        printOffer(x['minOffer'], 'minOffer')
        printOffer(x['maxOffer'], 'maxOffer')
