import json
from datetime import datetime
from dateutil.relativedelta import relativedelta

f = '%Y-%m-%d'
now = datetime.strptime('2023-04-15', f)
dd = datetime.fromisoformat('2013-01-03T12:00:00.000+03:00')

def filter_data(text: str) -> str:
    j = json.loads(text)
    ret = []
    for x in j:
        if not 'admin' in x['roles']:
            continue
        dob = datetime.strptime(x['profile']['dob'], f)
        difference = relativedelta(now, dob).years
        if difference < 35:
            continue
        created = datetime.fromisoformat(x['createdAt'])
        if created < dd:
            continue

        ret.append({
            "username": x['username'],
            "email": x['email'],
            "name": x['profile']['name'],
            "age": difference,
        })
    return json.dumps(ret)


if __name__ == "__main__":
    input_str = input()
    print(filter_data(input_str))

